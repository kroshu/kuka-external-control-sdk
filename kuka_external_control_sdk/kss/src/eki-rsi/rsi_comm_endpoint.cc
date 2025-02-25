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

#include "kuka/external-control-sdk/kss/eki-rsi/rsi_comm_endpoint.h"

#include <cstring>

namespace kuka::external::control::kss {

bool RSICommEndpoint::Setup(unsigned short local_udp_port) {
  os::core::udp::communication::SocketAddress replier_address(local_udp_port);

  return (replier_socket_ =
              std::make_unique<os::core::udp::communication::Replier>(replier_address))
             ->Setup() == 0;
}

bool RSICommEndpoint::ReceiveOrTimeout(std::chrono::milliseconds receive_request_timeout) {
  // TODO implement recv with timeout
  std::size_t total_bytes_recv = 0;
  std::size_t bytes_recv = 0;
  bool checkForMore = true;
  // Get all buffered data. (In case delays happened there could be multiple packets)

  auto recv_ret = replier_socket_->ReceiveRequestOrTimeout(receive_request_timeout);
  if (recv_ret == os::core::udp::communication::Socket::ErrorCode::kSuccess) {
    memset(recv_msg_, '\0', 1024);
    strncpy(recv_msg_, (const char*)replier_socket_->GetRequestMessage().first,
            replier_socket_->GetRequestMessage().second);
    return true;
  }
  return false;
}

std::string_view RSICommEndpoint::GetReceivedMessage() { return recv_msg_; }

bool RSICommEndpoint::MessageSend(std::string_view send_msg) {
  bool sendOK;
  std::size_t bytesSent;
  return replier_socket_->SendReply((uint8_t*)send_msg.begin(), send_msg.length()) ==
         os::core::udp::communication::Replier::ErrorCode::kSuccess;
}

}  // namespace kuka::external::control::kss
