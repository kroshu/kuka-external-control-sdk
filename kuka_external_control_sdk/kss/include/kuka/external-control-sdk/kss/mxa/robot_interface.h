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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_ROBOT_INTERFACE_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_ROBOT_INTERFACE_H_

#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/message_builder.h"
#include "kuka/external-control-sdk/kss/mxa/client.h"
#include "kuka/external-control-sdk/kss/rsi/robot_interface.h"

namespace kuka::external::control::kss::mxa {

class Robot : public kuka::external::control::kss::rsi::Robot {
  // Special methods
 public:
  Robot(Configuration);

  // Interface implementation
 public:
  virtual Status Setup() override;

  virtual Status StartControlling(kuka::external::control::ControlMode) override;
  virtual Status StopControlling() override;

  virtual Status SendControlSignal() override;

  // TODO add to documentation that other commands could come in between the Stop and Start call
  // here, also evaluate dispatcher mode
  virtual Status SwitchControlMode(ControlMode control_mode) override;
  virtual Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) override;

 private:
  Status CancelRSI();
  
  bool stop_flag_;
  bool rsi_running_ = false;
  
  // Members and methods necessary for network configuration and error handling.
 private:
  Configuration config_;
  Client client_;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_MXA_ROBOT_INTERFACE_H_
