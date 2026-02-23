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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_INITIALIZATION_DATA_H_
#define KUKA_EXTERNAL_CONTROL__KSS_INITIALIZATION_DATA_H_

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss
{

struct InitializationData
{
  InitializationData() = default;
  InitializationData(uint8_t num_ax, uint8_t num_ext_ax)
  : num_axes(num_ax), num_external_axes(num_ext_ax)
  {
  }

  virtual ~InitializationData() = default;  // makes it polymorphic

  uint8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }

  uint8_t num_axes = 0;
  uint8_t num_external_axes = 0;
};

class IEventHandlerExtension
{
public:
  virtual void OnConnected(const InitializationData & init_data) = 0;
};

}  // namespace kuka::external::control::kss
#endif  // KUKA_EXTERNAL_CONTROL__KSS_INITIALIZATION_DATA_H_
