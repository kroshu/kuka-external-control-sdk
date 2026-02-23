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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_STATUS_UPDATE_H_
#define KUKA_EXTERNAL_CONTROL__KSS_STATUS_UPDATE_H_

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss
{

struct StatusUpdate
{
  void Reset()
  {
    control_mode_ = ControlMode::UNSPECIFIED;
    cycle_time_ = CycleTime::UNSPECIFIED;
    drives_powered_ = false;
    emergency_stop_ = false;
    guard_stop_ = false;
    in_motion_ = false;
    motion_possible_ = false;
    operation_mode_ = OperationMode::UNSPECIFIED;
    robot_stopped_ = false;
  }

  bool operator==(const StatusUpdate & other) const noexcept
  {
    return std::tie(
             control_mode_, cycle_time_, drives_powered_, emergency_stop_, guard_stop_, in_motion_,
             motion_possible_, operation_mode_, robot_stopped_) ==
           std::tie(
             other.control_mode_, other.cycle_time_, other.drives_powered_, other.emergency_stop_,
             other.guard_stop_, other.in_motion_, other.motion_possible_, other.operation_mode_,
             robot_stopped_);
  }

  bool operator!=(const StatusUpdate & other) const noexcept { return !(*this == other); }

  ControlMode control_mode_;
  CycleTime cycle_time_;
  bool drives_powered_;
  bool emergency_stop_;
  bool guard_stop_;
  bool in_motion_;
  bool motion_possible_;
  OperationMode operation_mode_;
  bool robot_stopped_;
};

class IStatusUpdateHandler
{
public:
  virtual void OnStatusUpdateReceived(const StatusUpdate & response) = 0;
};

}  // namespace kuka::external::control::kss
#endif  // KUKA_EXTERNAL_CONTROL__KSS_STATUS_UPDATE_H_
