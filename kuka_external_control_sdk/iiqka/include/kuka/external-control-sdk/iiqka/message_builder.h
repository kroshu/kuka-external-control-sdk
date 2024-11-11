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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_

#include <limits>
#include <string>

#include "arena_wrapper.h"
#include "kuka/external-control-sdk/common/message_builder.h"
#include "proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "proto-api/motion-services-ecs/motion_state_external.pb.h"
#include "proto-api/motion-services-ecs/signal_config_external.pb.h"

namespace kuka::external::control::iiqka {

enum class SignalDirection { UNSPECIFIED = 0, INPUT = 1, OUTPUT = 2 };
enum class SignalValueType { UNSPECIFIED = 0, BOOL = 1, RAW = 2, NUMBER = 3 };

class Signal_Configuration {
public:
  Signal_Configuration() = default;
  Signal_Configuration(
      const kuka::ecs::v1::SignalConfigExternal &protobuf_signal_config) {
    *this = std::move(protobuf_signal_config);
  }
  ~Signal_Configuration() = default;

  std::size_t const &GetSignalId() const { return signal_id_; }
  bool const &IsSignalUsed() const { return is_signal_used_; }
  void SetSignalToUse(bool signal_used) {
    is_signal_used_ = signal_used;
    is_changed_ = true;
  }
  bool const &IsChanged() const { return is_changed_; }
  void ClearChanged() { is_changed_ = false; }
  std::string const &GetName() const { return name_; }
  SignalDirection const &GetDirection() const { return direction_; }
  SignalValueType const &GetValueType() const { return value_type_; }

  // kuka::ecs::v1::SetSignalForControl SetSignalForControl() {
  //   auto ret_val = kuka::ecs::v1::SetSignalForControl();
  //   ret_val.set_signal_id(signal_id_);
  //   ret_val.set_is_signal_used(is_signal_used_);
  //   return ret_val;
  // }

  Signal_Configuration &
  operator=(kuka::ecs::v1::SignalConfigExternal &&protobuf_signal_config) {
    auto &pb_sc = protobuf_signal_config.signal_config();
    bool has_pb_sc = protobuf_signal_config.has_signal_config();

    this->signal_id_ = protobuf_signal_config.signal_id();
    this->is_signal_used_ = protobuf_signal_config.has_signal_config();
    if (has_pb_sc) {
      this->name_ = pb_sc.name();
      switch (pb_sc.direction()) {
      case kuka::ecs::v1::SignalConfig::INPUT:
        this->direction_ = SignalDirection::INPUT;
        break;
      case kuka::ecs::v1::SignalConfig::OUTPUT:
        this->direction_ = SignalDirection::OUTPUT;
      default:
        this->direction_ = SignalDirection::UNSPECIFIED;
        break;
      }
      switch (pb_sc.data_type()) {
      case kuka::ecs::v1::SignalConfig::BOOL:
        this->value_type_ = SignalValueType::BOOL;
        break;
      case kuka::ecs::v1::SignalConfig::RAW:
        this->value_type_ = SignalValueType::RAW;
        break;
      case kuka::ecs::v1::SignalConfig::NUMBER:
        this->value_type_ = SignalValueType::NUMBER;
        break;
      default:
        this->value_type_ = SignalValueType::UNSPECIFIED;
        break;
      }
    }
    return *this;
  }

private:
  std::size_t signal_id_;
  bool is_signal_used_ = false;
  bool is_changed_ = false;
  std::string name_;
  SignalDirection direction_ = SignalDirection::UNSPECIFIED;
  SignalValueType value_type_ = SignalValueType::UNSPECIFIED;
};

class MotionState : public BaseMotionState {
public:
  // Measured velocities are not provided by the controller, vector should
  // remain empty
  MotionState(std::size_t dof) : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
  }
  MotionState(kuka::ecs::v1::MotionStateExternal &protobuf_motion_state,
              uint8_t dof)
      : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    *this = std::move(protobuf_motion_state);
  }

  MotionState &
  operator=(kuka::ecs::v1::MotionStateExternal &&protobuf_motion_state) {
    auto &pb_ms = protobuf_motion_state.motion_state();
    bool has_pb_ms = protobuf_motion_state.has_motion_state();

    this->has_positions_ = has_pb_ms ? pb_ms.has_measured_positions() : false;
    this->has_torques_ = has_pb_ms ? pb_ms.has_measured_torques() : false;
    if (this->has_positions_) {
      std::move(
          std::begin(pb_ms.measured_positions().values()),
          std::begin(pb_ms.measured_positions().values()) +
              std::min((int)dof_, pb_ms.measured_positions().values_size()),
          measured_positions_.begin());
    }

    if (this->has_torques_) {
      std::move(std::begin(pb_ms.measured_torques().values()),
                std::begin(pb_ms.measured_torques().values()) +
                    std::min((int)dof_, pb_ms.measured_torques().values_size()),
                measured_torques_.begin());
    }

    return *this;
  }
};

