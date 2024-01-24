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

#include "test-assets/os-core-udp-communication/requester.h"

//#HOWTO: how to handle error logs?

namespace os::core::udp::communication {

Requester::Requester(const SocketAddress& local_address, const SocketAddress& replier_address)
    : local_address_(local_address), replier_address_(replier_address) {}

Requester::ErrorCode Requester::Setup() {
  if (!socket_) {
    socket_ = std::make_unique<Socket>();
  }
  if (socket_->IsActive()) {
    return Requester::ErrorCode::kAlreadyActive;
  }
  int result = socket_->Map(0);
  if (result < 0) {
    return Requester::ErrorCode::kSocketError;
  }
  result = socket_->SetReuseAddress();
  if (result < 0) {
    return Requester::ErrorCode::kSocketError;
  }
  result = socket_->Bind(local_address_);
  if (result < 0) {
    return Requester::ErrorCode::kSocketError;
  }
  result = socket_->Connect(replier_address_);
  if (result < 0) {
    return Requester::ErrorCode::kSocketError;
  }
  return (Requester::ErrorCode)socket_->DoHandshake();
}

void Requester::Reset() {
  active_request_ = false;
  last_reply_size_ = 0;
}

Requester::ErrorCode Requester::SendRequest(uint8_t* req_msg_data, size_t req_msg_size) {
  return SendRequestOrTimeout(req_msg_data, req_msg_size, std::chrono::microseconds(0));
}

Requester::ErrorCode Requester::SendRequestOrTimeout(uint8_t* req_msg_data, size_t req_msg_size,
                                                     std::chrono::microseconds send_timeout) {
  if (active_request_) {
    return Requester::ErrorCode::kError;
  }
  auto time_start_send = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());

  StartSending(time_start_send, req_msg_data, req_msg_size);

  auto sent_bytes = socket_->Send(req_msg_data, req_msg_size, MSG_DONTWAIT);

  auto time_stop_send = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
  Requester::ErrorCode send_op_result;
  send_op_result = sent_bytes >= 0 ? Requester::ErrorCode::kSuccess
                                   : (sent_bytes == Requester::ErrorCode::kTimeout
                                          ? Requester::ErrorCode::kTimeout
                                          : Requester::ErrorCode::kError);
  StopSending(time_stop_send, send_op_result);

  if (sent_bytes < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      // if(send_timeout.count() != 0) -- avoid unnecessary select
      auto result = socket_->Select(send_timeout, false);
      if (result == 0) {
        return Requester::ErrorCode::kTimeout;
      } else if (result < 0) {
        return Requester::ErrorCode::kSocketError;
      } else {
        // socket got writable, try again
        sent_bytes = socket_->Send(req_msg_data, req_msg_size, MSG_DONTWAIT);
      }
    } else {
      return Requester::ErrorCode::kSocketError;
    }
  }

  if (sent_bytes >= 0) {
    active_request_ = true;
    return Requester::ErrorCode::kSuccess;
  } else {
    return Requester::ErrorCode::kSocketError;
  }

  return Requester::ErrorCode::kError;
}

Requester::ErrorCode Requester::ReceiveReply() {
  return ReceiveReplyOrTimeout(std::chrono::microseconds(0));
}

Requester::ErrorCode Requester::ReceiveReplyOrTimeout(std::chrono::microseconds recv_timeout) {
  if (!active_request_) {
    return Requester::ErrorCode::kError;
  }
  int recv_bytes = 0;

  auto time_start_recv = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
  StartReceiving(time_start_recv);
  if (recv_timeout.count() == 0) {
    recv_bytes = socket_->Receive(reply_buffer_, kMaxBufferSize);
  } else {
    recv_bytes = socket_->ReceiveOrTimeout(recv_timeout, reply_buffer_, kMaxBufferSize);
  }
  auto time_stop_recv = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
  Requester::ErrorCode recv_op_result;
  recv_op_result = recv_bytes >= 0 ? Requester::ErrorCode::kSuccess
                                   : (recv_bytes == Requester::ErrorCode::kTimeout
                                          ? Requester::ErrorCode::kTimeout
                                          : Requester::ErrorCode::kError);
  StopReceiving(time_stop_recv, reply_buffer_, recv_bytes, recv_op_result);

  if (recv_bytes >= 0) {
    last_reply_size_ = recv_bytes;
    active_request_ = false;
    return Requester::ErrorCode::kSuccess;
  } else if (recv_bytes == Requester::ErrorCode::kTimeout) {
    return Requester::ErrorCode::kTimeout;
  } else {
    return Requester::ErrorCode::kSocketError;
  }
}

Requester::ErrorCode Requester::ReceiveReplyAll() {
  if (!active_request_) {
    return Requester::ErrorCode::kError;
  }
  int recv_bytes = 0;
  int peek_size;
  recv_bytes = socket_->Receive(reply_buffer_, kMaxBufferSize);

  recv_bytes = peek_size = socket_->Receive(reply_buffer_, kMaxBufferSize);
  while (peek_size > 0) {
    peek_size = socket_->Receive(reply_buffer_, kMaxBufferSize, MSG_DONTWAIT);
    if (peek_size > 0) {
      recv_bytes = peek_size;
    }
  }

  if (recv_bytes >= 0) {
    last_reply_size_ = recv_bytes;
    active_request_ = false;
    return Requester::ErrorCode::kSuccess;
  } else if (recv_bytes == Requester::ErrorCode::kTimeout) {
    return Requester::ErrorCode::kTimeout;
  } else {
    return Requester::ErrorCode::kSocketError;
  }
}

Requester::ErrorCode Requester::ReceiveReplyAllOrTimeout(std::chrono::microseconds recv_timeout) {
  if (!active_request_) {
    return Requester::ErrorCode::kError;
  }

  int recv_bytes = 0;
  int peek_size;
  recv_bytes = peek_size = socket_->ReceiveOrTimeout(recv_timeout, reply_buffer_, kMaxBufferSize);

  while (peek_size > 0) {
    peek_size = socket_->Receive(reply_buffer_, kMaxBufferSize, MSG_DONTWAIT);
    if (peek_size > 0) {
      recv_bytes = peek_size;
    }
  }

  if (recv_bytes >= 0) {
    last_reply_size_ = recv_bytes;
    active_request_ = false;
    return Requester::ErrorCode::kSuccess;
  } else if (recv_bytes == Requester::ErrorCode::kTimeout) {
    return Requester::ErrorCode::kTimeout;
  } else {
    return Requester::ErrorCode::kSocketError;
  }
}

std::pair<const uint8_t*, size_t> Requester::GetReplyMessage() const {
  return {reply_buffer_, last_reply_size_};
}

}  // namespace os::core::udp::communication
