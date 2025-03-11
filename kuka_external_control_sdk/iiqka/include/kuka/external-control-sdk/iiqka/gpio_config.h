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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_GPIO_CONFIG_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_GPIO_CONFIG_H_

#include "kuka/external-control-sdk/common/gpio_config.h"
#include "proto-api/motion-services-ecs/signal_config_external.pb.h"

namespace kuka::external::control::iiqka {

class GPIOConfig : public BaseGPIOConfig {
public:
  GPIOConfig() : BaseGPIOConfig(){};
  GPIOConfig(
      const kuka::ecs::v1::SignalConfigExternal &protobuf_signal_config) {
    *this = std::move(protobuf_signal_config);
  }
  ~GPIOConfig() = default;

  bool const &IsGPIOUsed() const { return is_gpio_used_; }
  void SetGPIOToUse(bool signal_used) { is_gpio_used_ = signal_used; }

  GPIOConfig &operator=(const kuka::ecs::v1::SignalConfigExternal &rhs) {
    auto &pb_sc = rhs.signal_config();
    bool has_pb_sc = rhs.has_signal_config();

    this->gpio_id_ = rhs.signal_id();
    this->is_gpio_used_ = rhs.has_signal_config();
    if (has_pb_sc) {
      this->name_ = pb_sc.name();
      switch (pb_sc.direction()) {
      case kuka::ecs::v1::SignalConfig::INPUT:
        this->direction_ = GPIODirection::INPUT;
        break;
      case kuka::ecs::v1::SignalConfig::OUTPUT:
        this->direction_ = GPIODirection::OUTPUT;
        break;
      default:
        this->direction_ = GPIODirection::UNSPECIFIED;
        break;
      }
      switch (pb_sc.data_type()) {
      case kuka::ecs::v1::SignalConfig::BOOL:
        this->value_type_ = GPIOValueType::BOOL_VALUE;
        break;
      case kuka::ecs::v1::SignalConfig::NUMBER:
        this->value_type_ = GPIOValueType::DOUBLE_VALUE;
        break;
      case kuka::ecs::v1::SignalConfig::RAW:
        this->value_type_ = GPIOValueType::RAW_VALUE;
        break;
      default:
        this->value_type_ = GPIOValueType::UNSPECIFIED;
        break;
      }
    }
    return *this;
  }

private:
  bool is_gpio_used_ = false;
};

} // namespace kuka::external::control::iiqka

#endif // #define KUKA_EXTERNAL_CONTROL__IIQKA_GPIO_CONFIG_H_