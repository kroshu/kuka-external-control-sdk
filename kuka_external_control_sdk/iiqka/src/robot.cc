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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/secure_socket.h"
#include "proto-api/motion-services-ecs/control_signal_external.pb.h"

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

  event_handler_ = std::make_unique<EventHandler>();
}

Status Robot::Setup() {
  Reset();
  auto replier_address = os::core::udp::communication::SocketAddress::SafeConstruct(
      config_.client_ip_address.c_str(), config_.udp_replier_port);

  auto subscriber_address = os::core::udp::communication::SocketAddress::SafeConstruct(
      config_.udp_subscriber_multicast_address.c_str(), config_.udp_subscriber_port);

  auto interface_address =
      os::core::udp::communication::SocketAddress::SafeConstruct(config_.client_ip_address);

  if (!replier_address || !subscriber_address || !interface_address) {
    return Status(ReturnCode::ERROR, "Invalid IP in configuration");
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

Status Robot::SetQoSProfile(QoS_Configuration qos_config) {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR, "SetQoSProfile failed: network connection not initialized.");
  }

  kuka::ecs::v1::SetQoSProfileRequest request;
  kuka::ecs::v1::SetQoSProfileResponse response;
  grpc::ClientContext context;

  request.add_qos_profiles();

  request.mutable_qos_profiles(0)->mutable_rt_packet_loss_profile()->set_consequent_lost_packets(
      qos_config.consecutive_packet_loss_limit);
  request.mutable_qos_profiles(0)->mutable_rt_packet_loss_profile()->set_lost_packets_in_timeframe(
      qos_config.packet_loss_in_timeframe_limit);
  request.mutable_qos_profiles(0)->mutable_rt_packet_loss_profile()->set_timeframe_ms(
      qos_config.timeframe_ms);

  return ConvertStatus(stub_->SetQoSProfile(&context, request, &response));
}

Status Robot::StartControlling(ControlMode control_mode) {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR,
                  "StartControlling failed: network connection not initialized.");
  }
  kuka::ecs::v1::OpenControlChannelRequest request;
  kuka::ecs::v1::OpenControlChannelResponse response;
  grpc::ClientContext context;

  request.set_ip_address(config_.client_ip_address);
  request.set_timeout(config_.connection_timeout);
  request.set_cycle_time(config_.cycle_time);
  control_mode_ = kuka::motion::external::ExternalControlMode(control_mode);
  request.set_external_control_mode(control_mode_);
  request.set_is_secure(config_.is_secure);

  stop_flag_ = false;

  Status op_status = ConvertStatus(stub_->OpenControlChannel(&context, request, &response));

  if (op_status.return_code == ReturnCode::ERROR) {
    return op_status;
  }

  return event_handler_set_
             ? Status(ReturnCode::OK)
             : Status(ReturnCode::WARN,
                      "Warning: StartControlling called with default event handler.");
}

Status Robot::StopControlling() {
  stop_flag_ = true;
  if (!replier_socket_->IsRequestActive()) {
    // Wait for next motion state, if no request is active to be able to send valid stop signal
    // Timeout is default 6 ms
    if (this->ReceiveMotionState(std::chrono::milliseconds(kStopRecvTimeout)).return_code !=
        kuka::external::control::ReturnCode::OK)
      return Status(ReturnCode::ERROR, "Failed to receive before sending stop signal");
  }
  return SendControlSignal();
}

Status Robot::CreateControllingSubscription() {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR,
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

  return Status(ReturnCode::OK);
}

Status Robot::CancelControllingSubscription() {
  if (!HasControllingSubscription()) {
    return Status(ReturnCode::ERROR,
                  "StopObservingControlState failed: observing is not in progress.");
  }

  observer_context_->TryCancel();
  observer_thread_.join();

  return Status(ReturnCode::OK);
}

Status Robot::StartMonitoring() {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR, "StartMonitoring failed: network connection not initialized.");
  }

  kuka::ecs::v1::StartMonitoringRequest request;
  kuka::ecs::v1::StartMonitoringResponse response;
  grpc::ClientContext context;

  return ConvertStatus(stub_->StartMonitoring(&context, request, &response));
}

Status Robot::CreateMonitoringSubscription(
    std::function<void(BaseMotionState&)> handle_motion_states_) {
  if (HasMonitoringSubscription()) {
    return Status(ReturnCode::WARN, "Subscribe failed: already subscribed to motion states.");
  }

  stop_monitoring_ = false;

  monitoring_thread_ = std::thread([=]() {
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

  return Status(ReturnCode::OK);
}

Status Robot::StopMonitoring() {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR, "StopMonitoring failed: network connection not initialized.");
  }

  kuka::ecs::v1::StopMonitoringRequest request;
  kuka::ecs::v1::StopMonitoringResponse response;
  grpc::ClientContext context;

  return ConvertStatus(stub_->StopMonitoring(&context, request, &response));
}

