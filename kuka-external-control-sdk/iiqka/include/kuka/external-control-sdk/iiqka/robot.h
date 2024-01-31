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

#include "arena_wrapper.h"
#include "configuration.h"
#include "iiqka/proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "iiqka/proto-api/motion-services-ecs/motion_services_ecs.grpc.pb.h"
#include "iiqka/proto-api/motion-services-ecs/motion_state_external.pb.h"
#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/replier.h"
#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/secure_replier.h"
#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/subscriber.h"
#include "message_builder.h"

namespace kuka::external::control::iiqka {

class Robot : public IRobot {
  // Special methods
 public:
  Robot(Configuration);
  virtual ~Robot() override { Reset(); }

  // Interface implementation
 public:
  virtual OperationStatus Setup() override;

  virtual OperationStatus StartControlling() override;
  virtual OperationStatus StartMonitoring() override;

  virtual OperationStatus StopControlling() override;
  virtual OperationStatus StopMonitoring() override;

  virtual OperationStatus CreateMonitoringSubscription(
      std::function<void(BaseMotionState&)>) override;
  virtual OperationStatus CancelMonitoringSubscription() override;

  virtual bool IsSubscribedToMonitoring() override;

  virtual OperationStatus SendControlSignal() override;
  virtual OperationStatus ReceiveMotionState(
      std::chrono::milliseconds receive_request_timeout) override;

  virtual BaseControlSignal& GetControlSignal() override;
  virtual BaseMotionState& GetLastMotionState() override;

  virtual OperationStatus SwitchControlMode(ControlMode control_mode) override;
  virtual OperationStatus RegisterEventHandler(
      std::unique_ptr<EventHandler>&& event_handler) override;

  // ECI-specific features
 public:
  OperationStatus SetQoSProfile(QoS_Configuration);

  // Members used for keeping track of the state.
 private:
  void Reset();
  bool Uninitialized();

  virtual bool IsSubscribedToControlling();
  OperationStatus CreateControllingSubscription();
  OperationStatus CancelControllingSubscription();

  std::unique_ptr<kuka::ecs::v1::ExternalControlService::Stub> stub_{nullptr};

  std::unique_ptr<os::core::udp::communication::Replier> replier_socket_{nullptr};
  std::unique_ptr<os::core::udp::communication::Subscriber> subscriber_socket_{nullptr};

  // Members and methods used for implementing observer functionality.
 private:
  std::unique_ptr<grpc::ClientContext> observer_context_;
  std::thread observer_thread_;
  std::thread monitoring_thread_;
  std::unique_ptr<EventHandler> event_handler_;
  bool event_handler_set_ = false;

  // Members and helper methods for implementing control.
 private:
  OperationStatus SendControlSignal(bool stop_control);

  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> controlling_arena_;
  ArenaWrapper<kuka::ecs::v1::MotionStateExternal> monitoring_arena_;

  int last_ipoc_;

  ControlSignal control_signal_;
  MotionState last_motion_state_;
  kuka::motion::external::ExternalControlMode control_mode_{
      kuka::motion::external::ExternalControlMode::EXTERNAL_CONTROL_MODE_UNSPECIFIED};
  std::atomic<bool> stop_monitoring_;
  std::mutex event_handler_mutex_;

  // Members and methods necessary for network configuration and error handling.
 private:
  Configuration config_;
  void SetupGRPCChannel();
  OperationStatus SetupUDPChannel();
};

}  // namespace kuka::external::control::iiqka
#endif  // EXTERNAL_CONTROL_SDK__IIQKA_ROBOT_INTERFACE_H_
