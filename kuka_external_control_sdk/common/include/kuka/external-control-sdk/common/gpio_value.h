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

#ifndef KUKA_EXTERNAL_CONTROL__GPIO_VALUE_H_
#define KUKA_EXTERNAL_CONTROL__GPIO_VALUE_H_
#include "gpio_config.h"
#include <cstdint>
#include <memory>

namespace kuka::external::control {
class BaseGPIOValue {
public:
  BaseGPIOValue() = default;
  BaseGPIOValue(std::unique_ptr<BaseGPIOConfig> gpio_config)
      : gpio_config_(std::move(gpio_config)) {}
  ~BaseGPIOValue() = default;

  // uint32_t const &GetGPIOId() const { return gpio_id_; }
  // void SetGPIOId(uint32_t id) { gpio_id_ = id; }
  // GPIOValueType const &GetValueType() const { return value_type_; }
  // void SetValueType(GPIOValueType type) { value_type_ = type; }
  std::unique_ptr<BaseGPIOConfig> const &GetGPIOConfig() const {
    return gpio_config_;
  }
  bool const &GetBoolValue() const { return value_.bool_value_; }
  void SetBoolValue(bool value) { value_.bool_value_ = value; }
  void SetBoolValue(double value) {
    value_.bool_value_ = static_cast<bool>(value);
  }
  double const &GetDoubleValue() const { return value_.double_value_; }
  void SetDoubleValue(double value) { value_.double_value_ = value; }
  uint64_t const &GetRawValue() const { return value_.raw_value_; }
  void SetRawValue(uint64_t value) { value_.raw_value_ = value; }
  void SetRawValue(double value) {
    value_.raw_value_ = static_cast<uint64_t>(value);
  }
  int64_t const &GetLongValue() const { return value_.long_value_; }
  void SetLongValue(int64_t value) { value_.long_value_ = value; }
  void SetLongValue(double value) {
    value_.long_value_ = static_cast<int64_t>(value);
  }

protected:
  // uint32_t gpio_id_;
  // GPIOValueType value_type_ = GPIOValueType::UNSPECIFIED;
  std::unique_ptr<BaseGPIOConfig> gpio_config_;
  union {
    bool bool_value_;
    double double_value_;
    uint64_t raw_value_;
    int64_t long_value_;
  } value_;
  // std::variant<bool,double,uint64_t,int64_t> value_;
};
} // namespace kuka::external::control

#endif // KUKA_EXTERNAL_CONTROL__GPIO_VALUE_H_