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

  ~GPIOConfig() = default;
  // Add RSI specific methods
};

} // namespace kuka::external::control::kss

#endif // #define KUKA_EXTERNAL_CONTROL__KSS_GPIO_CONFIG_H_