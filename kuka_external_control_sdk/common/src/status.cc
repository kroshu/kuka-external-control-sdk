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

#include <cstring>

#include "kuka/external-control-sdk/common/status.h"

namespace kuka::external::control {

Status::Status(ReturnCode param_return_code, const char* param_message) {
  return_code = param_return_code;
  strcpy(&message[0], param_message);
}

}  // namespace kuka::external::control
