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

#ifndef KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_
#define KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_

#include <mutex>

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
  Status Setup() override;

  // Call EKI service
  Status StartControlling(kuka::external::control::ControlMode) override;

  // Set stop flag + send
  Status StopControlling() override;

  // Call EKI service, only in inactive
  Status SwitchControlMode(ControlMode control_mode) override;

  // EKI response / new EKI client-server with external the service
  Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) override;

  Status TurnOnDrives() override;

  Status TurnOffDrives() override;

  Status SetCycleTime(CycleTime cycle_time) override;

  Status RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) override;

  Status RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler>&& handler) override;

  // Members and methods necessary for network configuration and error handling.
 private:
  Configuration config_;
  Client tcp_client_;
};

}  // namespace kuka::external::control::kss
#endif  // KUKA_EXTERNAL_CONTROL__EKI_ROBOT_INTERFACE_H_
