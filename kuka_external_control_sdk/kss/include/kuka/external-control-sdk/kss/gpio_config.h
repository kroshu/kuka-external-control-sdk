// Copyright 2025 KUKA Hungaria kft.
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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_GPIO_CONFIG_H_
#define KUKA_EXTERNAL_CONTROL__KSS_GPIO_CONFIG_H_

#include "kuka/external-control-sdk/common/gpio_config.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss {

class GPIOConfig : public BaseGPIOConfig {
public:
  GPIOConfig() : BaseGPIOConfig(){};
  GPIOConfig(const GPIOConfig &other) = default;
  GPIOConfig(std::string name, GPIOValueType value_type,
             double initial_value = 0.0, bool enable_limits = false,
             double min_value = 0.0, double max_value = 0.0)
      : BaseGPIOConfig(name, value_type, initial_value, enable_limits,
                       min_value, max_value){};
  GPIOConfig(GPIOConfiguration config)
      : BaseGPIOConfig(config.name, config.value_type, config.initial_value,
                       config.enable_limits, config.min_value,
                       config.max_value){};
  // GPIOConfig(GPIOConfiguration config) : BaseGPIOConfig() {
  //   this->name_ = config.name;
  //   // Convert string to GPIOValueType enum
  //   if (config.value_type == "bool" || config.value_type == "BOOL" ||
  //       config.value_type == "boolean" || config.value_type ==
  //       "BOOLEAN") {
  //     this->value_type_ = GPIOValueType::BOOLEAN;
  //   } else if (config.value_type == "double" || config.value_type ==
  //   "DOUBLE" ||
  //              config.value_type == "float" || config.value_type ==
  //              "FLOAT" || config.value_type == "analog" ||
  //              config.value_type == "ANALOG") {
  //     this->value_type_ = GPIOValueType::ANALOG;
  //   } else if (config.value_type == "int" || config.value_type == "INT"
  //   ||
  //              config.value_type == "long" || config.value_type ==
  //              "LONG" || config.value_type == "digital" ||
  //              config.value_type == "DIGITAL") {
  //     this->value_type_ = GPIOValueType::DIGITAL;
  //   } else {
  //     this->value_type_ = GPIOValueType::UNSPECIFIED;
  //   }
  //   if (!config.initial_value.empty()) {
  //     try {
  //       this->initial_value_ = std::stod(config.initial_value);
  //     } catch (const std::invalid_argument &) {
  //       this->initial_value_ = 0.0; // If initial_value is not a valid
  //       number, set to 0.0
  //     }
  //   } else {
  //     this->initial_value_ = 0.0; // If initial_value is empty, set to
  //     0.0
  //   }
  //   if (config.enable_limits == "true" || config.enable_limits ==
  //   "TRUE") {
  //     this->enable_limits_ = true;
  //   } else {
  //     this->enable_limits_ = false;
  //   }
  //   if (!config.min_value.empty()) {
  //     try {
  //       this->min_value_ = std::stod(config.min_value);
  //     } catch (const std::invalid_argument &) {
  //       this->enable_limits_ =
  //           false; // If min_value is not a valid number, disable
  //           limits
  //     }
  //   } else {
  //     this->enable_limits_ = false; // If min_value is empty, disable
  //     limits
  //   }
  //   if (!config.max_value.empty()) {
  //     try {
  //       this->max_value_ = std::stod(config.max_value);
  //     } catch (const std::invalid_argument &) {
  //       this->enable_limits_ =
  //           false; // If max_value is not a valid number, disable
  //           limits
  //     }
  //   } else {
  //     this->enable_limits_ = false; // If max_value is empty, disable
  //     limits
  //   }
  // }

  ~GPIOConfig() = default;
  // Add RSI specific methods
};

} // namespace kuka::external::control::kss

#endif // #define KUKA_EXTERNAL_CONTROL__KSS_GPIO_CONFIG_H_