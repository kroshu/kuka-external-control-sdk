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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_GPIO_VALUE_H_
#define KUKA_EXTERNAL_CONTROL__KSS_GPIO_VALUE_H_

#include "gpio_config.h"
#include "kuka/external-control-sdk/common/gpio_value.h"
#include <memory>

namespace kuka::external::control::kss {

class GPIOValue : public BaseGPIOValue {
public:
  GPIOValue() : BaseGPIOValue(){};
  GPIOValue(std::unique_ptr<GPIOConfig> gpio_config)
      : BaseGPIOValue(std::move(gpio_config)) {}
  GPIOValue(std::unique_ptr<GPIOConfig> gpio_config, double value)
      : BaseGPIOValue(std::move(gpio_config)) {
    this->SetValue(value);
  }
  ~GPIOValue() = default;
};

} // namespace kuka::external::control::kss

#endif // #define KUKA_EXTERNAL_CONTROL__KSS_GPIO_VALUE_H_