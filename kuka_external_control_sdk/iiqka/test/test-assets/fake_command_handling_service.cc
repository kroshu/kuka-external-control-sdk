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

#include "fake_command_handling_service.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include <thread>

namespace kuka::external::control::test
{

FakeCommandHandlingService::~FakeCommandHandlingService()
{
  monitoring_active_ = false;

  if (monitoring_thread_.joinable())
  {
    monitoring_thread_.join();
  }

  controlling_active_ = false;

  if (controlling_thread_.joinable())
  {
    controlling_thread_.join();
  }

  server_->Shutdown();
}

void FakeCommandHandlingService::Setup(const std::string & service_ip)
{
  grpc::ServerBuilder builder;
  builder.AddListeningPort(service_ip + ":49335", grpc::InsecureServerCredentials());
  builder.RegisterService(this);
  server_ = builder.BuildAndStart();

  publisher_ = std::make_unique<os::core::udp::communication::Publisher>(
    os::core::udp::communication::SocketAddress("239.255.123.250", 44446),
    os::core::udp::communication::SocketAddress(service_ip), true);
  if (publisher_->Setup() != os::core::udp::communication::Publisher::ErrorCode::kSuccess)
  {
    exit(1);
  }

  for (int i = 0; i < 6; ++i)
  {
    motion_state_external_.mutable_motion_state()->mutable_measured_positions()->add_values(0.0);
  }

  for (int i = 0; i < 6; ++i)
  {
    motion_state_external_.mutable_motion_state()->mutable_measured_torques()->add_values(12.0);
  }

  for (int i = 0; i < 6; ++i)
  {
    prev_control_signal_external_.mutable_control_signal()
      ->mutable_joint_attributes()
      ->add_stiffness(30.0);
    prev_control_signal_external_.mutable_control_signal()->mutable_joint_attributes()->add_damping(
      0.7);
  }
}

::grpc::Status FakeCommandHandlingService::OpenControlChannel(
  ::grpc::ServerContext * context, const ::kuka::ecs::v1::OpenControlChannelRequest * request,
  ::kuka::ecs::v1::OpenControlChannelResponse * response)
{
  if (controlling_active_)
  {
    return ::grpc::Status(
      ::grpc::StatusCode::FAILED_PRECONDITION,
      "OpenControlChannel failed: external control is already active");
  }

  if (!valid_profile_)
  {
    return ::grpc::Status(
      ::grpc::StatusCode::FAILED_PRECONDITION,
      "OpenControlChannel failed: RTPacketLossProfile is not valid");
  }

  const std::string ip_address = request->ip_address();

  controlling_thread_ = std::thread(
    [=]()
    {
      auto requester = std::make_unique<os::core::udp::communication::Requester>(
        os::core::udp::communication::SocketAddress("127.0.0.3", 44445),
        os::core::udp::communication::SocketAddress(ip_address, 44444));
      controlling_active_ =
        requester->Setup() == os::core::udp::communication::Publisher::ErrorCode::kSuccess;

      while (controlling_active_)
      {
        uint8_t out_buff_arr[3072] = {0};

        if (!motion_state_external_.SerializeToArray(
              out_buff_arr, motion_state_external_.ByteSizeLong()))
        {
          return;
        }

        requester->SendRequest(out_buff_arr, motion_state_external_.ByteSizeLong());

        if (
          requester->ReceiveReplyOrTimeout(std::chrono::seconds(6)) ==
          os::core::udp::communication::Socket::ErrorCode::kSuccess)
        {
          auto arrival_time = std::chrono::system_clock::now();
          auto reply_message = requester->GetReplyMessage();

          kuka::ecs::v1::ControlSignalExternal incoming_control_signal;
          if (!incoming_control_signal.ParseFromArray(reply_message.first, reply_message.second))
          {
            return;
          }

          Teleport(incoming_control_signal, motion_state_external_);

          if (incoming_control_signal.control_signal().stop_ipo() == true)
          {
            controlling_active_ = false;
          }

          std::this_thread::sleep_until(arrival_time + std::chrono::milliseconds(1));
        }
        else
        {
          controlling_active_ = false;
        }
      }
    });

  return ::grpc::Status::OK;
}

::grpc::Status FakeCommandHandlingService::StartMonitoring(
  ::grpc::ServerContext * context, const ::kuka::ecs::v1::StartMonitoringRequest *,
  ::kuka::ecs::v1::StartMonitoringResponse *)
{
  if (controlling_active_)
  {
    return ::grpc::Status(
      ::grpc::StatusCode::FAILED_PRECONDITION,
      "External controlling is active, cannot start monitoring");
  }

  if (!monitoring_active_)
  {
    monitoring_active_ = true;

    monitoring_thread_ = std::thread(
      [&]()
      {
        while (monitoring_active_)
        {
          uint8_t out_buff_arr[3072] = {0};

          if (!motion_state_external_.SerializeToArray(
                out_buff_arr, motion_state_external_.ByteSizeLong()))
          {
            return;
          }
          publisher_->Send(out_buff_arr, motion_state_external_.ByteSizeLong());
          std::this_thread::sleep_for(std::chrono::milliseconds(4));
        }
      });
  }

  return ::grpc::Status::OK;
}

::grpc::Status FakeCommandHandlingService::StopMonitoring(
  ::grpc::ServerContext * context, const ::kuka::ecs::v1::StopMonitoringRequest *,
  ::kuka::ecs::v1::StopMonitoringResponse *)
{
  if (!monitoring_active_)
  {
    return ::grpc::Status(
      ::grpc::StatusCode::FAILED_PRECONDITION,
      "Stop monitoring called while monitoring was inactive.");
  }
  monitoring_active_ = false;
  if (monitoring_thread_.joinable())
  {
    monitoring_thread_.join();
  }
  return ::grpc::Status::OK;
};

::grpc::Status FakeCommandHandlingService::ObserveControlState(
  ::grpc::ServerContext * context, const ::kuka::ecs::v1::ObserveControlStateRequest * request,
  ::grpc::ServerWriter<::kuka::ecs::v1::CommandState> * writer)
{
  return ::grpc::Status::OK;
};

::grpc::Status FakeCommandHandlingService::SetQoSProfile(
  ::grpc::ServerContext * /* context */, const ::kuka::ecs::v1::SetQoSProfileRequest * request,
  ::kuka::ecs::v1::SetQoSProfileResponse *)
{
  if (controlling_active_)
  {
    return ::grpc::Status(
      ::grpc::StatusCode::FAILED_PRECONDITION,
      "Setting QoS profile failed: control is already active");
  }

  valid_profile_ = false;
  if (request->qos_profiles()[0].has_rt_packet_loss_profile())
  {
    auto profile = request->qos_profiles()[0].rt_packet_loss_profile();

    if (profile.consequent_lost_packets() > kMaxConsequentLostPackets)
    {
      return ::grpc::Status(
        ::grpc::StatusCode::FAILED_PRECONDITION,
        "OpenControlChannel failed: RTPacketLossProfile is not valid - "
        "consequent lost packets limit exceeded");
    }

    if (profile.timeframe_ms() > kMaxTimeFrame)
    {
      return ::grpc::Status(
        ::grpc::StatusCode::FAILED_PRECONDITION,
        "OpenControlChannel failed: RTPacketLossProfile is not valid - "
        "timeframe limit exceeded");
    }

    if (
      static_cast<uint32_t>(profile.timeframe_ms() / profile.lost_packets_in_timeframe()) <
      kMaxPacketLossRatio)
    {
      return ::grpc::Status(
        ::grpc::StatusCode::FAILED_PRECONDITION,
        "OpenControlChannel failed: RTPacketLossProfile is not valid - packet "
        "loss ratio limit exceeded");
    }

    if (profile.lost_packets_in_timeframe() > kMaxLostPackets)
    {
      return ::grpc::Status(
        ::grpc::StatusCode::FAILED_PRECONDITION,
        "OpenControlChannel failed: RTPacketLossProfile is not valid - lost "
        "packets limit exceeded - a smaller timeframe should be used! (Hint: use "
        "a smaller timeframe and the same ratio)");
    }
  }
  valid_profile_ = true;
  return ::grpc::Status::OK;
}
}  // namespace kuka::external::control::test
