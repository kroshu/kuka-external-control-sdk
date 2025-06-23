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

#ifndef KUKA_EXTERNAL_CONTROL__GPIO_CONFIG_H_
#define KUKA_EXTERNAL_CONTROL__GPIO_CONFIG_H_

#include <string>

namespace kuka::external::control {
enum class GPIODirection { UNSPECIFIED = 0, INPUT = 1, OUTPUT = 2 };
enum class GPIOValueType {
  UNSPECIFIED = 0,
  BOOL_VALUE = 1,
  DOUBLE_VALUE = 2,
  RAW_VALUE = 3,
  LONG_VALUE = 4
};

class BaseGPIOConfig {
public:
  BaseGPIOConfig() = default;
  ~BaseGPIOConfig() = default;

  std::size_t const &GetGPIOId() const { return gpio_id_; }
  std::string const &GetName() const { return name_; }
  GPIODirection const &GetDirection() const { return direction_; }
  GPIOValueType const &GetValueType() const { return value_type_; }

protected:
  std::size_t gpio_id_;
  std::string name_;
  GPIODirection direction_ = GPIODirection::UNSPECIFIED;
  GPIOValueType value_type_ = GPIOValueType::UNSPECIFIED;
};
} // namespace kuka::external::control

#endif // KUKA_EXTERNAL_CONTROL__GPIO_CONFIG_H_