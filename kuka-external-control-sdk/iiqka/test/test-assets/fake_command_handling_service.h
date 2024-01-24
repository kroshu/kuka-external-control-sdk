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
#include "iiqka/proto-api/motion-services-ecs/motion_services_ecs.grpc.pb.h"
#include "test-assets/nanopb/control_signal_external.pb.h"
#include "test-assets/nanopb/motion_state_external.pb.h"
#include "test-assets/nanopb/pb.h"
#include "test-assets/nanopb/pb_decode.h"
#include "test-assets/nanopb/pb_encode.h"
#include "test-assets/os-core-udp-communication/publisher.h"
#include "test-assets/os-core-udp-communication/requester.h"

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
  void Teleport(kuka_ecs_v1_ControlSignalExternal& control_signal,
                kuka_ecs_v1_MotionStateExternal& motion_state) {
    if (control_signal.has_header) {
      motion_state.has_header = true;
      motion_state.header = control_signal.header;
    }

    if (control_signal.has_control_signal) {
      motion_state.has_motion_state = true;
      motion_state.motion_state.control_mode = control_signal.control_signal.control_mode;

      if (control_signal.control_signal.has_joint_command) {
        motion_state.motion_state.has_measured_positions = true;
        motion_state.motion_state.measured_positions.values_count =
            control_signal.control_signal.joint_command.values_count;

        for (int i = 0; i < control_signal.control_signal.joint_command.values_count; ++i) {
          motion_state.motion_state.measured_positions.values[i] =
              control_signal.control_signal.joint_command.values[i];
        }
      }

      if (control_signal.control_signal.has_joint_torque_command) {
        motion_state.motion_state.has_measured_torques = true;
        motion_state.motion_state.measured_torques.values_count =
            control_signal.control_signal.joint_torque_command.values_count;

        for (int i = 0; i < control_signal.control_signal.joint_torque_command.values_count; ++i) {
          motion_state.motion_state.measured_torques.values[i] =
              control_signal.control_signal.joint_torque_command.values[i];
        }
      }

      if (control_signal.control_signal.has_joint_velocity_command) {
        motion_state.motion_state.has_measured_velocities = true;
        motion_state.motion_state.measured_velocities.values_count =
            control_signal.control_signal.joint_velocity_command.values_count;

        for (int i = 0; i < control_signal.control_signal.joint_velocity_command.values_count;
             ++i) {
          motion_state.motion_state.measured_velocities.values[i] =
              control_signal.control_signal.joint_velocity_command.values[i];
        }
      }

      motion_state.motion_state.ipo_stopped = control_signal.control_signal.stop_ipo;
    }
  }

  int Encode(const void* message, const pb_msgdesc_t* fields, uint8_t* buffer, size_t buffer_size,
             const char** error_message) {
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);
    bool success = pb_encode(&stream, fields, message);
    if (!success && error_message != nullptr) {
      *error_message = PB_GET_ERROR(&stream);
    }
    return success ? stream.bytes_written : -1;
  }

  bool Decode(const uint8_t* buffer, size_t buffer_size, void* message, const pb_msgdesc_t* fields,
              const char** error_message) {
    pb_istream_t stream = pb_istream_from_buffer(buffer, buffer_size);
    bool success = pb_decode(&stream, fields, message);
    if (!success && error_message != nullptr) {
      *error_message = PB_GET_ERROR(&stream);
    }
    return success;
  }

  std::unique_ptr<os::core::udp::communication::Publisher> publisher_{nullptr};

  std::unique_ptr<grpc::Server> server_;
  std::thread grpc_server_wait_;
  std::thread monitoring_thread_;
  std::thread controlling_thread_;
  std::atomic<bool> monitoring_active_{false};
  std::atomic<bool> controlling_active_{false};

  kuka_ecs_v1_ControlSignalExternal prev_control_signal_external_ =
      kuka_ecs_v1_ControlSignalExternal_init_default;

  kuka_ecs_v1_MotionStateExternal motion_state_external_ =
      kuka_ecs_v1_MotionStateExternal_init_default;

  const uint32_t kMaxConsequentLostPackets = 5;
  const uint32_t kMaxTimeFrame = 3600000;  // 1 hour
  // Ratio: in 1000ms, max 1000/40 = 25 packet losses are allowed
  const uint32_t kMaxPacketLossRatio = 40;
  const uint32_t kMaxLostPackets = 25;  // Using max ratio for 1 second
  bool valid_profile_ = true;
};
}  // namespace kuka::external::control::test

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_FAKE_COMMAND_HANDLING_SERVICE_H_
