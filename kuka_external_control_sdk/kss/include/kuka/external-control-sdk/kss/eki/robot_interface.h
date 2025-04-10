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

#ifndef KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_
#define KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_

#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/eki/client.h"
#include "kuka/external-control-sdk/kss/rsi/endpoint.h"
#include "kuka/external-control-sdk/kss/rsi/robot_interface.h"
#include "kuka/external-control-sdk/kss/message_builder.h"

namespace kuka::external::control::kss::eki {

class Robot : public kuka::external::control::kss::rsi::Robot {
  // Special methods
 public:
  Robot(Configuration);

  // Interface implementation
 public:
  virtual Status Setup() override;

  virtual Status StartControlling(
      kuka::external::control::ControlMode) override;  // call EKI service

  virtual Status StopControlling() override;  // Set stop flag + send

  virtual Status SwitchControlMode(
      ControlMode control_mode) override;  // call EKI service, only in inactive
  virtual Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler)
      override;  // EKI response / new EKI client-server with external the service
  virtual Status RegisterEventHandler(std::unique_ptr<KssEventHandler>&& event_handler) override;

  virtual Status TurnOnDrives() override;
  virtual Status TurnOffDrives() override;
  virtual Status SetCycleTime(Configuration::CycleTime cycle_time) override;

  // Members and methods necessary for network configuration and error handling.
 private:
  Configuration config_;
  Client tcp_client_;
};

}  // namespace kuka::external::control::kss
#endif  // KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_
