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

#include <iterator>
#include <map>
#include <optional>
#include <vector>

#include "proto-api/motion-services-ecs/signal_value_external.pb.h"

namespace kuka::external::control {

static constexpr size_t kMotionState_SignalValueMaxCount{100};
static constexpr size_t kControlSignal_SignalValueMaxCount{10};

class SignalValue {
public:
  enum class SignalValueType {
    UNSPECIFIED = 0,
    BOOL_VALUE = 1,
    DOUBLE_VALUE = 2,
    RAW_VALUE = 3
  };
  SignalValue() = default;
  SignalValue(kuka::ecs::v1::SignalValueExternal protobuf_signal_value) {
    *this = std::move(protobuf_signal_value);
  }
  SignalValue &
  operator=(kuka::ecs::v1::SignalValueExternal &protobuf_signal_value) {
    this->signal_id_ = protobuf_signal_value.signal_id();

    switch (protobuf_signal_value.signal_type_case()) {
    case kuka::ecs::v1::SignalValueExternal::kBoolValue:
      this->value_type_ = SignalValueType::BOOL_VALUE;
      this->value_.bool_value_ = protobuf_signal_value.bool_value();
      break;
    case kuka::ecs::v1::SignalValueExternal::kDoubleValue:
      this->value_type_ = SignalValueType::DOUBLE_VALUE;
      this->value_.double_value_ = protobuf_signal_value.double_value();
      break;
    case kuka::ecs::v1::SignalValueExternal::kRawValue:
      this->value_type_ = SignalValueType::RAW_VALUE;
      this->value_.raw_value_ = protobuf_signal_value.raw_value();
      break;
    default:
      this->value_type_ = SignalValueType::UNSPECIFIED;
      break;
    }
    return *this;
  }
  uint32_t const &GetSignalID() const { return signal_id_; }
  SignalValueType const &GetValueType() const { return value_type_; }
  bool const &GetBoolValue() const { return value_.bool_value_; }
  void SetBoolValue(bool &value) { value_.bool_value_ = value; }
  double const &GetDoubleValue() const { return value_.double_value_; }
  void SetDoubleValue(double &value) { value_.double_value_ = value; }
  uint64_t const &GetRawValue() const { return value_.raw_value_; }
  void SetRawValue(uint64_t &value) { value_.raw_value_ = value; }

private:
  uint32_t signal_id_;
  SignalValueType value_type_ = SignalValueType::UNSPECIFIED;
  union {
    bool bool_value_;
    double double_value_;
    uint64_t raw_value_;
  } value_;
};

class BaseMotionState {
public:
  BaseMotionState(std::size_t dof) : dof_(dof) {}

  std::vector<double> const &GetMeasuredPositions() {
    return measured_positions_;
  }

  std::vector<double> const &GetMeasuredTorques() { return measured_torques_; }

  std::vector<double> const &GetMeasuredVelocities() {
    return measured_velocities_;
  }

  std::vector<double> const &GetMeasuredCartesianPositions() {
    return measured_cartesian_positions_;
  }

  std::vector<SignalValue> const &GetSignalValues() {
    return measured_signal_values_;
  }

protected:
  bool has_positions_ = false;
  bool has_torques_ = false;
  bool has_velocities_ = false;
  bool has_cartesian_positions_ = false;
  bool has_signal_values_ = false;

  std::vector<double> measured_positions_;
  std::vector<double> measured_torques_;
  std::vector<double> measured_velocities_;
  std::vector<double> measured_cartesian_positions_;
  std::vector<SignalValue> measured_signal_values_;

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

  template <typename InputIt>
  void AddSignalValues(InputIt first, InputIt last) {
    has_signal_values_ = true;
    for (size_t i = 0; i < kControlSignal_SignalValueMaxCount && first != last;
         ++i, ++first) {
      signal_values_[i] = *first;
    }
  }

protected:
  bool has_positions_ = false;
  bool has_torques_ = false;
  bool has_velocities_ = false;
  bool has_stiffness_and_damping_ = false;
  bool has_cartesian_positions_ = false;
  bool has_signal_values_ = false;

  std::vector<double> joint_position_values_;
  std::vector<double> joint_torque_values_;
  std::vector<double> joint_velocity_values_;
  std::vector<double> joint_impedance_stiffness_values_;
  std::vector<double> joint_impedance_damping_values_;
  std::vector<double> cartesian_position_values_;
  std::vector<SignalValue> signal_values_;

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
