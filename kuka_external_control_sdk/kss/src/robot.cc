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

#include "kuka/external-control-sdk/kss/robot.h"

#include "kuka/external-control-sdk/kss/eki/robot_interface.h"
#include "kuka/external-control-sdk/kss/mxa/robot_interface.h"
#include "kuka/external-control-sdk/kss/rsi/robot_interface.h"

namespace kuka::external::control::kss {

Robot::Robot(Configuration config) {
  switch (config.installed_interface) {
    case Configuration::InstalledInterface::MXA_RSI:
      installed_interface_ = std::make_unique<kuka::external::control::kss::mxa::Robot>(config);
      break;
    case Configuration::InstalledInterface::EKI_RSI:
      installed_interface_ = std::make_unique<kuka::external::control::kss::eki::Robot>(config);
      break;
    case Configuration::InstalledInterface::RSI_ONLY:
      installed_interface_ = std::make_unique<kuka::external::control::kss::rsi::Robot>(config);
      break;
    default:
      throw std::runtime_error("Configuration uses an invalid interface");
  };
}

Status Robot::Setup() {
  return installed_interface_->Setup();
}

Status Robot::StartControlling(kuka::external::control::ControlMode control_mode) {
  return installed_interface_->StartControlling(control_mode);
}

Status Robot::StartMonitoring() {
  return installed_interface_->StartMonitoring();
}

Status Robot::StopControlling() {
  return installed_interface_->StopControlling();
}

Status Robot::StopMonitoring() {
  return installed_interface_->StopMonitoring();
}

Status Robot::CreateMonitoringSubscription(std::function<void(BaseMotionState&)> func) {
  return installed_interface_->CreateMonitoringSubscription(func);
}

Status Robot::CancelMonitoringSubscription() {
  return installed_interface_->CancelMonitoringSubscription();
}

bool Robot::HasMonitoringSubscription() {
  return installed_interface_->HasMonitoringSubscription();
}

Status Robot::SendControlSignal() {
  return installed_interface_->SendControlSignal();
}

Status Robot::ReceiveMotionState(std::chrono::milliseconds receive_request_timeout) {
  return installed_interface_->ReceiveMotionState(receive_request_timeout);
}

BaseControlSignal& Robot::GetControlSignal() {
  return installed_interface_->GetControlSignal();
}

BaseMotionState& Robot::GetLastMotionState() {
  return installed_interface_->GetLastMotionState();
}

Status Robot::SwitchControlMode(ControlMode control_mode) {
  return installed_interface_->SwitchControlMode(control_mode);
}

Status Robot::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  return installed_interface_->RegisterEventHandler(std::move(event_handler));
}

Status Robot::TurnOnDrives() {
  return installed_interface_->TurnOnDrives();
}

Status Robot::TurnOffDrives() {
  return installed_interface_->TurnOffDrives();
}

Status Robot::SetCycleTime(CycleTime cycle_time) {
  return installed_interface_->SetCycleTime(cycle_time);
}

Status Robot::RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) {
  return installed_interface_->RegisterEventHandlerExtension(std::move(extension));
}

Status Robot::RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler>&& handler) {
  return installed_interface_->RegisterStatusResponseHandler(std::move(handler));
}

};  // namespace kuka::external::control::kss
