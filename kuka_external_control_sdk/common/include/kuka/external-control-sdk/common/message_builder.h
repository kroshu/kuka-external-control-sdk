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

#ifndef KUKA_EXTERNAL_CONTROL__MESSAGE_BUILDER_H_
#define KUKA_EXTERNAL_CONTROL__MESSAGE_BUILDER_H_

#include "gpio_value.h"

#include <iterator>
#include <map>
#include <optional>
#include <vector>

namespace kuka::external::control {

class BaseMotionState {
public:
  BaseMotionState(std::size_t dof) : dof_(dof) {}

  std::vector<double> const &GetMeasuredPositions() const {
    return measured_positions_;
  }

  std::vector<double> const &GetMeasuredTorques() const {
    return measured_torques_;
  }

  std::vector<double> const &GetMeasuredVelocities() const {
    return measured_velocities_;
  }

  std::vector<double> const &GetMeasuredCartesianPositions() const {
    return measured_cartesian_positions_;
  }

  std::vector<std::shared_ptr<BaseGPIOValue>> const &GetGPIOValues() const {
    return measured_gpio_values_;
  }

protected:
  bool has_positions_ = false;
  bool has_torques_ = false;
  bool has_velocities_ = false;
  bool has_cartesian_positions_ = false;

  std::vector<double> measured_positions_;
  std::vector<double> measured_torques_;
  std::vector<double> measured_velocities_;
  std::vector<double> measured_cartesian_positions_;
  std::vector<std::shared_ptr<BaseGPIOValue>> measured_gpio_values_;

  std::size_t dof_;
};

class BaseControlSignal {
public:
  BaseControlSignal(std::size_t dof) : dof_(dof) {}

  template <typename InputIt>
  void AddJointPositionValues(InputIt first, InputIt last) {
    if (first != last) {
      has_positions_ = true;
      AddValues(joint_position_values_, first, last);
    }
  }

  template <typename InputIt>
  void AddTorqueValues(InputIt first, InputIt last) {
    if (first != last) {
      has_torques_ = true;
      AddValues(joint_torque_values_, first, last);
    }
  }

  template <typename InputIt>
  void AddVelocityValues(InputIt first, InputIt last) {
    if (first != last) {
      has_velocities_ = true;
      AddValues(joint_velocity_values_, first, last);
    }
  }

  template <typename InputIt>
  void
  AddStiffnessAndDampingValues(InputIt first_stiffness, InputIt last_stiffness,
                               InputIt first_damping, InputIt last_damping) {
    if (first_damping != last_damping) {
      has_stiffness_and_damping_ = true;
      AddValues(joint_impedance_stiffness_values_, first_stiffness,
                last_stiffness);
    }
    if (first_stiffness != last_stiffness) {
      has_stiffness_and_damping_ = true;
      AddValues(joint_impedance_damping_values_, first_damping, last_damping);
    }
  }

  template <typename InputIt>
  void AddCartesianPositionValues(InputIt first, InputIt last) {
    if (first != last) {
      has_cartesian_positions_ = true;
      AddValues(cartesian_position_values_, first, last);
    }
  }

  template <typename InputIt> void AddGPIOValues(InputIt first, InputIt last) {
    for (size_t i = 0; i < gpio_values_.size() && first != last; i++, ++first) {
      auto &gpio = gpio_values_.at(i);
      switch (gpio->GetGPIOConfig()->GetValueType()) {
      case GPIOValueType::BOOL_VALUE:
        gpio->SetBoolValue(*first);
        break;

      case GPIOValueType::DOUBLE_VALUE:
        gpio->SetDoubleValue(*first);
        break;

      case GPIOValueType::RAW_VALUE:
        gpio->SetRawValue(*first);
        break;

      case GPIOValueType::LONG_VALUE:
        gpio->SetLongValue(*first);
        break;

      default:
        break;
      }
    }
  }

  std::vector<std::shared_ptr<BaseGPIOValue>> const &GetGPIOValues() const {
    return gpio_values_;
  }

protected:
  bool has_positions_ = false;
  bool has_torques_ = false;
  bool has_velocities_ = false;
  bool has_stiffness_and_damping_ = false;
  bool has_cartesian_positions_ = false;

  std::vector<double> joint_position_values_;
  std::vector<double> joint_torque_values_;
  std::vector<double> joint_velocity_values_;
  std::vector<double> joint_impedance_stiffness_values_;
  std::vector<double> joint_impedance_damping_values_;
  std::vector<double> cartesian_position_values_;
  std::vector<std::shared_ptr<BaseGPIOValue>> gpio_values_;

  std::size_t dof_ = 0;

private:
  template <typename InputIt>
  void AddValues(std::vector<double> &output, InputIt first, InputIt last) {
    for (size_t i = 0; i < dof_ && first != last; ++i, ++first) {
      AddToVector(output[i], *first);
    }
  }

  void AddToVector(double &vector_pos, double value) { vector_pos = value; }

  template <typename KeyType>
  void AddToVector(double &vector_pos,
                   const std::pair<const KeyType, double> &pair) {
    vector_pos = pair.second;
  }
};
} // namespace kuka::external::control

#endif // KUKA_EXTERNAL_CONTROL__MESSAGE_BUILDER_H_
