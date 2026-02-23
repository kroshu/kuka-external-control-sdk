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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_FAKE_COMMAND_HANDLING_SERVICE_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_FAKE_COMMAND_HANDLING_SERVICE_H_

#include <atomic>
#include <memory>
#include <thread>

#include "grpc/grpc.h"
#include "grpcpp/grpcpp.h"
#include "grpcpp/server.h"
#include "grpcpp/server_builder.h"
#include "proto-api/motion-services-ecs/motion_services_ecs.grpc.pb.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/publisher.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/requester.h"
#include "proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "proto-api/motion-services-ecs/motion_state_external.pb.h"

namespace kuka::external::control::test {
class FakeCommandHandlingService : public ::kuka::ecs::v1::ExternalControlService::Service {
 public:
  FakeCommandHandlingService() {}
  ~FakeCommandHandlingService();

  void Setup(const std::string& service_ip);

  virtual ::grpc::Status OpenControlChannel(
      ::grpc::ServerContext* context, const ::kuka::ecs::v1::OpenControlChannelRequest* request,
      ::kuka::ecs::v1::OpenControlChannelResponse* response) override;

  virtual ::grpc::Status StartMonitoring(::grpc::ServerContext* context,
                                         const ::kuka::ecs::v1::StartMonitoringRequest*,
                                         ::kuka::ecs::v1::StartMonitoringResponse*) override;

  virtual ::grpc::Status StopMonitoring(::grpc::ServerContext* context,
                                        const ::kuka::ecs::v1::StopMonitoringRequest*,
                                        ::kuka::ecs::v1::StopMonitoringResponse*) override;

  virtual ::grpc::Status ObserveControlState(
      ::grpc::ServerContext* context, const ::kuka::ecs::v1::ObserveControlStateRequest* request,
      ::grpc::ServerWriter<::kuka::ecs::v1::CommandState>* writer) override;

  virtual ::grpc::Status SetQoSProfile(::grpc::ServerContext* context,
                                       const ::kuka::ecs::v1::SetQoSProfileRequest*,
                                       ::kuka::ecs::v1::SetQoSProfileResponse*) override;

 private:
  void Teleport(kuka::ecs::v1::ControlSignalExternal& control_signal,
                kuka::ecs::v1::MotionStateExternal& motion_state) {
    *(motion_state.mutable_header()) = control_signal.header();
    motion_state.mutable_motion_state()->set_ipo_stopped(control_signal.control_signal().stop_ipo());

    if (control_signal.control_signal().control_mode() == kuka::motion::external::ExternalControlMode::JOINT_POSITION_CONTROL
        || control_signal.control_signal().control_mode() == kuka::motion::external::ExternalControlMode::JOINT_IMPEDANCE_CONTROL) {
      for (int i = 0; i < control_signal.control_signal().joint_command().values_size();
            ++i) {
        motion_state.mutable_motion_state()->mutable_measured_positions()->set_values(i, control_signal.control_signal().joint_command().values(i));
      }
    }

    if (control_signal.control_signal().control_mode() == kuka::motion::external::ExternalControlMode::JOINT_TORQUE_CONTROL) {
      for (int i = 0; i < control_signal.control_signal().joint_torque_command().values_size();
            ++i) {
        // motion_state.mutable_motion_state()->mutable_measured_torques()->set_values(i, control_signal.control_signal().joint_torque_command().values(i));
      }
    }

    if (control_signal.control_signal().control_mode() ==
        kuka::motion::external::ExternalControlMode::JOINT_IMPEDANCE_CONTROL) {
        for (size_t i = 0;
              i < control_signal.control_signal().joint_attributes().stiffness_size(); ++i) {
          if (control_signal.control_signal().joint_attributes().stiffness(i) < 0 ||
              control_signal.control_signal().joint_attributes().stiffness(i) > 2000) {
            control_signal.mutable_control_signal()->mutable_joint_attributes()->set_stiffness(i, prev_control_signal_external_.control_signal().joint_attributes().stiffness(i));
            return;
          }
        }
        for (size_t i = 0;
              i < control_signal.control_signal().joint_attributes().damping_size(); ++i) {
          if (control_signal.control_signal().joint_attributes().damping(i) < 0 ||
              control_signal.control_signal().joint_attributes().damping(i) > 2000) {
            control_signal.mutable_control_signal()->mutable_joint_attributes()->set_damping(i, prev_control_signal_external_.control_signal().joint_attributes().damping(i));
            return;
          }
        }
    }

    *prev_control_signal_external_.mutable_control_signal()->mutable_joint_attributes() = control_signal.control_signal().joint_attributes();
    *prev_control_signal_external_.mutable_control_signal()->mutable_joint_torque_command() = control_signal.control_signal().joint_torque_command();
    *prev_control_signal_external_.mutable_control_signal()->mutable_joint_command() = control_signal.control_signal().joint_command();
  }

  std::unique_ptr<os::core::udp::communication::Publisher> publisher_{nullptr};

  std::unique_ptr<grpc::Server> server_;
  std::thread grpc_server_wait_;
  std::thread monitoring_thread_;
  std::thread controlling_thread_;
  std::atomic<bool> monitoring_active_{false};
  std::atomic<bool> controlling_active_{false};

  kuka::ecs::v1::ControlSignalExternal prev_control_signal_external_;
  kuka::ecs::v1::MotionStateExternal motion_state_external_;
  const uint32_t kMaxConsequentLostPackets = 5;
  const uint32_t kMaxTimeFrame = 3600000;  // 1 hour
  // Ratio: in 1000ms, max 1000/40 = 25 packet losses are allowed
  const uint32_t kMaxPacketLossRatio = 40;
  const uint32_t kMaxLostPackets = 25;  // Using max ratio for 1 second
  bool valid_profile_ = true;
};
}  // namespace kuka::external::control::test

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_FAKE_COMMAND_HANDLING_SERVICE_H_
