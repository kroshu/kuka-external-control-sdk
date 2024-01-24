// This material is the exclusive property of KUKA Deutschland GmbH.
// Except as expressly permitted by separate agreement, this material may only
// be used by members of the development department of KUKA Deutschland GmbH for
// internal development purposes of KUKA Deutschland GmbH.
//
// Copyright (C)
// KUKA Deutschland GmbH, Germany. All Rights Reserved.

#ifndef OS_CORE_COMM_UDP_PUBLISHER_H
#define OS_CORE_COMM_UDP_PUBLISHER_H

#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication {

class Publisher {
 public:
  typedef Socket::ErrorCode ErrorCode;

 public:
  Publisher(const SocketAddress& pub_address, const SocketAddress& interface_address,
            bool is_multicast);
  virtual ~Publisher() = default;
  ErrorCode Setup();

  ErrorCode Send(const uint8_t* msg_data, uint16_t msg_size);
  bool SetTTL(int ttl);

 public:
  const SocketAddress& Address() const { return pub_address_; }
  bool IsMulticast() const { return is_multicast_; }

 protected:
  Socket socket_;
  SocketAddress pub_address_;
  SocketAddress interface_address_;
  const bool is_multicast_;
};
}  // namespace os::core::udp::communication

#endif  // OS_CORE_COMM_UDP_PUBLISHER_H
