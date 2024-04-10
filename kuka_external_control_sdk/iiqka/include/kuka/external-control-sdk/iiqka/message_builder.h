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

#include "arena_wrapper.h"
#include "iiqka/proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "iiqka/proto-api/motion-services-ecs/motion_state_external.pb.h"
#include "kuka/external-control-sdk/common/message_builder.h"

namespace kuka::external::control::iiqka {

class MotionState : public BaseMotionState {
 public:
  MotionState(std::size_t dof) : BaseMotionState(dof) {
    measured_positions_.resize(dof, 0.0);
    measured_torques_.resize(dof, 0.0);
    measured_velocities_.resize(dof, 0.0);
  }
  MotionState(kuka::ecs::v1::MotionStateExternal& protobuf_motion_state, uint8_t dof)
      : BaseMotionState(dof) {
    measured_positions_.resize(dof, 0.0);
    measured_torques_.resize(dof, 0.0);
    measured_velocities_.resize(dof, 0.0);
    *this = std::move(protobuf_motion_state);
  }

  MotionState& operator=(kuka::ecs::v1::MotionStateExternal&& protobuf_motion_state) {
    this->has_positions_ = protobuf_motion_state.has_motion_state()
                               ? protobuf_motion_state.motion_state().has_measured_positions()
                               : false;
    this->has_torques_ = protobuf_motion_state.has_motion_state()
                             ? protobuf_motion_state.motion_state().has_measured_torques()
                             : false;
    this->has_velocities_ = protobuf_motion_state.has_motion_state()
                                ? protobuf_motion_state.motion_state().has_measured_velocities()
                                : false;
    if (this->has_positions_) {
      std::move(
          std::begin(protobuf_motion_state.motion_state().measured_positions().values()),
          std::begin(protobuf_motion_state.motion_state().measured_positions().values()) + dof_,
          measured_positions_.begin());
    }

    if (this->has_torques_) {
      std::move(std::begin(protobuf_motion_state.motion_state().measured_torques().values()),
                std::begin(protobuf_motion_state.motion_state().measured_torques().values()) + dof_,
                measured_torques_.begin());
    }

    if (this->has_velocities_) {
      std::move(
          std::begin(protobuf_motion_state.motion_state().measured_velocities().values()),
          std::begin(protobuf_motion_state.motion_state().measured_velocities().values()) + dof_,
          measured_velocities_.begin());
    }

    return *this;
  }
};

class ControlSignal : public BaseControlSignal {
 public:
  ControlSignal(ArenaWrapper<kuka::ecs::v1::ControlSignalExternal>* arena, std::size_t dof)
      : BaseControlSignal(dof), controlling_arena_(arena) {
    joint_position_values_.resize(dof, 0.0);
    joint_torque_values_.resize(dof, 0.0);
    joint_velocity_values_.resize(dof, 0.0);
    joint_impedance_stiffness_values_.resize(dof, 0.0);
    joint_impedance_damping_values_.resize(dof, 0.0);
  }

  kuka::ecs::v1::ControlSignalExternal* CreateProtobufControlSignal(int last_ipoc, int control_mode,
                                                                    bool stop_control = false) {
    controlling_arena_->CreateMessage();
    controlling_arena_->GetMessage()->mutable_header()->set_ipoc(last_ipoc);
    controlling_arena_->GetMessage()->mutable_control_signal()->set_stop_ipo(stop_control);
    controlling_arena_->GetMessage()->mutable_control_signal()->set_control_mode(
        static_cast<kuka::motion::external::ExternalControlMode>(control_mode));

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
  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal>* controlling_arena_;
};

}  // namespace kuka::external::control::iiqka

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_
