// Copyright 2023 KUKA Deutschland GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "kuka/external-control-sdk/iiqka/robot.h"

#include <grpcpp/create_channel.h>

#include "iiqka/proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/secure_socket.h"

using namespace std::chrono_literals;
using namespace kuka::external::control;

namespace kuka::external::control::iiqka {

Robot::Robot(Configuration config)
    : control_signal_(&controlling_arena_, config.dof), last_motion_state_(config.dof) {
  config_.koni_ip_address = config.koni_ip_address;
  config_.client_ip_address = config.client_ip_address;
  config_.is_secure = config.is_secure;
  config_.certificate_path = config.certificate_path;
  config_.private_key_path = config.private_key_path;
  config_.dof = config.dof;
  config_.monitoring_timeout = config.monitoring_timeout;
  config_.connection_timeout = config.connection_timeout;
  config_.initial_control_mode = config.initial_control_mode;

  event_handler_ = std::make_unique<EventHandler>();
}

OperationStatus Robot::Setup() {
  Reset();
  auto replier_address = os::core::udp::communication::SocketAddress::SafeConstruct(
          config_.client_ip_address.c_str(), config_.udp_replier_port);

  auto subscriber_address = os::core::udp::communication::SocketAddress::SafeConstruct(
          config_.udp_subscriber_multicast_address.c_str(), config_.udp_subscriber_port);

  auto interface_address =
      os::core::udp::communication::SocketAddress::SafeConstruct(config_.client_ip_address);

  if (!replier_address || !subscriber_address || !interface_address) {
    return OperationStatus(ReturnCode::ERROR, "Invalid IP in configuration");
  }

  if (config_.is_secure) {
    replier_socket_ = std::make_unique<os::core::udp::communication::SecureReplier>(
        config_.certificate_path, config_.private_key_path, replier_address.value());
    dynamic_cast<os::core::udp::communication::SecureReplier&>(*replier_socket_)
        .SetServerErrorCallback([this](os::core::udp::communication::SecureReplier& replier) {
          std::lock_guard<std::mutex> lck(event_handler_mutex_);
          const auto& error_ret_pair = replier.Socket().GetLastSocketError();
          event_handler_->OnError("Connecting to server failed with error code: " +
                                  std::to_string(error_ret_pair.first) +
                                  " and message: " + std::to_string(error_ret_pair.second));
          return true;
        });
  } else {
    replier_socket_ =
        std::make_unique<os::core::udp::communication::Replier>(replier_address.value());
  }

  subscriber_socket_ = std::make_unique<os::core::udp::communication::Subscriber>(
      subscriber_address.value(), interface_address.value(), true);

  SetupGRPCChannel();

  auto start_control_observing = CreateControllingSubscription();
  if (start_control_observing.return_code != ReturnCode::OK) {
    return start_control_observing;
  };

  return SetupUDPChannel();
}

OperationStatus Robot::SetQoSProfile(QoS_Configuration qos_config) {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "SetQoSProfile failed: network connection not initialized.");
  }

  kuka::ecs::v1::SetQoSProfileRequest request;
  kuka::ecs::v1::SetQoSProfileResponse response;
  grpc::ClientContext context;

  request.add_qos_profiles();

  request.mutable_qos_profiles()
      ->at(0)
      .mutable_rt_packet_loss_profile()
      ->set_consequent_lost_packets(qos_config.consecutive_packet_loss_limit);
  request.mutable_qos_profiles()
      ->at(0)
      .mutable_rt_packet_loss_profile()
      ->set_lost_packets_in_timeframe(qos_config.packet_loss_in_timeframe_limit);
  request.mutable_qos_profiles()->at(0).mutable_rt_packet_loss_profile()->set_timeframe_ms(
      qos_config.timeframe_ms);

  return OperationStatus(stub_->SetQoSProfile(&context, request, &response));
}

OperationStatus Robot::StartControlling() {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "StartControlling failed: network connection not initialized.");
  }
  kuka::ecs::v1::OpenControlChannelRequest request;
  kuka::ecs::v1::OpenControlChannelResponse response;
  grpc::ClientContext context;

  auto control_mode = kuka::motion::external::ExternalControlMode(config_.initial_control_mode);
  request.set_ip_address(config_.client_ip_address);
  request.set_timeout(config_.connection_timeout);
  request.set_cycle_time(config_.cycle_time);
  request.set_external_control_mode(control_mode);
  control_mode_ = control_mode;
  request.set_is_secure(config_.is_secure);

  OperationStatus op_status(stub_->OpenControlChannel(&context, request, &response));

  if (op_status.return_code == ReturnCode::ERROR) {
    return op_status;
  }

  return event_handler_set_
             ? OperationStatus(ReturnCode::OK)
             : OperationStatus(ReturnCode::WARN,
                               "Warning: StartControlling called with default event handler.");
}