Status Robot::CancelMonitoringSubscription() {
  if (!HasMonitoringSubscription()) {
    return Status(ReturnCode::ERROR, "Unsubscribe failed: not subscribed to motion states.");
  }

  stop_monitoring_ = true;
  if (monitoring_thread_.joinable()) {
    monitoring_thread_.join();
  }

  return Status(ReturnCode::OK);
}

Status Robot::SendControlSignal() {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR,
                  "SendControlSignal failed: network connection not initialized.");
  }

  kuka::ecs::v1::ControlSignalExternal* protobuf_control_signal =
      control_signal_.CreateProtobufControlSignal(last_ipoc_, control_mode_, stop_flag_);
  if (protobuf_control_signal->has_control_signal() == false && !stop_flag_) {
    return Status(ReturnCode::ERROR,
                  "SendControlSignal failed: please fill out the control signal first.");
  }

  std::size_t size = protobuf_control_signal->ByteSizeLong();
  uint8_t encode_buffer[4096];

  if (!controlling_arena_.SerializeExistingMessageToArray(encode_buffer, size)) {
    return Status(ReturnCode::ERROR, "SendControlSignal failed: failed to serialize to array.");
  }

  return ConvertStatus(replier_socket_->SendReply(encode_buffer, size));
}

Status Robot::ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) {
  if (Uninitialized()) {
    return Status(ReturnCode::ERROR,
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

  return ConvertStatus(recv_ret);
}

BaseControlSignal& Robot::GetControlSignal() { return control_signal_; };
BaseMotionState& Robot::GetLastMotionState() { return last_motion_state_; };

Status Robot::SwitchControlMode(ControlMode control_mode) {
  control_mode_ = kuka::motion::external::ExternalControlMode(control_mode);
  return SendControlSignal();
}

bool Robot::HasMonitoringSubscription() { return monitoring_thread_.joinable(); }
bool Robot::HasControllingSubscription() {
  return observer_context_ != nullptr && observer_thread_.joinable();
}

Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  if (event_handler == nullptr) {
    return Status(ReturnCode::ERROR,
                  "RegisterEventHandler failed: please provide a valid pointer.");
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return Status(ReturnCode::OK);
};

void Robot::Reset() {
  if (HasMonitoringSubscription()) CancelMonitoringSubscription();
  if (HasControllingSubscription()) CancelControllingSubscription();
  stub_.reset();
  replier_socket_.reset();
  subscriber_socket_.reset();
}

bool Robot::Uninitialized() {
  return stub_ == nullptr || replier_socket_ == nullptr || subscriber_socket_ == nullptr;
}

Status Robot::ConvertStatus(grpc::Status grpc_status) {
  Status op_status;
  switch (grpc_status.error_code()) {
    case grpc::StatusCode::OK:
      op_status.return_code = ReturnCode::OK;
      break;
    default:
      op_status.return_code = ReturnCode::ERROR;
  }
  strcpy(op_status.message, grpc_status.error_message().c_str());
  return op_status;
}

Status Robot::ConvertStatus(os::core::udp::communication::Socket::ErrorCode code) {
  using namespace os::core::udp::communication;
  Status op_status;

  char errno_msg[256] = "Socket error: ";

  switch (code) {
    case Socket::ErrorCode::kSuccess:
      op_status.return_code = ReturnCode::OK;
      break;
    case Socket::ErrorCode::kTimeout:
      strcpy(op_status.message, "Timeout: operation did not finish in time.");
      op_status.return_code = ReturnCode::TIMEOUT;
      break;
    case Socket::ErrorCode::kSocketError:
      strcpy(op_status.message, strcat(errno_msg, std::strerror(errno)));
      op_status.return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kAlreadyActive:
      strcpy(op_status.message, "Error: socket already active.");
      op_status.return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kNotBound:
      strcpy(op_status.message, "Error: socket not bound.");
      op_status.return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kNotConnected:
      strcpy(op_status.message, "Error: socket not connected.");
      op_status.return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kClosed:
      strcpy(op_status.message, "Error: socket closed.");
      op_status.return_code = ReturnCode::ERROR;
      break;
    default:
      strcpy(op_status.message, "Request - Reply pattern broken.");
      op_status.return_code = ReturnCode::ERROR;
  }

  return op_status;
}

void Robot::SetupGRPCChannel() {
  stub_ = kuka::ecs::v1::ExternalControlService::NewStub(
      grpc::CreateChannel(config_.koni_ip_address + ":" + std::to_string(config_.ecs_grpc_port),
                          grpc::InsecureChannelCredentials()));
}

Status Robot::SetupUDPChannel() {
  auto replier_setup = ConvertStatus(replier_socket_->Setup());

  if (replier_setup.return_code == ReturnCode::OK) {
    return ConvertStatus(subscriber_socket_->Setup());
  }

  return replier_setup;
}
};  // namespace kuka::external::control::iiqka
