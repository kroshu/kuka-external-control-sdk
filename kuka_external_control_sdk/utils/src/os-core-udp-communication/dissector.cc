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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/dissector.h"

#include <string.h>
#include <unistd.h>

namespace os::core::udp::communication
{

Dissector::Dissector(std::shared_ptr<Socket> socket, size_t buffer_size)
: socket_(std::move(socket)), buffer_(buffer_size, '\0'), maximum_buffer_size_(buffer_size)
{
}

Socket::ErrorCode Dissector::Receive(raw_message_t & message, int flags)
{
  const static std::chrono::microseconds blocking_time(Socket::kBlockingTimeout);
  return ReceiveOrTimeout(blocking_time, message, flags);
}

Socket::ErrorCode Dissector::ReceiveOrTimeout(
  const std::chrono::microseconds & timeout, raw_message_t & message, int flags)
{
  message.first = nullptr;
  message.second = 0;
  // if no data in buffer then try to receive data
  bool partial = false;
  auto recv_cursor = Cursor();
  auto start_time = std::chrono::steady_clock::now();
  auto current_timeout = timeout;

  while (true)
  {
    int received_bytes = 0;

    if (data_length_ == 0 || partial)
    {
      // still partial message but no more time (to lose)
      if (timeout.count() >= 0 && current_timeout.count() < 0)
      {
        return Socket::ErrorCode::kTimeout;
      }
      int result = socket_->ReceiveOrTimeout(
        current_timeout, (unsigned char *)recv_cursor, maximum_buffer_size_ - data_length_, flags);

      // TODO: according some logic move back data to pos#0, maybe at message processing
      if (result <= 0)
      {
        data_cursor_ = 0;
        data_length_ = 0;
        return static_cast<Socket::ErrorCode>(result);
      }

      // for timeout case we have to handle multiple partial receive so timeout must be decreased
      // with the elapsed time
      if (timeout.count() >= 0)
      {
        current_timeout = timeout - std::chrono::duration_cast<std::chrono::microseconds>(
                                      std::chrono::steady_clock::now() - start_time);
      }

      received_bytes = result;
      data_length_ += received_bytes;
    }

    int msg_len = Dissect(Cursor(), data_length_);
    if (msg_len < 0)
    {
      data_cursor_ = 0;
      data_length_ = 0;
      return Socket::ErrorCode::kInvalidMessage;
    }
    else if (msg_len <= data_length_)
    {
      // we have a message here
      partial = false;
      message.first = Cursor();
      message.second = msg_len;
      data_length_ -= msg_len;
      if (data_length_ == 0)
      {
        data_cursor_ = 0;
      }
      else
      {
        data_cursor_ += msg_len;
      }

      return Socket::ErrorCode::kSuccess;
    }
    else
    {
      // we have a partial message here
      partial = true;
      recv_cursor = recv_cursor + received_bytes;
      continue;
    }
  }
}

DynamicDissector::DynamicDissector(
  std::shared_ptr<Socket> socket, size_t buffer_size, std::function<dissector_fn_t> dissector_fn)
: Dissector(std::move(socket), buffer_size), message_dissector_fn_(dissector_fn)
{
}

}  // namespace os::core::udp::communication
