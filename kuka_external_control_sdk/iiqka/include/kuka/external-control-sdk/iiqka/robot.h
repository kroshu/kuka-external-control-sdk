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

#ifndef EXTERNAL_CONTROL_SDK__IIQKA_ROBOT_INTERFACE_H_
#define EXTERNAL_CONTROL_SDK__IIQKA_ROBOT_INTERFACE_H_

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <variant>
#include <vector>

#include "arena_wrapper.h"
#include "configuration.h"
#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/replier.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/secure_replier.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"
#include "message_builder.h"
#include "proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "proto-api/motion-services-ecs/motion_services_ecs.grpc.pb.h"
#include "proto-api/motion-services-ecs/motion_state_external.pb.h"

namespace kuka::external::control::iiqka {

class Robot : public IRobot {
  // Special methods
public:
  Robot(Configuration);
  virtual ~Robot() override { Reset(); }

  // delete copy constructor and copy assignment operator
  Robot(const Robot &) = delete;
  Robot &operator=(const Robot &) = delete;

  // delete move constructor and move assignment operator
  Robot(Robot &&) = delete;
  Robot &operator=(Robot &&) = delete;

  // Interface implementation
public:
  virtual Status Setup() override;

  /** Start controlling with the specified control mode
   *  At the present, the following control modes are supported:
   *  1 - Joint position control
   *  2 - Joint impedance control
   *  4 - Joint torque control
   */
  virtual Status StartControlling(ControlMode control_mode) override;
  virtual Status StartMonitoring() override;

  virtual Status StopControlling() override;
  virtual Status StopMonitoring() override;

  virtual Status CreateMonitoringSubscription(
      std::function<void(BaseMotionState &)>) override;
  virtual Status CancelMonitoringSubscription() override;

  virtual bool HasMonitoringSubscription() override;

  virtual Status SendControlSignal() override;
  virtual Status ReceiveMotionState(
      std::chrono::milliseconds receive_request_timeout) override;

  virtual std::shared_ptr<BaseControlSignal> GetControlSignal() override;
  virtual std::shared_ptr<BaseMotionState> GetLastMotionState() override;

  virtual Status SwitchControlMode(ControlMode control_mode) override;
  virtual Status
  RegisterEventHandler(std::unique_ptr<EventHandler> &&event_handler) override;

  // ECI-specific features
public:
  Status SetQoSProfile(QoS_Configuration);
  // This might have to be moved to IRobot
  Status GetSignalConfiguration(
      std::shared_ptr<std::vector<Signal_Configuration>> &shared_signal_config);

  // Members used for keeping track of the state.
private:
  void Reset();
  bool Uninitialized();

  Status ConvertStatus(grpc::Status);
  Status ConvertStatus(os::core::udp::communication::Socket::ErrorCode);

  virtual bool HasControllingSubscription();
  Status CreateControllingSubscription();
  Status CancelControllingSubscription();

  std::unique_ptr<kuka::ecs::v1::ExternalControlService::Stub> stub_{nullptr};

  std::unique_ptr<os::core::udp::communication::Replier> replier_socket_{
      nullptr};
  std::unique_ptr<os::core::udp::communication::Subscriber> subscriber_socket_{
      nullptr};

  // Members and methods used for implementing observer functionality.
private:
  std::unique_ptr<grpc::ClientContext> observer_context_;
  std::thread observer_thread_;
  std::thread monitoring_thread_;
  std::unique_ptr<EventHandler> event_handler_;
  bool event_handler_set_ = false;

  // Members and helper methods for implementing control.
private:
  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> controlling_arena_;
  ArenaWrapper<kuka::ecs::v1::MotionStateExternal> monitoring_arena_;

  uint32_t last_ipoc_;

  std::shared_ptr<ControlSignal> control_signal_;
  std::shared_ptr<MotionState> last_motion_state_;
  kuka::motion::external::ExternalControlMode control_mode_{
      kuka::motion::external::ExternalControlMode::
          EXTERNAL_CONTROL_MODE_UNSPECIFIED};
  std::atomic<bool> stop_monitoring_;
  bool stop_flag_;
  std::mutex event_handler_mutex_;

  // Members and methods necessary for network configuration and error handling.
private:
  Configuration config_;
  void SetupGRPCChannel();
  Status SetupUDPChannel();

  const int kStopRecvTimeout{6};

  // Members and methods necessary for signal hadling
  std::shared_ptr<std::vector<Signal_Configuration>> signal_config_list_ptr_{
      nullptr};
};

} // namespace kuka::external::control::iiqka
#endif // EXTERNAL_CONTROL_SDK__IIQKA_ROBOT_INTERFACE_H_
