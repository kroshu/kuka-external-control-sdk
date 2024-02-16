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

#ifndef KUKA_EXTERNAL_CONTROL__OPERATION_STATUS_H_
#define KUKA_EXTERNAL_CONTROL__OPERATION_STATUS_H_

#include <grpcpp/impl/codegen/status.h>
#include <string.h>

#include "kuka/external-control-sdk/iiqka/utils/os-core-udp-communication/socket.h"

namespace kuka::external::control {
enum class ReturnCode { UNSPECIFIED, OK, WARN, ERROR, TIMEOUT };

struct OperationStatus {
  OperationStatus() = default;
  OperationStatus(ReturnCode, const char* = "\0");

  ReturnCode return_code = ReturnCode::UNSPECIFIED;
  char message[256] = {};
};

}  // namespace kuka::external::control

#endif  // KUKA_EXTERNAL_CONTROL__OPERATION_STATUS_H_
