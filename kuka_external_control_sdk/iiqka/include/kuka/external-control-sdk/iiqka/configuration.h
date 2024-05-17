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
  // If the number of lost packets in a given timeframe exceeds this value, the connection is
  // lost.
  uint32_t packet_loss_in_timeframe_limit = 3;
  // The timeframe in milliseconds.
  uint32_t timeframe_ms = 200;
  // If the number of consecutive lost packets exceeds this value, the connection is lost.
  uint32_t consecutive_packet_loss_limit = 2;
};

}  // namespace kuka::external::control::iiqka

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_CONFIGURATION_H_
