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

#include "arena_wrapper.h"
#include "kuka/external-control-sdk/common/message_builder.h"
#include "proto-api/motion-services-ecs/control_signal_external.pb.h"
#include "proto-api/motion-services-ecs/motion_state_external.pb.h"

namespace kuka::external::control::iiqka {

class MotionState : public BaseMotionState {
 public:
  // Measured velocities are not provided by the controller, vector should remain empty
  MotionState(std::size_t dof) : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_twist_.resize(twist_dof_, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(cart_pos_dof_, std::numeric_limits<double>::quiet_NaN());
  }
  MotionState(kuka::ecs::v1::MotionStateExternal& protobuf_motion_state, uint8_t dof)
      : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_twist_.resize(twist_dof_, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(cart_pos_dof_, std::numeric_limits<double>::quiet_NaN());

    *this = std::move(protobuf_motion_state);
  }

  MotionState& operator=(kuka::ecs::v1::MotionStateExternal&& protobuf_motion_state) {
    auto& pb_ms = protobuf_motion_state.motion_state();
    bool has_pb_ms = protobuf_motion_state.has_motion_state();

    this->has_positions_ = has_pb_ms ? pb_ms.has_measured_positions() : false;
    this->has_torques_ = has_pb_ms ? pb_ms.has_measured_torques() : false;
    this->has_twist_ = has_pb_ms ? pb_ms.has_measured_twist() : false;
    this->has_cartesian_positions_ = has_pb_ms ? pb_ms.has_measured_cartesian_position() : false;
    if (this->has_positions_) {
      std::move(std::begin(pb_ms.measured_positions().values()),
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
    
    if (this->has_twist_) {
      measured_twist_[0] = protobuf_motion_state.motion_state().measured_twist().linear().x();
      measured_twist_[1] = protobuf_motion_state.motion_state().measured_twist().linear().y();
      measured_twist_[2] = protobuf_motion_state.motion_state().measured_twist().linear().z();
      measured_twist_[3] = protobuf_motion_state.motion_state().measured_twist().angular().x();
      measured_twist_[4] = protobuf_motion_state.motion_state().measured_twist().angular().y();
      measured_twist_[5] = protobuf_motion_state.motion_state().measured_twist().angular().z();
    }
    if (this->has_cartesian_positions_) {
      measured_cartesian_positions_[0] =
          protobuf_motion_state.motion_state().measured_cartesian_position().translation().x();
      measured_cartesian_positions_[1] =
          protobuf_motion_state.motion_state().measured_cartesian_position().translation().y();
      measured_cartesian_positions_[2] =
          protobuf_motion_state.motion_state().measured_cartesian_position().translation().z();
      measured_cartesian_positions_[3] =
          protobuf_motion_state.motion_state().measured_cartesian_position().rotation().x();
      measured_cartesian_positions_[4] =
          protobuf_motion_state.motion_state().measured_cartesian_position().rotation().y();
      measured_cartesian_positions_[5] =
          protobuf_motion_state.motion_state().measured_cartesian_position().rotation().z();
      measured_cartesian_positions_[6] =
          protobuf_motion_state.motion_state().measured_cartesian_position().rotation().w();
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
    cartesian_position_values_.resize(cart_pos_dof_, 0.0);
    twist_values_.resize(twist_dof_, 0.0);
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

    controlling_arena_->GetMessage()->mutable_control_signal()->mutable_twist_command()->Clear();

    if (this->has_twist_) {
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_linear()
          ->set_x(twist_values_.at(0));
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_linear()
          ->set_y(twist_values_.at(1));
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_linear()
          ->set_z(twist_values_.at(2));
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_angular()
          ->set_x(twist_values_.at(3));
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_angular()
          ->set_y(twist_values_.at(4));
      controlling_arena_->GetMessage()
          ->mutable_control_signal()
          ->mutable_twist_command()
          ->mutable_angular()
          ->set_z(twist_values_.at(5));
    }

    return controlling_arena_->GetMessage();
  }

 private:
  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal>* controlling_arena_;
};

}  // namespace kuka::external::control::iiqka

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_
