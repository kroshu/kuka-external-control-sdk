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

#include "kuka/external-control-sdk/kss/robot.h"

#include <iostream>

namespace kuka::external::control::kss {

Robot::Robot(Configuration config)
    : config_(config)
    , eki_tcp_channel_(config.kli_ip_address, config.eki_port)
    , control_signal_(config.dof)
    , last_motion_state_(config.dof)
    , initial_motion_state_(config.dof)
    , motion_states_initialized_(false) {
  control_signal_format_ = config_.control_signal_default_format_str_;
  motion_state_format_ = config_.motion_state_default_format_str_;
}

Status Robot::Setup() {
  auto setup_ret = eki_tcp_channel_.Setup();
  if (setup_ret != os::core::udp::communication::TCPClient::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR, "Setup failed with error code: " + setup_ret};
  }

  auto start_ret = eki_tcp_channel_.Start();
  if (start_ret.return_code != ReturnCode::OK && start_ret.return_code != ReturnCode::WARN) {
    return start_ret;
  }

  if (!rsi_comm_endpoint_.Setup(config_.client_port)) {
    return {ReturnCode::ERROR, "Setup of RSI UDP endpoint failed"};
  }

  return start_ret;
}

Status Robot::StartControlling(kuka::external::control::ControlMode control_mode) {
  return eki_tcp_channel_.StartRSI(control_mode);
}

Status Robot::StopControlling() {
  auto stop_send_str_view =
      control_signal_.GetXMLString(control_signal_format_, last_ipoc_, initial_motion_state_, true);
  if (!stop_send_str_view.has_value()) {
    return {ReturnCode::ERROR, "Parsing control signal to proper XML format failed"};
  }

  if (!rsi_comm_endpoint_.MessageSend(stop_send_str_view.value())) {
    return {ReturnCode::ERROR, "Sending RSI stop command failed"};
  }

  return eki_tcp_channel_.StopRSI();
}

Status Robot::SendControlSignal() {
  auto ctr_signal_xml =
      control_signal_.GetXMLString(control_signal_format_, last_ipoc_, initial_motion_state_);
  if (!ctr_signal_xml.has_value()) {
    return {ReturnCode::ERROR, "Parsing control signal to proper XML format failed"};
  }

  if (!rsi_comm_endpoint_.MessageSend(ctr_signal_xml.value())) {
    return {ReturnCode::ERROR, "Sending RSI control signal failed"};
  }
  return {ReturnCode::OK, "Sent RSI control signal"};
}

Status Robot::ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) {
  if (!rsi_comm_endpoint_.ReceiveOrTimeout(receive_request_timeout)) {
    return {ReturnCode::ERROR, "Receiving RSI state failed"};
  }

  return ParseIncomingXML(rsi_comm_endpoint_.GetReceivedMessage());
}

BaseControlSignal& Robot::GetControlSignal() { return control_signal_; }
BaseMotionState& Robot::GetLastMotionState() { return last_motion_state_; }

Status Robot::SwitchControlMode(ControlMode control_mode) {}
Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  return eki_tcp_channel_.RegisterEventHandler(std::move(event_handler));
}

Status Robot::ParseIncomingXML(std::string_view xml_str) {
  std::array<double, 6> arr;
  int ret = std::sscanf(xml_str.data(), motion_state_format_.data(), &arr[0], &arr[1], &arr[2],
                        &arr[3], &arr[4], &arr[5], &last_ipoc_);

  if (ret == 7) {
    if (!motion_states_initialized_) {
      initial_motion_state_ = arr;
      motion_states_initialized_ = true;
    }
    last_motion_state_ = arr;
    return {ReturnCode::OK, "Parsed incoming RSI server message"};
  }
  return {ReturnCode::ERROR,
          "Failed to parse all necessary fields of the incoming RSI server message"};
}

void Robot::Reset() {}
bool Robot::Uninitialized() {}

};  // namespace kuka::external::control::kss