OperationStatus Robot::StopControlling() { return SendControlSignal(true); }

OperationStatus Robot::CreateControllingSubscription() {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "ObserveControlState failed: network connection not initialized.");
  }

  observer_context_ = std::make_unique<grpc::ClientContext>();

  observer_thread_ = std::thread([&]() {
    kuka::ecs::v1::ObserveControlStateRequest request;
    kuka::ecs::v1::CommandState response;

    std::unique_ptr<grpc::ClientReader<kuka::ecs::v1::CommandState>> reader(
        stub_->ObserveControlState(observer_context_.get(), request));

    while (reader->Read(&response)) {
      std::lock_guard<std::mutex> lck(event_handler_mutex_);
      switch (static_cast<int>(response.event())) {
        case kuka::ecs::v1::CommandEvent::SAMPLING:
          event_handler_->OnSampling();
          {
            std::lock_guard<std::mutex> lck(cv_mutex_);
            cv_flag_ = true;
            control_mode_changed_.notify_all();
          }
          break;
        case kuka::ecs::v1::CommandEvent::CONTROL_MODE_SWITCH:
          event_handler_->OnControlModeSwitch(response.message());
          break;
        case kuka::ecs::v1::CommandEvent::STOPPED:
          event_handler_->OnStopped(response.message());
          break;
        case kuka::ecs::v1::CommandEvent::ERROR:
          event_handler_->OnError(response.message());
          break;
        default:
          break;
      }
    }
  });

  return OperationStatus(ReturnCode::OK);
}

OperationStatus Robot::CancelControllingSubscription() {
  if (!IsSubscribedToControlling()) {
    return OperationStatus(ReturnCode::ERROR,
                           "StopObservingControlState failed: observing is not in progress.");
  }

  observer_context_->TryCancel();
  observer_thread_.join();

  return OperationStatus(ReturnCode::OK);
}

OperationStatus Robot::StartMonitoring() {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "StartMonitoring failed: network connection not initialized.");
  }

  kuka::ecs::v1::StartMonitoringRequest request;
  kuka::ecs::v1::StartMonitoringResponse response;
  grpc::ClientContext context;

  return OperationStatus(stub_->StartMonitoring(&context, request, &response));
}

OperationStatus Robot::CreateMonitoringSubscription(
    std::function<void(BaseMotionState&)> handle_motion_states_) {
  if (IsSubscribedToMonitoring()) {
    return OperationStatus(ReturnCode::WARN,
                           "Subscribe failed: already subscribed to motion states.");
  }

  stop_monitoring_ = false;

  monitoring_thread_ = std::thread([&]() {
    MotionState internal_motion_state(config_.dof);

    ArenaWrapper<kuka::ecs::v1::MotionStateExternal> monitoring_arena;

    while (!stop_monitoring_) {
      if (subscriber_socket_->WaitForAndReceive(
              std::chrono::milliseconds(config_.monitoring_timeout)) ==
          os::core::udp::communication::Socket::ErrorCode::kSuccess) {
        auto received_msg = subscriber_socket_->GetMessage();

        if (monitoring_arena.ParseFromArray(received_msg.first, received_msg.second)) {
          internal_motion_state = std::move(*monitoring_arena.GetMessage());
          handle_motion_states_(internal_motion_state);
        }
      }
    }
  });

  return OperationStatus(ReturnCode::OK);
}

OperationStatus Robot::StopMonitoring() {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "StopMonitoring failed: network connection not initialized.");
  }

  kuka::ecs::v1::StopMonitoringRequest request;
  kuka::ecs::v1::StopMonitoringResponse response;
  grpc::ClientContext context;

  return OperationStatus(stub_->StopMonitoring(&context, request, &response));
}

OperationStatus Robot::CancelMonitoringSubscription() {
  if (!IsSubscribedToMonitoring()) {
    return OperationStatus(ReturnCode::ERROR,
                           "Unsubscribe failed: not subscribed to motion states.");
  }

  stop_monitoring_ = true;
  if (monitoring_thread_.joinable()) {
    monitoring_thread_.join();
  }

  return OperationStatus(ReturnCode::OK);
}

