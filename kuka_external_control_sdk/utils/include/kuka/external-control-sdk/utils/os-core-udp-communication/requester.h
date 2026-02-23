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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__REQUESTER_H_
#define KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__REQUESTER_H_

#include <chrono>
#include <memory>
#include <utility>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication
{
class Requester
{
public:
  typedef Socket::ErrorCode ErrorCode;

public:  // <ctor>
  explicit Requester(const SocketAddress & local_address, const SocketAddress & replier_address);
  virtual ~Requester() = default;

  template <typename SocketType, class... Args>
  void SetSocket(Args &&... args)
  {
    socket_ = std::make_unique<SocketType>(std::forward<Args>(args)...);
  }

  ErrorCode Setup();
  virtual void Reset();

public:  // <operations>
  ErrorCode SendRequest(uint8_t * req_msg_data, size_t req_msg_size);
  virtual ErrorCode SendRequestOrTimeout(
    uint8_t * req_msg_data, size_t req_msg_size, std::chrono::microseconds send_timeout);

  ErrorCode ReceiveReply();
  virtual ErrorCode ReceiveReplyOrTimeout(std::chrono::microseconds recv_timeout);

  ErrorCode ReceiveReplyAll();
  virtual ErrorCode ReceiveReplyAllOrTimeout(std::chrono::microseconds recv_timeout);

public:  // <properties>
  static constexpr uint16_t kMaxBufferSize = 65500;
  bool IsRequestActive() const { return active_request_; }
  std::pair<const uint8_t *, size_t> GetReplyMessage() const;
  const SocketAddress & LocalAddress() const { return local_address_; }
  const SocketAddress & ReplierAddress() const { return replier_address_; }

protected:
  virtual void StartSending(std::chrono::milliseconds, uint8_t *, size_t) {}

  virtual void StopSending(std::chrono::milliseconds, Requester::ErrorCode) {}

  virtual void StartReceiving(std::chrono::milliseconds) {}

  virtual void StopReceiving(std::chrono::milliseconds, uint8_t *, size_t, Requester::ErrorCode) {}

  uint8_t reply_buffer_[kMaxBufferSize];

  std::unique_ptr<Socket> socket_;
  SocketAddress local_address_;
  SocketAddress replier_address_;

  bool active_request_ = false;
  int last_reply_size_ = 0;
};
}  // namespace os::core::udp::communication

#endif  // KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__REQUESTER_H_
