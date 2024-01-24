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

#include "kuka/external-control-sdk/common/operation_status.h"

#include <cstring>

namespace kuka::external::control {

OperationStatus::OperationStatus(grpc::Status grpc_status) {
  switch (grpc_status.error_code()) {
    case grpc::StatusCode::OK:
      return_code = ReturnCode::OK;
      break;
    default:
      return_code = ReturnCode::ERROR;
  }
  strcpy(message, grpc_status.error_message().c_str());
}

OperationStatus::OperationStatus(os::core::udp::communication::Socket::ErrorCode code) {
  using namespace os::core::udp::communication;
  char errno_msg[256] = "Socket error: ";

  switch (code) {
    case Socket::ErrorCode::kSuccess:
      return_code = ReturnCode::OK;
      break;
    case Socket::ErrorCode::kTimeout:
      strcpy(message, "Timeout: operation did not finish in time.");
      return_code = ReturnCode::TIMEOUT;
      break;
    case Socket::ErrorCode::kSocketError:
      // TODO is there a better solution to provide the errno msg here?
      // errno_msg += std::strerror(errno);
      strcpy(message, strcat(errno_msg, std::strerror(errno)));
      return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kAlreadyActive:
      strcpy(message, "Error: socket already active.");
      return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kNotBound:
      strcpy(message, "Error: socket not bound.");
      return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kNotConnected:
      strcpy(message, "Error: socket not connected.");
      return_code = ReturnCode::ERROR;
      break;
    case Socket::ErrorCode::kClosed:
      strcpy(message, "Error: socket closed.");
      return_code = ReturnCode::ERROR;
      break;
    default:
      strcpy(message, "Request - Reply pattern broken.");
      return_code = ReturnCode::ERROR;
  }
}

OperationStatus::OperationStatus(ReturnCode param_return_code, const char* param_message) {
  return_code = param_return_code;
  strcpy(&message[0], param_message);
}

}  // namespace kuka::external::control
