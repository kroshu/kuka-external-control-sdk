// Copyright 2023 KUKA Hungaria Kft.
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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_

#include <chrono>
#include <string>

#include "kuka/external-control-sdk/common/irobot.h"

namespace kuka::external::control::kss {

// RSI cycle time
enum class CycleTime : uint8_t { UNSPECIFIED = 0, RSI_4MS = 1, RSI_12MS = 2 };

struct GPIOConfiguration {
  // Name of the GPIO
  std::string name;
  //  Type of the GPIO value (BOOLEAN, ANALOG, DIGITAL)
  GPIOValueType value_type = GPIOValueType::UNSPECIFIED;
  // (Optional) Initial value for the GPIO
  // TODO (Komaromi): Make it type specific
  double initial_value = 0;
  // (Optional) Enable limits for the GPIO value
  // If true, min_value and max_value must be set
  // If false, min_value and max_value are ignored
  bool enable_limits = false;
  // (Optional) Minimum value for the GPIO
  double min_value = 0;
  // (Optional) Maximum value for the GPIO
  double max_value = 0;
};

struct Configuration {
  // IP address of the KONI interface on the KRC-5.
  std::string kli_ip_address;
  // IP address of the client machine.
  std::string client_ip_address;

  // Degree of freedom.
  std::size_t dof = 6;

  // GPIO states
  std::vector<GPIOConfiguration> gpio_state_configs;

  // GPIO commands
  std::vector<GPIOConfiguration> gpio_command_configs;

  // The control mode to begin external control in.
  // At the present, the following modes are supported:
  // 1 - Joint position control
  ControlMode initial_control_mode = ControlMode::UNSPECIFIED;

  // This value is ignored if plain RSI is used
  CycleTime cycle_time = CycleTime::RSI_12MS;

  enum class InstalledInterface {
    UNSPECIFIED = 0,
    MXA_RSI = 1,
    EKI_RSI = 2,
    RSI_ONLY = 3
  };

  // The interface installed on the KSS robot
  InstalledInterface installed_interface = InstalledInterface::RSI_ONLY;

  // Action to do after MXA/KRC error signaled to event handler
  // If true -> reset error messages
  // If false -> error messages remain
  bool reset_errors = true;

  // Ports open on the KRC to enable external control. These values are fixed.
  const unsigned short eki_port = 54600;
  const unsigned short client_port = 59152;
};

} // namespace kuka::external::control::kss

#endif // KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_
