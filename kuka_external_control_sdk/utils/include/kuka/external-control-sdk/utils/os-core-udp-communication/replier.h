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

#ifndef OS_CORE_COMM_UDP_REPLIER_H
#define OS_CORE_COMM_UDP_REPLIER_H

#include <chrono>

#include "socket.h"

namespace os::core::udp::communication {

class Replier {
 public:
  typedef Socket::ErrorCode ErrorCode;

 public:  //<ctor>
  Replier(const SocketAddress& local_address);
  virtual ~Replier() = default;
  virtual ErrorCode Setup();
  virtual void Reset();

 public:  //<operations>
  virtual ErrorCode ReceiveRequest();
  virtual ErrorCode ReceiveRequestOrTimeout(std::chrono::microseconds recv_timeout);
  virtual ErrorCode EmptyBuffer();
  virtual ErrorCode SendReply(uint8_t* reply_msg_data, size_t reply_msg_size);

 public:  //<properties>
  static constexpr uint16_t kMaxBufferSize = 65500;
  bool IsRequestActive() const { return active_request_; }
  std::pair<const uint8_t*, size_t> GetRequestMessage() const;
  const SocketAddress& LocalAddress() const { return local_address_; }
  const SocketAddress& LastRemoteAddress() const { return last_remote_address_; }

 protected:
  uint8_t server_buffer_[kMaxBufferSize];

  Socket socket_;
  SocketAddress local_address_;

  bool active_request_ = false;
  SocketAddress last_remote_address_;
  int last_request_size_ = 0;

  static constexpr int kEmtyBufferRecvTimeoutMs = 40;
};
}  // namespace os::core::udp::communication

#endif  // OS_CORE_COMM_UDP_REPLIER_H
