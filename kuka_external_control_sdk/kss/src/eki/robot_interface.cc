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

#include "kuka/external-control-sdk/kss/eki/robot_interface.h"

namespace kuka::external::control::kss::eki {

Robot::Robot(Configuration config)
    : kuka::external::control::kss::rsi::Robot(config)
    , tcp_client_(config.kli_ip_address, config.eki_port)
{}

Status Robot::Setup() {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};

  os::core::udp::communication::TCPClient::ErrorCode setup_ret = tcp_client_.Setup();
  if (setup_ret != os::core::udp::communication::TCPClient::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR, "Setup failed with error code: " + setup_ret};
  }

  Status start_ret = tcp_client_.Start();
  if (start_ret.return_code != ReturnCode::OK && start_ret.return_code != ReturnCode::WARN) {
    return start_ret;
  }

  if (!endpoint_.Setup(config_.client_port)) {
    return {ReturnCode::ERROR, "Setup of RSI UDP endpoint failed"};
  }

  return start_ret;
}

Status Robot::StartControlling(kuka::external::control::ControlMode control_mode) {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.StartRSI(control_mode);
}

Status Robot::StopControlling() {
  Status stop_ret = kuka::external::control::kss::rsi::Robot::StopControlling();
  if (stop_ret.return_code != ReturnCode::OK && stop_ret.return_code != ReturnCode::WARN) {
    return stop_ret;
  }

  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.StopRSI();
}

Status Robot::SwitchControlMode(ControlMode control_mode) {
  Status stop_ret = StopControlling();
  if (stop_ret.return_code != ReturnCode::OK && stop_ret.return_code != ReturnCode::WARN) {
    return stop_ret;
  }

  return StartControlling(control_mode);
}

Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  return tcp_client_.RegisterEventHandler(std::move(event_handler));
}

Status Robot::RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) {
  return tcp_client_.RegisterEventHandlerExtension(std::move(extension));
}

Status Robot::RegisterStatusResponseHandler(std::unique_ptr<IStatusResponseHandler>&& handler) {
  return tcp_client_.RegisterStatusResponseHandler(std::move(handler));
}

Status Robot::TurnOnDrives() {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.TurnOnDrives();
}

Status Robot::TurnOffDrives() {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.TurnOffDrives();
}

Status Robot::SetCycleTime(CycleTime cycle_time) {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.SetCycleTime(cycle_time);
}

Status Robot::GetStatus() {
  std::lock_guard<std::mutex> lck{tcp_client_mtx_};
  return tcp_client_.GetStatus();
}

};  // namespace kuka::external::control::kss
