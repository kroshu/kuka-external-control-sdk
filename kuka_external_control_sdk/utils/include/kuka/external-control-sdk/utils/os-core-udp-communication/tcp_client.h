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

#ifndef OS_CORE_COMM_TCP_CLIENT_H
#define OS_CORE_COMM_TCP_CLIENT_H

#include "dissector.h"
#include "socket.h"

namespace os::core::udp::communication {

class TCPClientSocket : public Socket {
 public:
  /* creates a new socket with the given `flags`, and returns the underlaying
   * socket identifer */
  virtual int Map(int flags = 0) override;
};

class TCPClient : public Dissector {
 public:
  typedef Socket::ErrorCode ErrorCode;

 public:
  TCPClient(size_t buffer_size, const SocketAddress &remote_addr, int flags = 0,
            const std::optional<SocketAddress> &local_addr = std::nullopt);
  ~TCPClient() = default;

  ErrorCode Setup();

  int Send(unsigned char *buffer, size_t buffer_len) { return socket_->Send(buffer, buffer_len); }
  bool Receive(unsigned char *recv_data, std::chrono::microseconds timeout);

 private:
  SocketAddress remote_addr_;
  int flags_;
  std::optional<SocketAddress> local_addr_;
};

} // namespace os::core::udp::communication

#endif // OS_CORE_COMM_TCP_CLIENT_H
