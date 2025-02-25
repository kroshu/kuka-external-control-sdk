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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_RSI_COMM_ENDPOINT_H_
#define KUKA_EXTERNAL_CONTROL__KSS_RSI_COMM_ENDPOINT_H_

#include <memory>
#include <string>

#include "kuka/external-control-sdk/common/status.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/replier.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"

namespace kuka::external::control::kss {

/**
 * @brief The RSICommEndpoint class handles RSI communication to the Kuka
 * which uses a UDP Server for communication and XML formatted packets for data exchange
 * by the ETHERNET object in RSI.
 */
class RSICommEndpoint {
 public:
  bool Setup(unsigned short local_udp_port);

  bool ReceiveOrTimeout(std::chrono::milliseconds receive_request_timeout);

  std::string_view GetReceivedMessage();

  bool MessageSend(std::string_view send_msg);

 private:
  std::unique_ptr<os::core::udp::communication::Replier> replier_socket_{nullptr};

  char recv_msg_[1024];
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_RSI_COMM_ENDPOINT_H_
