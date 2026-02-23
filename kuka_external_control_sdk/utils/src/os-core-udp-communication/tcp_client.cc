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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/tcp_client.h"

#include <cstring>

namespace os::core::udp::communication
{

int TCPClientSocket::Map(int flags)
{
  if (IsActive())
  {
    return SetError(ErrorCode::kAlreadyActive);
  }
  socket_fd_ = socket(AF_INET, SOCK_STREAM, flags);
  if (socket_fd_ < 0)
  {
    SetError(kSocketError);
  }
  return socket_fd_;
}

TCPClient::TCPClient(
  size_t buffer_size, const os::core::udp::communication::SocketAddress & remote_addr, int flags,
  const std::optional<os::core::udp::communication::SocketAddress> & local_addr)
: Dissector(std::make_shared<TCPClientSocket>(), buffer_size),
  remote_addr_(remote_addr),
  flags_(flags),
  local_addr_(local_addr)
{
  // TODO check whether we need to try to reconnect multiple times
}

TCPClient::ErrorCode TCPClient::Setup()
{
  if (socket_->IsActive())
  {
    return TCPClient::ErrorCode::kAlreadyActive;
  }
  int result = socket_->Map(flags_);
  if (result < 0)
  {
    return TCPClient::ErrorCode::kSocketError;
  }
  result = socket_->SetReuseAddress();
  if (result < 0)
  {
    return TCPClient::ErrorCode::kSocketError;
  }
  if (local_addr_.has_value())
  {
    result = socket_->Bind(*local_addr_);
    if (result < 0)
    {
      return TCPClient::ErrorCode::kSocketError;
    }
  }
  result = socket_->Connect(remote_addr_);
  if (result < 0)
  {
    return TCPClient::ErrorCode::kSocketError;
  }
  return TCPClient::ErrorCode::kSuccess;
}

bool TCPClient::Receive(unsigned char * recv_data, std::chrono::microseconds timeout)
{
  raw_message_t message;
  int receive_state = ReceiveOrTimeout(timeout, message);
  int received_bytes = message.second;

  if (
    receive_state < 0 ||
    (receive_state == os::core::udp::communication::Socket::ErrorCode::kSuccess &&
     received_bytes == 0))
  {
    // TODO handle different errors
    return false;
  }

  memcpy(recv_data, message.first, message.second);
  return true;
}

}  // namespace os::core::udp::communication
