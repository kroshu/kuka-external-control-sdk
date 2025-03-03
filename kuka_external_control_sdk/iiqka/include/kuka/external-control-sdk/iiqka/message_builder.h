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
#include "signal_value.h"

namespace kuka::external::control::iiqka {

class MotionState : public BaseMotionState {
public:
  // Measured velocities are not provided by the controller, vector should
  // remain empty
  MotionState(std::size_t dof, std::size_t gpio_size) : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    // measured_signal_values_.resize(kMotionState_SignalValueMaxCount,
    //                                std::make_shared<SignalValue>());
    for (size_t i = 0; i < gpio_size; i++) {
      measured_signal_values_.push_back(std::make_shared<SignalValue>());
    }
  }
  MotionState(kuka::ecs::v1::MotionStateExternal &protobuf_motion_state,
              uint8_t dof, std::size_t gpio_size)
      : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    for (size_t i = 0; i < gpio_size; i++) {
      measured_signal_values_.push_back(std::make_shared<SignalValue>());
    }
    *this = std::move(protobuf_motion_state);
  }

  MotionState &
  operator=(kuka::ecs::v1::MotionStateExternal &&protobuf_motion_state) {
    auto &pb_ms = protobuf_motion_state.motion_state();
    auto &pb_sv = protobuf_motion_state.signal_values();
    bool has_pb_ms = protobuf_motion_state.has_motion_state();

    this->has_positions_ = has_pb_ms ? pb_ms.has_measured_positions() : false;
    this->has_torques_ = has_pb_ms ? pb_ms.has_measured_torques() : false;
    this->signal_values_size_ = protobuf_motion_state.signal_values_size();
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
    if (this->signal_values_size_ > 0) {
      // std::copy(protobuf_motion_state.mutable_signal_values()->begin(),
      //           protobuf_motion_state.mutable_signal_values()->end(),
      //           measured_signal_values_.begin())

      // for (size_t i = 0, j = 0; i <
      // protobuf_motion_state.signal_values_size();
      //      i++, j++) {
      //   *std::static_pointer_cast<SignalValue>(measured_signal_values_.at(i))
      //   =
      //       std::move(*protobuf_motion_state.mutable_signal_values(j));
      // }
      // measured_signal_values_.clear();
      // for (size_t i = 0;
      //      i < std::min(signal_values_size_,
      //                   static_cast<int>(kMotionState_SignalValueMaxCount));
      //      i++) {
      //   measured_signal_values_.push_back(std::make_shared<SignalValue>(
      //       *protobuf_motion_state.mutable_signal_values(i)));
      // }

      for (size_t i = 0;
           i < std::min(signal_values_size_, measured_signal_values_.size());
           i++) {
        *std::static_pointer_cast<SignalValue>(measured_signal_values_[i]) =
            std::move(*protobuf_motion_state.mutable_signal_values(i));
      }

      // *std::static_pointer_cast<SignalValue>(measured_signal_values_.at(0)) =
      //     std::move(*protobuf_motion_state.mutable_signal_values(0));
      // *std::static_pointer_cast<SignalValue>(measured_signal_values_.at(1))
      // =
      //     std::move(*protobuf_motion_state.mutable_signal_values(1));

      // std::move(protobuf_motion_state.mutable_signal_values()->begin(),
      //           protobuf_motion_state.mutable_signal_values()->begin() +
      //               std::min((int)kMotionState_SignalValueMaxCount,
      //                        protobuf_motion_state.signal_values_size()),
      //           measured_signal_values_.begin());
    }

    return *this;
  }
};

class ControlSignal : public BaseControlSignal {
public:
  ControlSignal(ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> *arena,
                std::size_t dof, std::size_t gpio_size)
      : BaseControlSignal(dof), controlling_arena_(arena) {
    joint_position_values_.resize(dof, 0.0);
    joint_torque_values_.resize(dof, 0.0);
    joint_velocity_values_.resize(dof, 0.0);
    joint_impedance_stiffness_values_.resize(dof, 0.0);
    joint_impedance_damping_values_.resize(dof, 0.0);
    for (size_t i = 0; i < gpio_size; i++) {
      signal_values_.push_back(std::make_shared<SignalValue>());
    }
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

    controlling_arena_->GetMessage()->mutable_signal_values()->Clear();

    for (size_t i = 0; i < std::min(signal_values_.size(), signal_values_size_);
         i++) {
      auto pb_sv =
          controlling_arena_->GetMessage()->mutable_signal_values()->Add();
      pb_sv->set_signal_id(signal_values_.at(i)->GetSignalID());
      switch (signal_values_.at(i)->GetValueType()) {
      case SignalValue::SignalValueType::BOOL_VALUE:
        pb_sv->set_bool_value(signal_values_.at(i)->GetBoolValue());
        break;
      case SignalValue::SignalValueType::DOUBLE_VALUE:
        pb_sv->set_double_value(signal_values_.at(i)->GetDoubleValue());
        break;
      case SignalValue::SignalValueType::RAW_VALUE:
        pb_sv->set_raw_value(signal_values_.at(i)->GetRawValue());
        break;
      default:
        break;
      }
    }

    return controlling_arena_->GetMessage();
  }

private:
  ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> *controlling_arena_;
};

} // namespace kuka::external::control::iiqka

#endif // KUKA_EXTERNAL_CONTROL__IIQKA_MESSAGE_BUILDER_H_
