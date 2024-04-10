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

#include <optional>
#include <vector>

namespace kuka::external::control {

class BaseMotionState {
 public:
  BaseMotionState(std::size_t dof) : dof_(dof) {}

  std::vector<double> const* GetMeasuredPositions() {
    return has_positions_ ? &measured_positions_ : nullptr;
  }
  std::vector<double> const* GetMeasuredTorques() {
    return has_torques_ ? &measured_torques_ : nullptr;
  }
  std::vector<double> const* GetMeasuredVelocities() {
    return has_velocities_ ? &measured_velocities_ : nullptr;
  }
  std::vector<double> const* GetMeasuredCartesianPositions() {
    return has_cartesian_positions_ ? &measured_cartesian_positions_ : nullptr;
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

  std::size_t dof_;
};

class BaseControlSignal {
 public:
  BaseControlSignal(std::size_t dof) : dof_(dof) {}

  void AddJointPositionValues(std::vector<double>& joint_position_values) {
    if (joint_position_values.size() > 0) {
      has_positions_ = true;
      std::vector<double>::iterator end_it =
          joint_position_values.begin() + std::min(joint_position_values.size(), dof_);
      joint_position_values_.assign(joint_position_values.begin(), end_it);
    }
  };

  void AddTorqueValues(std::vector<double>& joint_torque_values) {
    if (joint_torque_values.size() > 0) {
      has_torques_ = true;
      std::vector<double>::iterator end_it =
          joint_torque_values.begin() + std::min(joint_torque_values.size(), dof_);
      joint_torque_values_.assign(joint_torque_values.begin(), end_it);
    }
  };

  void AddVelocityValues(std::vector<double>& joint_velocity_values) {
    if (joint_velocity_values.size() > 0) {
      has_velocities_ = true;
      std::vector<double>::iterator end_it =
          joint_velocity_values.begin() + std::min(joint_velocity_values.size(), dof_);
      joint_velocity_values_.assign(joint_velocity_values.begin(), end_it);
    }
  }

  void AddStiffnessAndDampingValues(std::vector<double>& stiffness_values,
                                    std::vector<double>& damping_values) {
    if (stiffness_values.size() > 0) {
      has_stiffness_and_damping_ = true;
      std::vector<double>::iterator s_end_it =
          stiffness_values.begin() + std::min(stiffness_values.size(), dof_);
      joint_impedance_stiffness_values_.assign(stiffness_values.begin(), s_end_it);
    }

    if (damping_values.size() > 0) {
      has_stiffness_and_damping_ = true;
      std::vector<double>::iterator d_end_it =
          damping_values.begin() + std::min(damping_values.size(), dof_);
      joint_impedance_damping_values_.assign(damping_values.begin(), d_end_it);
    }
  };

  void AddCartesianPositionValues(std::vector<double>& cartesian_position_values) {
    if (cartesian_position_values.size() > 0) {
      has_cartesian_positions_ = true;
      std::vector<double>::iterator end_it =
          cartesian_position_values_.begin() + std::min(cartesian_position_values_.size(), dof_);
      cartesian_position_values_.assign(cartesian_position_values_.begin(), end_it);
    }
  };

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

  std::size_t dof_ = 0;
};
}  // namespace kuka::external::control

#endif  // KUKA_EXTERNAL_CONTROL__MESSAGE_BUILDER_H_
