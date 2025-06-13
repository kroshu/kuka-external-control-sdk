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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_IROBOT_H_
#define KUKA_EXTERNAL_CONTROL__KSS_IROBOT_H_

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/extension.h"

namespace kuka::external::control::kss {

class IRobot : public kuka::external::control::IRobot {
 public:
  virtual Status TurnOnDrives() = 0;

  virtual Status TurnOffDrives() = 0;

  virtual Status SetCycleTime(CycleTime cycle_time) = 0;

  virtual Status RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) = 0;

  virtual Status RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler>&& handler) = 0;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_IROBOT_H_
