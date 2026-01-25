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

#include "kuka/external-control-sdk/kss/rsi/robot_interface.h"
#include <cmath>

namespace kuka::external::control::kss::rsi {

Robot::Robot(Configuration config)
    : config_(config),
      last_motion_state_(config.dof, config.gpio_state_configs),
      initial_motion_state_(config.dof, config.gpio_state_configs),
      control_signal_(config.dof, config.gpio_command_configs) {}

Status Robot::Setup() {
  if (!endpoint_.Setup(config_.client_ip, config_.client_port)) {
    return {ReturnCode::ERROR, "Setup of RSI UDP endpoint failed"};
  }

  return {ReturnCode::OK, "Necessary network setup succeeded"};
}

Status Robot::StartControlling(kuka::external::control::ControlMode) {
  return {ReturnCode::UNSUPPORTED, error_text};
}

Status Robot::StartMonitoring() {
  return {ReturnCode::UNSUPPORTED, error_text};
}

Status Robot::StopControlling() {
  Status result = {ReturnCode::OK, ""};

  if (!endpoint_.IsRequestActive()) {
    auto ret =
        ReceiveMotionState(std::chrono::milliseconds(kStopReceiveTimeoutMs));
    if (ret.return_code != kuka::external::control::ReturnCode::OK) {
      return {ReturnCode::ERROR,
              "Failed to receive before sending stop signal"};
    }
  }

  auto stop_send_str_view = control_signal_.CreateXMLString(last_ipoc_, true);

  if (!stop_send_str_view.has_value()) {
    result = {ReturnCode::ERROR,
              "Parsing last control signal to proper XML format failed"};
  } else if (!endpoint_.MessageSend(stop_send_str_view.value())) {
    result = {ReturnCode::ERROR,
              "Sending last RSI stop command failed - cancelling RSI program"};
  }

  endpoint_.Reset();
  control_signal_.Reset();
  return result;
}

Status Robot::StopMonitoring() { return {ReturnCode::UNSUPPORTED, error_text}; }

Status
Robot::CreateMonitoringSubscription(std::function<void(BaseMotionState &)>) {
  return {ReturnCode::UNSUPPORTED, error_text};
}

Status Robot::CancelMonitoringSubscription() {
  return {ReturnCode::UNSUPPORTED, error_text};
}

bool Robot::HasMonitoringSubscription() { return false; }

Status Robot::SwitchControlMode(ControlMode control_mode) {
  return {ReturnCode::UNSUPPORTED, error_text};
}

Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler> &&) {
  return {ReturnCode::UNSUPPORTED, error_text};
}

Status Robot::SendControlSignal() {
  if (!control_signal_.InitialPositionsSet()) {
    return {ReturnCode::ERROR, "Control signal not initialized, please call "
                               "ReceiveMotionState() first"};
  }

  auto ctr_signal_xml = control_signal_.CreateXMLString(last_ipoc_, false);
  if (!ctr_signal_xml.has_value()) {
    return {ReturnCode::ERROR,
            "Parsing control signal to proper XML format failed"};
  }

  if (!endpoint_.MessageSend(ctr_signal_xml.value())) {
    return {ReturnCode::ERROR, "Sending RSI control signal failed"};
  }
  return {ReturnCode::OK, "Sent RSI control signal"};
}

Status
Robot::ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) {
  if (!endpoint_.ReceiveOrTimeout(receive_request_timeout)) {
    return {ReturnCode::ERROR, "Receiving RSI state failed"};
  }

  if (!control_signal_.InitialPositionsSet()) {
    initial_motion_state_.CreateFromXML(endpoint_.GetReceivedMessage().data());
    control_signal_.SetInitialPositions(initial_motion_state_);
  }

  return UpdateMotionState(endpoint_.GetReceivedMessage());
}

BaseControlSignal &Robot::GetControlSignal() { return control_signal_; }

BaseMotionState &Robot::GetLastMotionState() { return last_motion_state_; }

Status Robot::UpdateMotionState(std::string_view xml_str) {
  last_motion_state_.CreateFromXML(xml_str.data());
  last_ipoc_ = last_motion_state_.GetIpoc();
  return {ReturnCode::OK, "Parsed incoming RSI server message"};
}

}; // namespace kuka::external::control::kss::rsi
