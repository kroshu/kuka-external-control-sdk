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
#include <variant>

namespace kuka::external::control {
enum class GPIOValueType {
  UNSPECIFIED = 0,
  BOOLEAN = 1,
  ANALOG = 2,
  DIGITAL = 3
};

class BaseGPIOConfig {
public:
  BaseGPIOConfig() = default;
  BaseGPIOConfig(std::string name, GPIOValueType value_type,
                 bool enable_limits = false, double min_value = 0.0,
                 double max_value = 0.0)
      : name_(std::move(name)), value_type_(value_type),
        enable_limits_(enable_limits), min_value_(min_value),
        max_value_(max_value) {}
  ~BaseGPIOConfig() = default;

  std::string const &GetName() const { return name_; }
  GPIOValueType const &GetValueType() const { return value_type_; }
  double const &GetMinValue() const { return min_value_; }
  double const &GetMaxValue() const { return max_value_; }
  bool const &GetEnableLimits() const { return enable_limits_; }

protected:
  std::string name_;
  GPIOValueType value_type_ = GPIOValueType::UNSPECIFIED;
  // This might be useful in cases with only gpio command interfaces
  // std::variant<bool, double, int64_t> initial_value_;

  double min_value_;
  double max_value_;
  bool enable_limits_ = false;
};
} // namespace kuka::external::control

#endif // KUKA_EXTERNAL_CONTROL__GPIO_CONFIG_H_