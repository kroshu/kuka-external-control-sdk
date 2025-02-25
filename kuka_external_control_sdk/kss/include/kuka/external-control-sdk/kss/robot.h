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

#ifndef EXTERNAL_CONTROL_SDK__KSS_ROBOT_INTERFACE_H_
#define EXTERNAL_CONTROL_SDK__KSS_ROBOT_INTERFACE_H_

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <variant>

#include "configuration.h"
#include "eki-rsi/eki_comm_client.h"
#include "eki-rsi/rsi_comm_endpoint.h"
#include "kuka/external-control-sdk/common/irobot.h"
#include "message_builder.h"

namespace kuka::external::control::kss {

class Robot : public IRobot {
  // Special methods
 public:
  Robot(Configuration);

  // Interface implementation
 public:
  virtual Status Setup() override;

  virtual Status StartControlling(
      kuka::external::control::ControlMode) override;  // call EKI service
  virtual Status StartMonitoring() override { return {ReturnCode::ERROR, "Not supported"}; }

  virtual Status StopControlling() override;  // Set stop flag + send
  virtual Status StopMonitoring() override { return {ReturnCode::ERROR, "Not supported"}; }

  virtual Status CreateMonitoringSubscription(std::function<void(BaseMotionState&)>) override {
    return {ReturnCode::ERROR, "Not supported"};
  }
  virtual Status CancelMonitoringSubscription() override {
    return {ReturnCode::ERROR, "Not supported"};
  }

  virtual bool HasMonitoringSubscription() override { return false; }  // Not supported

  // TODO fix alignment of absolute positions <-> corrections
  virtual Status SendControlSignal() override;  // UDP lib
  virtual Status ReceiveMotionState(
      std::chrono::milliseconds receive_request_timeout) override;  // UDP lib

  virtual BaseControlSignal& GetControlSignal()
      override;  // getter, setters inside implement endoding
  virtual BaseMotionState& GetLastMotionState() override;  // xml parsing

  virtual Status SwitchControlMode(
      ControlMode control_mode) override;  // call EKI service, only in inactive
  virtual Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler)
      override;  // EKI response / new EKI client-server with external the service

  // RSI-EKI-specific features
 private:

  // Members used for keeping track of the state.
 private:
  void Reset();
  bool Uninitialized();

  // Members and methods for implementing control
 private:
  RSICommEndpoint rsi_comm_endpoint_;
  Status ParseIncomingXML(std::string_view xml_str);

  ControlSignal control_signal_;
  MotionState last_motion_state_;
  MotionState initial_motion_state_;

  std::string control_signal_format_;
  std::string motion_state_format_;

  int last_ipoc_ = 0;
  bool stop_flag_;
  bool motion_states_initialized_;

  // Members and methods necessary for network configuration and error handling.
 private:
  Configuration config_;
  EKICommClient eki_tcp_channel_;
};

}  // namespace kuka::external::control::kss
#endif  // EXTERNAL_CONTROL_SDK__KSS_ROBOT_INTERFACE_H_
