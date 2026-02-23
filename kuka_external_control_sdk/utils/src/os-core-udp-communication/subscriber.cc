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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"

namespace os::core::udp::communication
{

Subscriber::Subscriber(
  const SocketAddress & sub_address, const SocketAddress & interface_address, bool is_multicast)
: sub_address_(sub_address), interface_address_(interface_address), is_multicast_(is_multicast)
{
}

Subscriber::ErrorCode Subscriber::Setup()
{
  if (socket_.IsActive())
  {
    return Subscriber::ErrorCode::kAlreadyActive;
  }
  int result = socket_.Map(0);
  if (result < 0)
  {
    return Subscriber::ErrorCode::kSocketError;
  }

  result = socket_.SetReceiveBufferSize(kRecvBufferSize);
  if (result < 0)
  {
    return Subscriber::ErrorCode::kSocketError;
  }

  result = socket_.SetReuseAddress();
  if (result < 0)
  {
    return Subscriber::ErrorCode::kSocketError;
  }

  if (is_multicast_)
  {
    result = socket_.JoinMulticastGroup(sub_address_, interface_address_);
    if (result < 0)
    {
      return Subscriber::ErrorCode::kSocketError;
    }
  }

  result = socket_.Bind(SocketAddress(sub_address_.Port()));
  if (result < 0)
  {
    return Subscriber::ErrorCode::kSocketError;
  }

  return Subscriber::ErrorCode::kSuccess;
}

Subscriber::ErrorCode Subscriber::Receive()
{
  received_msg_size_ = socket_.Receive(recv_buffer_, kMaxBufferSize);

  if (received_msg_size_ >= 0)
  {
    return Subscriber::ErrorCode::kSuccess;
  }
  else if (received_msg_size_ == Subscriber::ErrorCode::kTimeout)
  {
    return Subscriber::ErrorCode::kTimeout;
  }
  else
  {
    return Subscriber::ErrorCode::kSocketError;
  }
}

Subscriber::ErrorCode Subscriber::ReceiveAllArrived()
{
  int peek_size;
  received_msg_size_ = peek_size = socket_.Receive(recv_buffer_, kMaxBufferSize);
  while (peek_size > 0)
  {
    peek_size = socket_.Receive(recv_buffer_, kMaxBufferSize, MSG_DONTWAIT);
    if (peek_size > 0)
    {
      received_msg_size_ = peek_size;
    }
  }

  if (received_msg_size_ >= 0)
  {
    return Subscriber::ErrorCode::kSuccess;
  }
  else if (received_msg_size_ == Subscriber::ErrorCode::kTimeout)
  {
    return Subscriber::ErrorCode::kTimeout;
  }
  else
  {
    return Subscriber::ErrorCode::kSocketError;
  }
}

Subscriber::ErrorCode Subscriber::WaitForAndReceive(std::chrono::microseconds recv_timeout)
{
  received_msg_size_ = socket_.ReceiveOrTimeout(recv_timeout, recv_buffer_, kMaxBufferSize);

  if (received_msg_size_ >= 0)
  {
    return Subscriber::ErrorCode::kSuccess;
  }
  else if (received_msg_size_ == Subscriber::ErrorCode::kTimeout)
  {
    return Subscriber::ErrorCode::kTimeout;
  }
  else
  {
    return Subscriber::ErrorCode::kSocketError;
  }
}

Subscriber::ErrorCode Subscriber::WaitForAndReceiveAllArrived(
  std::chrono::microseconds recv_timeout)
{
  int peek_size;
  received_msg_size_ = peek_size =
    socket_.ReceiveOrTimeout(recv_timeout, recv_buffer_, kMaxBufferSize);

  while (peek_size > 0)
  {
    peek_size = socket_.Receive(recv_buffer_, kMaxBufferSize, MSG_DONTWAIT);
    if (peek_size > 0)
    {
      received_msg_size_ = peek_size;
    }
  }

  if (received_msg_size_ >= 0)
  {
    return Subscriber::ErrorCode::kSuccess;
  }
  else if (received_msg_size_ == Subscriber::ErrorCode::kTimeout)
  {
    return Subscriber::ErrorCode::kTimeout;
  }
  else
  {
    return Subscriber::ErrorCode::kSocketError;
  }
}

std::pair<const uint8_t *, size_t> Subscriber::GetMessage() const
{
  return {recv_buffer_, received_msg_size_};
}

}  // namespace os::core::udp::communication
