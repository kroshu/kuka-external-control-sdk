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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/publisher.h"

#include <cstring>

namespace os::core::udp::communication {

Publisher::Publisher(const SocketAddress& pub_address, const SocketAddress& interface_address,
                     bool is_multicast)
    : pub_address_(pub_address)
    , interface_address_(interface_address)
    , is_multicast_(is_multicast) {}

Publisher::ErrorCode Publisher::Setup() {
  if (socket_.IsActive()) {
    return Publisher::ErrorCode::kAlreadyActive;
  }
  int result = socket_.Map(0);
  if (result < 0) {
    return Publisher::ErrorCode::kSocketError;
  }
  result = socket_.Bind(interface_address_);
  if (result < 0) {
    return Publisher::ErrorCode::kSocketError;
  }
  return Publisher::ErrorCode::kSuccess;
}

Publisher::ErrorCode Publisher::Send(const uint8_t* msg_data, uint16_t msg_size) {
  int sent_bytes = socket_.SendTo(pub_address_, msg_data, msg_size);

  if (sent_bytes >= 0) {
    return Publisher::ErrorCode::kSuccess;
  } else {
    return Publisher::ErrorCode::kSocketError;
  }
}

bool Publisher::SetTTL(int ttl) {
  return is_multicast_ ? socket_.SetTTLForMulticast(ttl) == 0 : socket_.SetTTLForUnicast(ttl) == 0;
}

}  // namespace os::core::udp::communication
