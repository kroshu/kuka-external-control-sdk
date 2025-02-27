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

#include "kuka/external-control-sdk/kss/mxa/robot_interface.h"

namespace kuka::external::control::kss::mxa {

Robot::Robot(Configuration config)
    : kuka::external::control::kss::rsi::Robot(config)
    , client_(config.kli_ip_address, config.reset_errors)
{}

Status Robot::Setup() {
  Status setup_ret = client_.Setup();
  if (setup_ret.return_code != ReturnCode::OK) {
    return {ReturnCode::ERROR, setup_ret.message};
  }

  return kuka::external::control::kss::rsi::Robot::Setup();
}

Status Robot::StartControlling(kuka::external::control::ControlMode control_mode) {
  Status start_rsi_ret = client_.StartRSI(control_mode);
  if (start_rsi_ret.return_code == ReturnCode::OK ||
      start_rsi_ret.return_code == ReturnCode::WARN) {
    rsi_running_ = true;
  }
  return start_rsi_ret;
}

Status Robot::StopControlling() {
  if (!rsi_running_) {
    return {ReturnCode::WARN, "Control already stopped"};
  }

  Status rsi_stop_ret = kuka::external::control::kss::rsi::Robot::StopControlling();
  if (rsi_stop_ret.return_code == ReturnCode::ERROR) {
        CancelRSI();
        return rsi_stop_ret;
  }

  client_.ResetRSI();
  rsi_running_ = false;

  return {ReturnCode::OK, "RSI successfully stopped via stop flag"};
}

Status Robot::CancelRSI() {
  Status cancel_rsi_ret = client_.CancelRSI();
  if (cancel_rsi_ret.return_code == ReturnCode::OK) {
    rsi_running_ = false;
  }
  return cancel_rsi_ret;
}

Status Robot::SendControlSignal() {
  if (client_.ShouldRSIStop()) {
    CancelRSI();
    endpoint_.Reset();
    rsi_running_ = false;
    return {ReturnCode::ERROR, "RSI communication stop triggered"};
  }

  return kuka::external::control::kss::rsi::Robot::SendControlSignal();
}

Status Robot::SwitchControlMode(ControlMode control_mode) {
  Status stop_ret = StopControlling();
  if (stop_ret.return_code != ReturnCode::OK && stop_ret.return_code != ReturnCode::WARN) {
    return stop_ret;
  }

  return StartControlling(control_mode);
}

Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  return client_.RegisterEventHandler(std::move(event_handler));
}

};  // namespace kuka::external::control::kss