class ControlSignal : public BaseControlSignal {
public:
  ControlSignal(ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> *arena,
                std::size_t dof)
      : BaseControlSignal(dof), controlling_arena_(arena) {
    joint_position_values_.resize(dof, 0.0);
    joint_torque_values_.resize(dof, 0.0);
    joint_velocity_values_.resize(dof, 0.0);
    joint_impedance_stiffness_values_.resize(dof, 0.0);
    joint_impedance_damping_values_.resize(dof, 0.0);
  }

  kuka::ecs::v1::ControlSignalExternal *
  CreateProtobufControlSignal(int last_ipoc, int control_mode,
                              bool stop_control = false) {
    controlling_arena_->CreateMessage();
    controlling_arena_->GetMessage()->mutable_header()->set_ipoc(last_ipoc);
    controlling_arena_->GetMessage()->mutable_control_signal()->set_stop_ipo(
        stop_control);
    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->set_control_mode(
            static_cast<kuka::motion::external::ExternalControlMode>(
                control_mode));

    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->mutable_joint_command()
        ->mutable_values()
        ->Clear();

    if (this->has_positions_) {
      for (int i = 0; i < dof_; i++) {
        controlling_arena_->GetMessage()
            ->mutable_control_signal()
            ->mutable_joint_command()
            ->mutable_values()
            ->Add(joint_position_values_[i]);
      }
    }

    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->mutable_joint_torque_command()
        ->mutable_values()
        ->Clear();

    if (this->has_torques_) {
      for (int i = 0; i < dof_; i++) {
        controlling_arena_->GetMessage()
            ->mutable_control_signal()
            ->mutable_joint_torque_command()
            ->mutable_values()
            ->Add(joint_torque_values_[i]);
      }
    }

    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->mutable_joint_velocity_command()
        ->mutable_values()
        ->Clear();

    if (this->has_velocities_) {
      for (int i = 0; i < dof_; i++) {
        controlling_arena_->GetMessage()
            ->mutable_control_signal()
            ->mutable_joint_velocity_command()
            ->mutable_values()
            ->Add(joint_velocity_values_[i]);
      }
    }

    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->mutable_joint_attributes()
        ->mutable_stiffness()
        ->Clear();

    controlling_arena_->GetMessage()
        ->mutable_control_signal()
        ->mutable_joint_attributes()
        ->mutable_damping()
        ->Clear();

    if (this->has_stiffness_and_damping_) {
      for (int i = 0; i < dof_; i++) {
        controlling_arena_->GetMessage()
            ->mutable_control_signal()
            ->mutable_joint_attributes()
            ->mutable_stiffness()
            ->Add(joint_impedance_stiffness_values_[i]);
        controlling_arena_->GetMessage()
            ->mutable_control_signal()
            ->mutable_joint_attributes()
            ->mutable_damping()
            ->Add(joint_impedance_damping_values_[i]);
      }
    }

    return controlling_arena_->GetMessage();
  }

private:
  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> *controlling_arena_;
};

} // namespace kuka::external::control::iiqka

#endif // KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_
