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

#ifndef EVENT_HANDLERS__CONTROL_EVENT_HANDLER_HPP_
#define EVENT_HANDLERS__CONTROL_EVENT_HANDLER_HPP_

#include <iostream>
#include <string>

#include "kuka/external-control-sdk/common/irobot.h"

namespace external_control_sdk_example
{

class ControlEventHandler : public kuka::external::control::EventHandler
{
  void OnSampling() override { std::cout << "Sampling started\n"; }
  void OnControlModeSwitch(const std::string & reason) override
  {
    std::cout << "Control mode switch, reason: " << reason << std::endl;
  }
  void OnStopped(const std::string & reason) override
  {
    std::cout << "Stopped, reason: " << reason << std::endl;
  }
  void OnError(const std::string & reason) override
  {
    std::cout << "Error occurred, reason: " << reason << std::endl;
  }
};

}  // namespace external_control_sdk_example

#endif  // EVENT_HANDLERS__CONTROL_EVENT_HANDLER_HPP_
