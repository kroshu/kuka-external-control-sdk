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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_CONFIGURATION_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_CONFIGURATION_H_

#include <chrono>
#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "proto-api/motion-services-ecs/signal_config_external.pb.h"

namespace kuka::external::control::iiqka {

struct Configuration {
  // IP address of the KONI interface on the KRC-5.
  std::string koni_ip_address;
  // IP address of the client machine.
  std::string client_ip_address;

  // Add a DTLS layer over the UDP communication during controlling.
  bool is_secure = false;

  // Certificate path, used in secure controlling
  std::string certificate_path;

  // Private key path, used in secure controlling
  std::string private_key_path;

  // Degree of freedom.
  uint8_t dof = 6;

  // Timeout to establish network connection with the KRC.
  uint32_t connection_timeout = 5000;

  // Cycle time in milliseconds Currently unused.
  static const uint32_t cycle_time{4};

  // Receive timeout for monitoring in milliseconds.
  uint32_t monitoring_timeout = 6;

  // Ports open on the KRC to enable external control. These values are fixed.
  static const unsigned short udp_replier_port{44444};
  static const unsigned short ecs_grpc_port{49335};
  static const unsigned short udp_subscriber_port{44446};

  // Multicast address to which packets get published in monitoring mode.
  const std::string udp_subscriber_multicast_address = "239.255.123.250";
};

struct QoS_Configuration {
  // If the number of lost packets in a given timeframe exceeds this value, the
  // connection is lost.
  uint32_t packet_loss_in_timeframe_limit = 3;
  // The timeframe in milliseconds.
  uint32_t timeframe_ms = 200;
  // If the number of consecutive lost packets exceeds this value, the
  // connection is lost.
  uint32_t consecutive_packet_loss_limit = 2;
};

class Signal_Configuration {
public:
  enum class SignalDirection { UNSPECIFIED = 0, INPUT = 1, OUTPUT = 2 };
  enum class SignalValueType { UNSPECIFIED = 0, BOOL = 1, RAW = 2, NUMBER = 3 };

  Signal_Configuration() = default;
  Signal_Configuration(
      const kuka::ecs::v1::SignalConfigExternal &protobuf_signal_config) {
    *this = std::move(protobuf_signal_config);
  }
  ~Signal_Configuration() = default;

  std::size_t const &GetSignalId() const { return signal_id_; }
  bool const &IsSignalUsed() const { return is_signal_used_; }
  void SetSignalToUse(bool signal_used) {
    is_signal_used_ = signal_used;
    is_changed_ = true;
  }
  bool const &IsChanged() const { return is_changed_; }
  void ClearChanged() { is_changed_ = false; }
  std::string const &GetName() const { return name_; }
  SignalDirection const &GetDirection() const { return direction_; }
  SignalValueType const &GetValueType() const { return value_type_; }

  // kuka::ecs::v1::SetSignal SetSignalForControl() {
  //   auto ret_val = kuka::ecs::v1::SetSignal()
  //   if (is_changed_) {

  //     is_changed_ = false;
  //   }
  //   //   auto ret_val = kuka::ecs::v1::SetSignalForControl();
  //   //   ret_val.set_signal_id(signal_id_);
  //   //   ret_val.set_is_signal_used(is_signal_used_);
  //   //   return ret_val;
  // }

  Signal_Configuration &
  operator=(const kuka::ecs::v1::SignalConfigExternal &rhs) {
    auto &pb_sc = rhs.signal_config();
    bool has_pb_sc = rhs.has_signal_config();

    this->signal_id_ = rhs.signal_id();
    this->is_signal_used_ = rhs.has_signal_config();
    if (has_pb_sc) {
      this->name_ = pb_sc.name();
      switch (pb_sc.direction()) {
      case kuka::ecs::v1::SignalConfig::INPUT:
        this->direction_ = SignalDirection::INPUT;
        break;
      case kuka::ecs::v1::SignalConfig::OUTPUT:
        this->direction_ = SignalDirection::OUTPUT;
        break;
      default:
        this->direction_ = SignalDirection::UNSPECIFIED;
        break;
      }
      switch (pb_sc.data_type()) {
      case kuka::ecs::v1::SignalConfig::BOOL:
        this->value_type_ = SignalValueType::BOOL;
        break;
      case kuka::ecs::v1::SignalConfig::RAW:
        this->value_type_ = SignalValueType::RAW;
        break;
      case kuka::ecs::v1::SignalConfig::NUMBER:
        this->value_type_ = SignalValueType::NUMBER;
        break;
      default:
        this->value_type_ = SignalValueType::UNSPECIFIED;
        break;
      }
    }
    return *this;
  }

private:
  std::size_t signal_id_;
  bool is_signal_used_ = false;
  bool is_changed_ = false;
  std::string name_;
  SignalDirection direction_ = SignalDirection::UNSPECIFIED;
  SignalValueType value_type_ = SignalValueType::UNSPECIFIED;
};

} // namespace kuka::external::control::iiqka

#endif // KUKA_EXTERNAL_CONTROL__IIQKA_CONFIGURATION_H_
