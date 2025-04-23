// Copyright 2025 KUKA Hungaria Kft.
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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_ROBOT_INTERFACE_H_
#define KUKA_EXTERNAL_CONTROL__KSS_ROBOT_INTERFACE_H_

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <variant>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/message_builder.h"
#include "kuka/external-control-sdk/kss/rsi/endpoint.h"

namespace kuka::external::control::kss {

class Robot : public IRobot {
  // Special methods
 public:
  Robot(Configuration);

  // Interface implementation
 public:
  virtual Status Setup() override;

  virtual Status StartControlling(kuka::external::control::ControlMode) override;
  virtual Status StartMonitoring() override;

  virtual Status StopControlling() override;
  virtual Status StopMonitoring() override;

  virtual Status CreateMonitoringSubscription(std::function<void(BaseMotionState&)>) override;
  virtual Status CancelMonitoringSubscription() override;

  virtual bool HasMonitoringSubscription() override;

  virtual Status SendControlSignal() override;
  virtual Status ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) override;

  BaseControlSignal& GetControlSignal() override;
  BaseMotionState& GetLastMotionState() override;

  // TODO add to documentation that other commands could come in between the Stop and Start call
  // here, also evaluate dispatcher mode
  virtual Status SwitchControlMode(ControlMode control_mode) override;
  virtual Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) override;

 private:
  std::unique_ptr<IRobot> installed_interface_ = nullptr;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_ROBOT_INTERFACE_H_
