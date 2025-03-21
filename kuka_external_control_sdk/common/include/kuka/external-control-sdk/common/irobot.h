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

#ifndef KUKA_EXTERNAL_CONTROL__I_ROBOT_H_
#define KUKA_EXTERNAL_CONTROL__I_ROBOT_H_

#include <chrono>
#include <functional>
#include <memory>
#include <utility>

#include "message_builder.h"
#include "status.h"

namespace kuka::external::control {

struct InitializationData {
  std::string semantic_version;
  int64_t ipoc;
  int8_t num_axes;
  int8_t num_external_axes;
  std::string model_name;
  std::vector<std::string> axis_type;
  std::vector<int16_t> ratio_numerator;
  std::vector<int16_t> ratio_denominator;
  std::vector<int16_t> max_rpm;
};

class EventHandler {
 public:
  virtual ~EventHandler() = default;

  virtual void OnSampling() {}
  virtual void OnControlModeSwitch(const std::string& reason) {}
  virtual void OnStopped(const std::string& reason) {}
  virtual void OnError(const std::string& reason) {}
  virtual void OnConnected(const InitializationData& init_data) {}
};

enum class ControlMode {
  UNSPECIFIED = 0,
  JOINT_POSITION_CONTROL = 1,
  JOINT_IMPEDANCE_CONTROL = 2,
  JOINT_VELOCITY_CONTROL = 3,
  JOINT_TORQUE_CONTROL = 4,
  CARTESIAN_POSITION_CONTROL = 5,
  CARTESIAN_IMPEDANCE_CONTROL = 6,
  CARTESIAN_VELOCITY_CONTROL = 7,
  WRENCH_CONTROL = 8
};

class IRobot {
 public:
  virtual ~IRobot() = default;

  virtual Status Setup() = 0;

  virtual Status StartControlling(ControlMode control_mode) = 0;
  virtual Status StartMonitoring() = 0;

  virtual Status CreateMonitoringSubscription(std::function<void(BaseMotionState&)>) = 0;
  virtual Status CancelMonitoringSubscription() = 0;
  virtual bool HasMonitoringSubscription() = 0;

  virtual Status StopControlling() = 0;
  virtual Status StopMonitoring() = 0;

  virtual Status SendControlSignal() = 0;
  virtual Status ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) = 0;

  virtual BaseControlSignal& GetControlSignal() = 0;
  virtual BaseMotionState& GetLastMotionState() = 0;

  virtual Status SwitchControlMode(ControlMode control_mode) = 0;
  virtual Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) = 0;
};

}  // namespace kuka::external::control

#endif  // KUKA_EXTERNAL_CONTROL__I_ROBOT_H_
