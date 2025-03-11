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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_SIGNAL_VALUE_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_SIGNAL_VALUE_H_

#include "gpio_config.h"
#include "kuka/external-control-sdk/common/signal_value.h"
#include "proto-api/motion-services-ecs/signal_value_external.pb.h"

namespace kuka::external::control::iiqka {
static constexpr size_t kMotionState_SignalValueMaxCount{100};
static constexpr size_t kControlSignal_SignalValueMaxCount{10};

class SignalValue : public BaseSignalValue {
public:
  SignalValue() : BaseSignalValue(){};

  ~SignalValue() = default;
  SignalValue(kuka::ecs::v1::SignalValueExternal &protobuf_signal_value)
      : BaseSignalValue() {
    *this = std::move(protobuf_signal_value);
  }
  SignalValue(GPIOConfig const &gpio_config) : BaseSignalValue() {
    signal_id_ = gpio_config.GetGPIOId();
    value_type_ = gpio_config.GetValueType();
  }
  SignalValue &
  operator=(kuka::ecs::v1::SignalValueExternal &&protobuf_signal_value) {
    this->signal_id_ = protobuf_signal_value.signal_id();

    switch (protobuf_signal_value.signal_type_case()) {
    case kuka::ecs::v1::SignalValueExternal::kBoolValue:
      this->value_type_ = GPIOValueType::BOOL_VALUE;
      this->value_.bool_value_ = protobuf_signal_value.bool_value();
      break;
    case kuka::ecs::v1::SignalValueExternal::kDoubleValue:
      this->value_type_ = GPIOValueType::DOUBLE_VALUE;
      this->value_.double_value_ = protobuf_signal_value.double_value();
      break;
    case kuka::ecs::v1::SignalValueExternal::kRawValue:
      this->value_type_ = GPIOValueType::RAW_VALUE;
      this->value_.raw_value_ = protobuf_signal_value.raw_value();
      break;
    default:
      this->value_type_ = GPIOValueType::UNSPECIFIED;
      break;
    }
    return *this;
  }
};

} // namespace kuka::external::control::iiqka

#endif // #define KUKA_EXTERNAL_CONTROL__IIQKA_SIGNAL_VALUE_H_
