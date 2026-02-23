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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__PUBLISHER_H_
#define KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__PUBLISHER_H_

#include <cstdint>
#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication
{

class Publisher
{
public:
  typedef Socket::ErrorCode ErrorCode;

public:
  Publisher(
    const SocketAddress & pub_address, const SocketAddress & interface_address, bool is_multicast);
  virtual ~Publisher() = default;
  ErrorCode Setup();

  ErrorCode Send(const uint8_t * msg_data, uint16_t msg_size);
  bool SetTTL(int ttl);

public:
  const SocketAddress & Address() const { return pub_address_; }
  bool IsMulticast() const { return is_multicast_; }

protected:
  Socket socket_;
  SocketAddress pub_address_;
  SocketAddress interface_address_;
  const bool is_multicast_;
};
}  // namespace os::core::udp::communication

#endif  // KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__PUBLISHER_H_
