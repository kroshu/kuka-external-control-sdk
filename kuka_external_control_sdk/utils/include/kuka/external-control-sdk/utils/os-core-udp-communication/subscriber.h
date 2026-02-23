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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SUBSCRIBER_H_
#define KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SUBSCRIBER_H_

#include <chrono>
#include <utility>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication
{

class Subscriber
{
public:
  typedef Socket::ErrorCode ErrorCode;

public:  // <ctor>
  explicit Subscriber(
    const SocketAddress & sub_address, const SocketAddress & interface_address, bool is_multicast);
  virtual ~Subscriber() = default;
  ErrorCode Setup();

public:  // <operations>
  ErrorCode Receive();
  ErrorCode ReceiveAllArrived();
  ErrorCode WaitForAndReceive(std::chrono::microseconds timeout);
  ErrorCode WaitForAndReceiveAllArrived(std::chrono::microseconds timeout);
  std::pair<const uint8_t *, size_t> GetMessage() const;

public:  // <properties>
  static constexpr uint16_t kMaxBufferSize = 65500;
  static constexpr int kRecvBufferSize = 1024 * kMaxBufferSize;
  const SocketAddress & Address() const { return sub_address_; }
  bool IsMulticast() const { return is_multicast_; }

protected:
  Socket socket_;
  SocketAddress sub_address_;
  SocketAddress interface_address_;
  const bool is_multicast_;

  uint8_t recv_buffer_[kMaxBufferSize];
  int received_msg_size_;
};
}  // namespace os::core::udp::communication

#endif  // KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SUBSCRIBER_H_
