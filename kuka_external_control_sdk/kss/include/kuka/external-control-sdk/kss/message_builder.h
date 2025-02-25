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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_

#include <math.h>

#include <algorithm>
#include <cstring>
#include <optional>
#include <string>

#include "kuka/external-control-sdk/common/message_builder.h"

namespace kuka::external::control::kss {

class MotionState : public BaseMotionState {
 public:
  MotionState(std::size_t dof) : BaseMotionState(dof) {
    measured_positions_.resize(dof);
    measured_torques_.resize(dof);
    measured_velocities_.resize(dof);
  }

  MotionState& operator=(const std::array<double, 6>& arr) {
    std::copy_n(arr.cbegin(), dof_, measured_positions_.begin());
    has_positions_ = true;
    return *this;
  }
};

class ControlSignal : public BaseControlSignal {
 public:
  ControlSignal(std::size_t dof) : BaseControlSignal(dof) {
    joint_position_values_.resize(dof, 0.0);
  }

  std::optional<std::string_view> GetXMLString(std::string_view format, int last_ipoc,
                                               MotionState& initial_position,
                                               bool stop_control = false) {
    // Reset the string to enable doubles with different precisions. (TODO: reset only 'ret'  number
    // of characters)
    std::memset(xml_string_, 0, sizeof(xml_string_));

    if (has_positions_) {
      std::transform(joint_position_values_.begin(), joint_position_values_.end(),
                     initial_position.GetMeasuredPositions().cbegin(),
                     joint_position_values_.begin(), std::minus<double>());
    }

    int ret = snprintf(xml_string_, sizeof(xml_string_), format.data(), joint_position_values_[0],
                       joint_position_values_[1], joint_position_values_[2],
                       joint_position_values_[3], joint_position_values_[4],
                       joint_position_values_[5], stop_control ? 1 : 0, last_ipoc);

    if (ret < 0 || ret == 1024) {
      return std::nullopt;
    }

    has_positions_ = true;
    return xml_string_;
  }

 private:
  char xml_string_[1024];
};
}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_
