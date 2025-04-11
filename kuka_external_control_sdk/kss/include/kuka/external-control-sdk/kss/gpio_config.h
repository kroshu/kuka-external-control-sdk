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

namespace kuka::external::control::kss {

class GPIOConfig : public BaseGPIOConfig {
public:
  GPIOConfig() : BaseGPIOConfig(){};
  GPIOConfig(std::size_t id, std::string name, GPIOValueType value_type)
      : BaseGPIOConfig() {
    this->gpio_id_ = id;
    this->name_ = name;
    this->value_type_ = value_type;
  }
  /* -- Parse XML to get config --*/
  //   GPIOConfig(
  //       const kuka::ecs::v1::SignalConfigExternal &protobuf_signal_config) {
  //     *this = std::move(protobuf_signal_config);
  //   }
  ~GPIOConfig() = default;

  /* -- Parse XML to get config --*/
  //   GPIOConfig &operator=(const kuka::ecs::v1::SignalConfigExternal &rhs) {
  //     auto &pb_sc = rhs.signal_config();
  //     bool has_pb_sc = rhs.has_signal_config();

  //     this->gpio_id_ = rhs.signal_id();
  //     this->is_gpio_used_ = rhs.has_signal_config();
  //     if (has_pb_sc) {
  //       this->name_ = pb_sc.name();
  //       switch (pb_sc.direction()) {
  //       case kuka::ecs::v1::SignalConfig::INPUT:
  //         this->direction_ = GPIODirection::INPUT;
  //         break;
  //       case kuka::ecs::v1::SignalConfig::OUTPUT:
  //         this->direction_ = GPIODirection::OUTPUT;
  //         break;
  //       default:
  //         this->direction_ = GPIODirection::UNSPECIFIED;
  //         break;
  //       }
  //       switch (pb_sc.data_type()) {
  //       case kuka::ecs::v1::SignalConfig::BOOL:
  //         this->value_type_ = GPIOValueType::BOOL_VALUE;
  //         break;
  //       case kuka::ecs::v1::SignalConfig::NUMBER:
  //         this->value_type_ = GPIOValueType::DOUBLE_VALUE;
  //         break;
  //       case kuka::ecs::v1::SignalConfig::RAW:
  //         this->value_type_ = GPIOValueType::RAW_VALUE;
  //         break;
  //       default:
  //         this->value_type_ = GPIOValueType::UNSPECIFIED;
  //         break;
  //       }
  //     }
  //     return *this;
  //   }
};

} // namespace kuka::external::control::kss

#endif // #define KUKA_EXTERNAL_CONTROL__KSS_GPIO_CONFIG_H_