// This material is the exclusive property of KUKA Deutschland GmbH.
// Except as expressly permitted by separate agreement, this material may only
// be used by members of the development department of KUKA Deutschland GmbH for
// internal development purposes of KUKA Deutschland GmbH.
//
// Copyright (C)
// KUKA Deutschland GmbH, Germany. All Rights Reserved.

#include "kuka/external-control-sdk/utils/os-core-udp-communication/tcp_client.h"

#include <cstring>

namespace os::core::udp::communication {

int TCPClientSocket::Map(int flags) {
  if (IsActive()) {
    return SetError(ErrorCode::kAlreadyActive);
  }
  socket_fd_ = socket(AF_INET, SOCK_STREAM, flags);
  if (socket_fd_ < 0) {
    SetError(kSocketError);
  }
  return socket_fd_;
}

TCPClient::TCPClient(size_t buffer_size,
                     const os::core::udp::communication::SocketAddress& remote_addr, int flags)
    : Dissector(std::make_shared<TCPClientSocket>(), buffer_size)
    , remote_addr_(remote_addr)
    , flags_(flags) {
  // TODO check whether we need to try to reconnect multiple times
}

TCPClient::ErrorCode TCPClient::Setup() {
  if (socket_->IsActive()) {
    return TCPClient::ErrorCode::kAlreadyActive;
  }
  int result = socket_->Map(flags_);
  if (result < 0) {
    return TCPClient::ErrorCode::kSocketError;
  }
  result = socket_->SetReuseAddress();
  if (result < 0) {
    return TCPClient::ErrorCode::kSocketError;
  }
  result = socket_->Connect(remote_addr_);
  if (result < 0) {
    return TCPClient::ErrorCode::kSocketError;
  }
  return TCPClient::ErrorCode::kSuccess;
}

bool TCPClient::Receive(unsigned char* recv_data, std::chrono::microseconds timeout) {
  raw_message_t message;
  int receive_state = ReceiveOrTimeout(timeout, message);
  int received_bytes = message.second;

  if (receive_state < 0 ||
      (receive_state == os::core::udp::communication::Socket::ErrorCode::kSuccess &&
       received_bytes == 0)) {
    // TODO handle different errors
    return false;
  } else {
    memcpy(recv_data, message.first, message.second);
    return true;
  }
}

}  // namespace os::core::udp::communication
