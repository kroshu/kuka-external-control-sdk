// Copyright 2025 KUKA Hungaria Kft.
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

#include "kuka/external-control-sdk/kss/rsi/endpoint.h"

#include <cstring>

namespace kuka::external::control::kss::rsi {

bool Endpoint::Setup(const std::string& local_ip, unsigned short local_udp_port) {
  os::core::udp::communication::SocketAddress replier_address(local_ip, local_udp_port);

  return (replier_socket_ =
              std::make_unique<os::core::udp::communication::Replier>(replier_address))
             ->Setup() == 0;
}

bool Endpoint::ReceiveOrTimeout(std::chrono::milliseconds receive_request_timeout) {
  os::core::udp::communication::Replier::ErrorCode recv_ret = replier_socket_->ReceiveRequestOrTimeout(receive_request_timeout);
  if (recv_ret == os::core::udp::communication::Socket::ErrorCode::kSuccess) {
    memset(recv_msg_, '\0', kBufferSize);
    strncpy(recv_msg_, (const char*)replier_socket_->GetRequestMessage().first,
            replier_socket_->GetRequestMessage().second);
    return true;
  }
  return false;
}

std::string_view Endpoint::GetReceivedMessage() { return recv_msg_; }

bool Endpoint::MessageSend(std::string_view send_msg) {
  bool sendOK;
  std::size_t bytesSent;
  return replier_socket_->SendReply((uint8_t*)send_msg.begin(), send_msg.length()) ==
         os::core::udp::communication::Replier::ErrorCode::kSuccess;
}

void Endpoint::EmptyBuffer() {
  // Receive all messages until no message left in buffer
  if (replier_socket_->EmptyBuffer() !=
      os::core::udp::communication::Replier::ErrorCode::kSuccess) {
    throw "Failed emptying buffer";
  }
}

bool Endpoint::IsRequestActive() {
  return replier_socket_->IsRequestActive();
}

void Endpoint::Reset() {
  EmptyBuffer();
  replier_socket_->Reset();
}

}  // namespace kuka::external::control::kss
