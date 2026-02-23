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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__TCP_CLIENT_H_
#define KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__TCP_CLIENT_H_

#include "kuka/external-control-sdk/utils/os-core-udp-communication/dissector.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication
{

class TCPClientSocket : public Socket
{
public:
  /* creates a new socket with the given `flags`, and returns the underlying
   * socket identifier */
  int Map(int flags = 0) override;
};

class TCPClient : public Dissector
{
public:
  typedef Socket::ErrorCode ErrorCode;

public:
  TCPClient(
    size_t buffer_size, const SocketAddress & remote_addr, int flags = 0,
    const std::optional<SocketAddress> & local_addr = std::nullopt);
  ~TCPClient() = default;

  ErrorCode Setup();

  int Send(unsigned char * buffer, size_t buffer_len) { return socket_->Send(buffer, buffer_len); }
  bool Receive(unsigned char * recv_data, std::chrono::microseconds timeout);

private:
  SocketAddress remote_addr_;
  int flags_;
  std::optional<SocketAddress> local_addr_;
};

}  // namespace os::core::udp::communication

#endif  // KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__TCP_CLIENT_H_
