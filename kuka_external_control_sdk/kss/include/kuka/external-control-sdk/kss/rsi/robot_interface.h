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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__KSS__RSI__ROBOT_INTERFACE_H_
#define KUKA__EXTERNAL_CONTROL_SDK__KSS__RSI__ROBOT_INTERFACE_H_

#include <functional>
#include <memory>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/initialization_data.h"
#include "kuka/external-control-sdk/kss/message_builder.h"
#include "kuka/external-control-sdk/kss/rsi/endpoint.h"
#include "kuka/external-control-sdk/kss/status_update.h"

namespace kuka::external::control::kss::rsi
{

class Robot : public IRobot
{
  // Special methods
public:
  explicit Robot(Configuration);

  // Interface implementation
public:
  Status Setup() override;

  Status StartControlling(kuka::external::control::ControlMode) override;
  Status StartMonitoring() override;

  Status StopControlling() override;
  Status StopMonitoring() override;

  Status CreateMonitoringSubscription(std::function<void(BaseMotionState &)>) override;
  Status CancelMonitoringSubscription() override;

  bool HasMonitoringSubscription() override;

  Status SendControlSignal() override;
  Status ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) override;

  BaseControlSignal & GetControlSignal() override;
  BaseMotionState & GetLastMotionState() override;

  // TODO(Svastits) add to documentation that other commands could come in between the Stop and
  // Start call here, also evaluate dispatcher mode
  Status SwitchControlMode(ControlMode control_mode) override;
  Status RegisterEventHandler(std::unique_ptr<EventHandler> && event_handler) override;

  // Extension methods not supported by plain RSI
  virtual Status CancelRsiProgram() { return {ReturnCode::UNSUPPORTED, error_text}; }
  virtual Status TurnOnDrives() { return {ReturnCode::UNSUPPORTED, error_text}; }
  virtual Status TurnOffDrives() { return {ReturnCode::UNSUPPORTED, error_text}; }
  virtual Status SetCycleTime(CycleTime cycle_time)
  {
    return {ReturnCode::UNSUPPORTED, error_text};
  }
  virtual Status RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension> && extension)
  {
    return {ReturnCode::UNSUPPORTED, error_text};
  }
  Status RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler> && handler)
  {
    return {ReturnCode::UNSUPPORTED, error_text};
  }

protected:
  MotionState last_motion_state_;
  MotionState initial_motion_state_;
  ControlSignal control_signal_;

  Configuration config_;
  int last_ipoc_ = 0;
  static constexpr int kStopReceiveTimeoutMs = 40;

  Endpoint endpoint_;

  // Members and methods for implementing control
private:
  Status UpdateMotionState(std::string_view xml_str);

private:
  static constexpr char error_text[] = "Not supported by plain RSI";
};

}  // namespace kuka::external::control::kss::rsi

#endif  // KUKA__EXTERNAL_CONTROL_SDK__KSS__RSI__ROBOT_INTERFACE_H_
