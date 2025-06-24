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
  std::optional<double> const &GetValue() const {
    switch (gpio_config_->GetValueType()) {
    case GPIOValueType::BOOLEAN:
      return static_cast<double>(value_.bool_value_);
    case GPIOValueType::ANALOG:
      return value_.double_value_;
    case GPIOValueType::DIGITAL:
      return static_cast<double>(value_.long_value_);
    case GPIOValueType::UNSPECIFIED:
    default:
      return std::nullopt;
    }
  }
  std::optional<bool> const &GetBoolValue() const {
    if (gpio_config_->GetValueType() == GPIOValueType::BOOLEAN) {
      return value_.bool_value_;
    }
    return std::nullopt;
  }
  std::optional<double> const &GetDoubleValue() const {
    if (gpio_config_->GetValueType() == GPIOValueType::ANALOG) {
      return value_.double_value_;
    }
    return std::nullopt;
  }
  std::optional<int64_t> const &GetLongValue() const {
    if (gpio_config_->GetValueType() == GPIOValueType::DIGITAL) {
      return value_.long_value_;
    }
    return std::nullopt;
  }

  bool SetValue(double value) {
    switch (gpio_config_->GetValueType()) {
    case GPIOValueType::BOOLEAN:
      return this->SetBoolValue(value);
    case GPIOValueType::ANALOG:
      return this->SetDoubleValue(value);
    case GPIOValueType::DIGITAL:
      return this->SetLongValue(value);
    case GPIOValueType::UNSPECIFIED:
    default:
      return false;
    }
  }
  BaseGPIOValue &operator=(double value) {
    this->SetValue(value);
    return *this;
  }

  bool SetBoolValue(double value) {
    return SetBoolValue(static_cast<bool>(value));
  }
  bool SetBoolValue(bool value) {
    if (gpio_config_->GetValueType() != GPIOValueType::BOOLEAN) {
      return false;
    }
    value_.bool_value_ = value;
    return true;
  }

  bool SetDoubleValue(double value) {
    if (gpio_config_->GetValueType() != GPIOValueType::ANALOG) {
      return false;
    }
    if (!check_limits<double>(value)) {
      return false;
    }
    value_.double_value_ = value;
    return true;
  }
  bool SetLongValue(double value) {
    return SetLongValue(static_cast<int64_t>(value));
  }
  bool SetLongValue(int64_t value) {
    if (gpio_config_->GetValueType() != GPIOValueType::DIGITAL) {
      return false;
    }
    if (!check_limits<int64_t>(value)) {
      return false;
    }
    value_.long_value_ = value;
    return true;
  }

protected:
  std::unique_ptr<BaseGPIOConfig> gpio_config_;
  union {
    bool bool_value_;
    double double_value_;
    int64_t long_value_;
  } value_;
  // std::variant<bool,double,uint64_t,int64_t> value_;

private:
  template <typename T> bool check_limits(T value) const {
    if (gpio_config_->GetEnableLimits()) {
      return value >= gpio_config_->GetMinValue() &&
             value <= gpio_config_->GetMaxValue();
    }
    return true;
  }
};
} // namespace kuka::external::control

#endif // KUKA_EXTERNAL_CONTROL__GPIO_VALUE_H_