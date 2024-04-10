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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/replier.h"

#include <cstring>

namespace os::core::udp::communication {

Replier::Replier(const SocketAddress& local_address) : local_address_(local_address) {
  memset(server_buffer_, 0, kMaxBufferSize);
}

Replier::ErrorCode Replier::Setup() {
  if (socket_.IsActive()) {
    return Replier::ErrorCode::kAlreadyActive;
  }
  int result = socket_.Map(0);
  if (result < 0) {
    return Replier::ErrorCode::kSocketError;
  }
  result = socket_.SetReuseAddress();
  if (result < 0) {
    return Replier::ErrorCode::kSocketError;
  }
  result = socket_.Bind(local_address_);
  if (result < 0) {
    return Replier::ErrorCode::kSocketError;
  }
  return Replier::ErrorCode::kSuccess;
}

void Replier::Reset() {
  active_request_ = false;
  last_request_size_ = 0;
}

Replier::ErrorCode Replier::ReceiveRequest() {
  return ReceiveRequestOrTimeout(std::chrono::microseconds(0));
}

Replier::ErrorCode Replier::ReceiveRequestOrTimeout(std::chrono::microseconds recv_timeout) {
  if (active_request_) {
    return Replier::ErrorCode::kError;
  }
  int recv_bytes = 0;
  if (recv_timeout.count() == 0) {
    recv_bytes = socket_.ReceiveFrom(last_remote_address_, server_buffer_, kMaxBufferSize);
  } else {
    recv_bytes = socket_.ReceiveFromOrTimeout(recv_timeout, last_remote_address_, server_buffer_,
                                              kMaxBufferSize);
  }

  if (recv_bytes >= 0) {
    last_request_size_ = recv_bytes;
    active_request_ = true;
    return Replier::ErrorCode::kSuccess;
  } else if (recv_bytes == Replier::ErrorCode::kTimeout) {
    active_request_ = false;
    return Replier::ErrorCode::kTimeout;
  } else {
    active_request_ = false;
    return Replier::ErrorCode::kSocketError;
  }
}

Replier::ErrorCode Replier::SendReply(uint8_t* reply_msg_data, size_t reply_msg_size) {
  if (!active_request_) {
    return Replier::ErrorCode::kError;
  }

  int ret = socket_.SendTo(last_remote_address_, reply_msg_data, reply_msg_size);

  if (ret > 0) {
    active_request_ = false;
    return Replier::ErrorCode::kSuccess;
  } else {
    return Replier::ErrorCode::kSocketError;
  }
}

std::pair<const uint8_t*, size_t> Replier::GetRequestMessage() const {
  return {server_buffer_, last_request_size_};
}

}  // namespace os::core::udp::communication
