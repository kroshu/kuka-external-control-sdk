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

#ifndef OS_CORE_COMM_UDP_SECURE_REPLIER_H
#define OS_CORE_COMM_UDP_SECURE_REPLIER_H

#include <atomic>
#include <chrono>
#include <functional>
#include <list>
#include <mutex>
#include <thread>

#include "replier.h"
#include "secure_socket.h"

namespace os::core::udp::communication
{

class SecureReplier : public Replier
{
public:
  using error_callback_t = std::function<bool(SecureReplier &)>;

public:  //<ctor>
  SecureReplier(
    const std::string & certificate_path, const std::string & private_key_path,
    const SocketAddress & local_address);
  virtual ~SecureReplier();
  virtual ErrorCode Setup() override;
  virtual void Reset() override;
  SecureReplier & SetServerErrorCallback(const error_callback_t & callback)
  {
    server_error_callback_ = callback;
    return *this;
  }

public:  //<Replier>
  virtual ErrorCode ReceiveRequest() override;
  virtual ErrorCode ReceiveRequestOrTimeout(std::chrono::microseconds recv_timeout) override;
  virtual ErrorCode SendReply(uint8_t * reply_msg_data, size_t reply_msg_size) override;

protected:  //<operations>
  void Serve();
  void Terminate() { thread_active_flag_.store(false); }

public:
  SecureSocket & Socket() { return server_socket_; }
  const SecureSocket & Socket() const { return server_socket_; }

protected:
  SecureSocket server_socket_;
  error_callback_t server_error_callback_{nullptr};

  std::mutex mutex_;
  std::atomic<bool> thread_active_flag_ = false;
  std::unique_ptr<std::thread> server_thread_;

  int epoll_fd_;
  std::list<std::unique_ptr<SecureSocket>> accepted_connections_;

  SecureSocket * last_active_socket_ = nullptr;
};
}  // namespace os::core::udp::communication

#endif  // OS_CORE_COMM_UDP_SECURE_REPLIER_H
