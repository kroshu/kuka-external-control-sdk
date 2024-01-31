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

#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/secure_replier.h"

#include <sys/epoll.h>
#include <unistd.h>

namespace os::core::udp::communication {

SecureReplier::SecureReplier(const std::string& certificate_path,
                             const std::string& private_key_path,
                             const SocketAddress& local_address)
    : Replier(local_address)
    , server_socket_(SecureSocket::Mode::server, certificate_path, private_key_path) {
  memset(server_buffer_, 0, kMaxBufferSize);
}

SecureReplier::~SecureReplier() {
  thread_active_flag_.store(false);
  if (server_thread_ != nullptr && server_thread_->joinable()) {
    server_thread_->join();
  }
}

SecureReplier::ErrorCode SecureReplier::Setup() {
  if (server_socket_.IsActive()) {
    return SecureReplier::ErrorCode::kAlreadyActive;
  }

  epoll_fd_ = epoll_create(1);
  if (epoll_fd_ < 0) {
    return SecureReplier::ErrorCode::kError;
  }

  int result = server_socket_.Map(0);
  if (result < 0) {
    return SecureReplier::ErrorCode::kSocketError;
  }
  result = server_socket_.SetReuseAddress();
  if (result < 0) {
    return SecureReplier::ErrorCode::kSocketError;
  }

  result = server_socket_.SetReceiveTimeout(std::chrono::microseconds{1000});
  if (result < 0) {
    return SecureReplier::ErrorCode::kSocketError;
  }

  result = server_socket_.Bind(local_address_);
  if (result < 0) {
    return SecureReplier::ErrorCode::kSocketError;
  }

  result = server_socket_.DoHandshake();
  if (result < 0) {
    return SecureReplier::ErrorCode::kSecureLayerError;
  }

  thread_active_flag_.store(true);
  server_thread_ = std::make_unique<std::thread>(&SecureReplier::Serve, this);
  return SecureReplier::ErrorCode::kSuccess;
}

void SecureReplier::Reset() {
  active_request_ = false;
  last_request_size_ = 0;
}

SecureReplier::ErrorCode SecureReplier::ReceiveRequest() {
  return ReceiveRequestOrTimeout(std::chrono::microseconds(0));
}

SecureReplier::ErrorCode SecureReplier::ReceiveRequestOrTimeout(
    std::chrono::microseconds recv_timeout) {
  if (active_request_) {
    return SecureReplier::ErrorCode::kError;
  }
  while (true) {
    last_active_socket_ = nullptr;
    struct epoll_event event;
    int result = epoll_wait(epoll_fd_, &event, 1,
                            ((recv_timeout.count() == 0) ? -1 : recv_timeout.count() / 1000));
    // TODO: think over whether return error or just sink them
    if (result == 0) {
      return Replier::ErrorCode::kTimeout;
    } else if (result < 0) {
      return Replier::ErrorCode::kError;
    } else {
      last_active_socket_ = (SecureSocket*)event.data.ptr;
      auto recv_bytes = last_active_socket_->Receive(server_buffer_, kMaxBufferSize);
      if (recv_bytes >= 0) {
        last_request_size_ = recv_bytes;
        active_request_ = true;
        return Replier::ErrorCode::kSuccess;
      } else if (recv_bytes == Replier::ErrorCode::kTimeout) {
        return Replier::ErrorCode::kTimeout;
      } else if (recv_bytes == Replier::ErrorCode::kClosed) {
        // auto r = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, last_active_socket_->GetSocketFd(),
        // nullptr);
        continue;
      } else {
        return Replier::ErrorCode::kSocketError;
      }
    }
  }
}

SecureReplier::ErrorCode SecureReplier::SendReply(uint8_t* reply_msg_data, size_t reply_msg_size) {
  if (!active_request_) {
    return SecureReplier::ErrorCode::kError;
  }
  int ret = last_active_socket_->Send(reply_msg_data, reply_msg_size);
  if (ret > 0) {
    active_request_ = false;
    return Replier::ErrorCode::kSuccess;
  } else {
    return Replier::ErrorCode::kSocketError;
  }
}

void SecureReplier::Serve() {
  while (thread_active_flag_.load(std::memory_order_relaxed)) {
    auto accepted_socket = server_socket_.Accept();

    if (accepted_socket) {
      struct epoll_event event;
      event.data.ptr = accepted_socket.get();
      event.events = EPOLLIN | EPOLLET;
      auto r = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, accepted_socket->GetSocketFd(), &event);
      if (r < 0) {
        continue;
      }
      std::lock_guard<std::mutex> lck(mutex_);
      accepted_connections_.emplace_back(std::move(accepted_socket));
    } else {
      if (server_socket_.GetLastSocketError().first == ErrorCode::kSocketError &&
          server_socket_.GetLastSocketError().second == EAGAIN) {
        continue;
      } else {
        if (server_error_callback_ != nullptr) {
          if (server_error_callback_(*this)) {
            Terminate();
          }
        }
      }
    }
  }
}

}  // namespace os::core::udp::communication