OperationStatus Robot::SendControlSignal() { return SendControlSignal(false); }

OperationStatus Robot::SendControlSignal(bool stop_control) {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "SendControlSignal failed: network connection not initialized.");
  }

  kuka::ecs::v1::ControlSignalExternal* protobuf_control_signal =
      control_signal_.CreateProtobufControlSignal(last_ipoc_, control_mode_, stop_control);
  if (protobuf_control_signal->has_control_signal() == false && !stop_control) {
    return OperationStatus(ReturnCode::ERROR,
                           "SendControlSignal failed: please fill out the control signal first.");
  }

  std::size_t size = protobuf_control_signal->ByteSizeLong();
  uint8_t encode_buffer[4096];

  if (!controlling_arena_.SerializeExistingMessageToArray(encode_buffer, size)) {
    return OperationStatus(ReturnCode::ERROR,
                           "SendControlSignal failed: failed to serialize to array.");
  }

  return OperationStatus(replier_socket_->SendReply(encode_buffer, size));
}

OperationStatus Robot::ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) {
  if (Uninitialized()) {
    return OperationStatus(ReturnCode::ERROR,
                           "ReceiveMotionState failed: network connection not initialized.");
  }

  auto recv_ret = replier_socket_->ReceiveRequestOrTimeout(receive_request_timeout);
  if (recv_ret == os::core::udp::communication::Socket::ErrorCode::kSuccess) {
    auto req_message = replier_socket_->GetRequestMessage();

    if (!monitoring_arena_.ParseFromArray(req_message.first, req_message.second)) {
      recv_ret = os::core::udp::communication::Socket::ErrorCode::kError;
    } else {
      last_ipoc_ = monitoring_arena_.GetMessage()->header().ipoc();
      last_motion_state_ = std::move(*monitoring_arena_.GetMessage());
    }
  }

  return OperationStatus(recv_ret);
}

BaseControlSignal& Robot::GetControlSignal() { return control_signal_; };
BaseMotionState& Robot::GetLastMotionState() { return last_motion_state_; };

OperationStatus Robot::SwitchControlMode(ControlMode control_mode) {
  /*
  using namespace std::chrono_literals;
  {
    std::lock_guard<std::mutex> lck(cv_mutex_);
    cv_flag_ = false;
  }
  */
  control_mode_ = kuka::motion::external::ExternalControlMode(control_mode);
  return SendControlSignal();
  //OperationStatus op_status = SendControlSignal();

  /*
  if (op_status.return_code != ReturnCode::OK) {
    return op_status;
  }
  std::unique_lock<std::mutex> lck(cv_mutex_);
  bool result = control_mode_changed_.wait_for(lck, 2s, [this] { return cv_flag_ == true; });

  return result ? OperationStatus(ReturnCode::OK)
                : OperationStatus(ReturnCode::ERROR,
                                  "SwitchControlMode failed: control mode switch failed or did not "
                                  "finish in time.");
                                  */
}

bool Robot::IsSubscribedToMonitoring() { return monitoring_thread_.joinable(); }
bool Robot::IsSubscribedToControlling() {
  return observer_context_ != nullptr && observer_thread_.joinable();
}

OperationStatus Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  if (event_handler == nullptr) {
    return OperationStatus(ReturnCode::ERROR,
                           "RegisterEventHandler failed: please provide a valid pointer.");
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return OperationStatus(ReturnCode::OK);
};

void Robot::Reset() {
  if (IsSubscribedToMonitoring()) CancelMonitoringSubscription();
  if (IsSubscribedToControlling()) CancelControllingSubscription();
  stub_.reset();
  replier_socket_.reset();
  subscriber_socket_.reset();
}

bool Robot::Uninitialized() {
  return stub_ == nullptr || replier_socket_ == nullptr || subscriber_socket_ == nullptr;
}

void Robot::SetupGRPCChannel() {
  stub_ = kuka::ecs::v1::ExternalControlService::NewStub(
      grpc::CreateChannel(config_.koni_ip_address + ":" + std::to_string(config_.ecs_grpc_port),
                          grpc::InsecureChannelCredentials()));
}

OperationStatus Robot::SetupUDPChannel() {
  auto replier_setup = OperationStatus(replier_socket_->Setup());

  if (replier_setup.return_code == ReturnCode::OK) {
    return OperationStatus(subscriber_socket_->Setup());
  }

  return replier_setup;
}
};  // namespace kuka::external::control::iiqka
