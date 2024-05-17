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

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <map>

#include "kuka/external-control-sdk/iiqka/arena_wrapper.h"
#include "kuka/external-control-sdk/iiqka/message_builder.h"

using ::testing::Test;

// Note that while the control signal / motion state values are expected to be filled by radians,
// the tests may not follow this rule
class TestMotionState : public ::testing::Test {
 protected:
  static constexpr double D_TOLERANCE = 0.01;
};

class TestControlSignal : public ::testing::Test {
 protected:
  static constexpr double D_TOLERANCE = 0.01;
};

TEST_F(TestMotionState, TestEmpty6Dof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);
}

TEST_F(TestMotionState, TestEmpty0Dof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(0);

  EXPECT_EQ(initial_motion_state.GetMeasuredPositions().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredTorques().size(), 0);
}

TEST_F(TestMotionState, TestAssignEmpty6Dof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal empty_ms;

  initial_motion_state = std::move(empty_ms);

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);
}

TEST_F(TestMotionState, TestAddPositionsEqualDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_positions;

  for (int i = 0; i < 6; ++i) {
    ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 +
                                                                                       (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);

  initial_motion_state = std::move(ms_with_positions);

  EXPECT_EQ(initial_motion_state.GetMeasuredPositions(),
            std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);
}

TEST_F(TestMotionState, TestAddPositionsProtobufMSHasSmallerDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_positions;

  for (int i = 0; i < 4; ++i) {
    ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 +
                                                                                       (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);

  initial_motion_state = std::move(ms_with_positions);

  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[0], 12.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[1], 13.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[2], 14.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[3], 15.0, D_TOLERANCE);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[4]), true);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[5]), true);

  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);
}

TEST_F(TestMotionState, TestAddPositionsProtobufMSHasGreaterDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_positions;

  for (int i = 0; i < 15; ++i) {
    ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 +
                                                                                       (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);

  initial_motion_state = std::move(ms_with_positions);

  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[0], 12.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[1], 13.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[2], 14.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[3], 15.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[4], 16.0, D_TOLERANCE);
  EXPECT_NEAR((initial_motion_state.GetMeasuredPositions())[5], 17.0, D_TOLERANCE);
  EXPECT_EQ(initial_motion_state.GetMeasuredPositions().size(), 6);

  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);
}

TEST_F(TestMotionState, TestAddTorquesEqualDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_torques;

  for (int i = 0; i < 6; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 +
                                                                                   (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);

  initial_motion_state = std::move(ms_with_torques);

  EXPECT_EQ(initial_motion_state.GetMeasuredTorques(),
            std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
}

TEST_F(TestMotionState, TestAddTorquesProtobufMSHasSmallerDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_torques;

  for (int i = 0; i < 4; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 +
                                                                                   (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);

  initial_motion_state = std::move(ms_with_torques);

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
}

TEST_F(TestMotionState, TestAddTorquesProtobufMSHasGreaterDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_torques;

  for (int i = 0; i < 15; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 +
                                                                                   (double)i);
  }

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);

  initial_motion_state = std::move(ms_with_torques);

  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
}

// Not possible to fill cartesian positions for iiQKA
TEST_F(TestMotionState, TestAddCartesianPositionsEqualDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);

  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
}

TEST_F(TestMotionState, TestAddEverythingEqualDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_torques;

  for (int i = 0; i < 6; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_positions()->add_values(0 + (double)i);
    ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 +
                                                                                   (double)i);
  }

  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);

  initial_motion_state = std::move(ms_with_torques);

  EXPECT_EQ(initial_motion_state.GetMeasuredPositions(),
            std::vector<double>({0.0, 1.0, 2.0, 3.0, 4.0, 5.0}));

  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
}

TEST_F(TestMotionState, TestAddEverythingNotEqualDof) {
  kuka::external::control::iiqka::MotionState initial_motion_state(6);
  kuka::ecs::v1::MotionStateExternal ms_with_torques;

  for (int i = 0; i < 6; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_positions()->add_values(0 + (double)i);
  }

  for (int i = 0; i < 4; ++i) {
    ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 +
                                                                                   (double)i);
  }

  EXPECT_EQ(initial_motion_state.GetMeasuredVelocities().size(), 0);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredPositions()[0]), true);
  EXPECT_EQ(std::isnan(initial_motion_state.GetMeasuredTorques()[0]), true);

  initial_motion_state = std::move(ms_with_torques);

  EXPECT_EQ(initial_motion_state.GetMeasuredPositions(),
            std::vector<double>({0.0, 1.0, 2.0, 3.0, 4.0, 5.0}));

  EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions().size(), 0);
}

TEST_F(TestControlSignal, TestEmpty6Dof) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);
  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestEmpty0Dof) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 0);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);
  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestAssignEmpty6Dof) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);
  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestAddPositions) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> positions = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, D_TOLERANCE);
  }
}

TEST_F(TestControlSignal, TestAddPositionsArray) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::array<double, 6> positions = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::array<double, 6> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, D_TOLERANCE);
  }
}

TEST_F(TestControlSignal, TestAddPositionsMap) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::map<int, double> positions = {{0, 12.0}, {1, 13.0}, {2, 14.0},
                                     {3, 15.0}, {4, 16.0}, {5, 17.0}};

  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::map<std::string, double> other_positions = {{"0", 2.0}, {"1", 3.0}, {"2", 4.0},
                                                   {"3", 5.0}, {"4", 6.0}, {"5", 7.0}};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, D_TOLERANCE);
  }
}

TEST_F(TestControlSignal, TestAddPositionsUsingSmallerVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> positions = {12.0, 13.0, 14.0};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_positions = {2.0, 3.0, 4.0};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(3), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(4), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(5), 0.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddPositionsUsingSmallerMap) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::map<int, double> positions = {{0, 12.0}, {1, 13.0}, {2, 14.0}};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::map<std::string, double> other_positions = {{"0", 2.0}, {"1", 3.0}, {"2", 4.0}};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(3), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(4), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(5), 0.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddPositionsUsingLargerVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> positions = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(3), 15.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(4), 16.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(5), 17.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddPositionsUsingLargerMap) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::map<int, double> positions = {{0, 12.0}, {1, 13.0}, {2, 14.0}, {3, 15.0}, {4, 16.0},
                                     {5, 17.0}, {6, 18.0}, {7, 19.0}, {8, 20.0}};

  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::map<std::string, double> other_positions = {{"0", 2.0}, {"1", 3.0}, {"2", 4.0}, {"3", 5.0},
                                                   {"4", 6.0}, {"5", 7.0}, {"6", 8.0}, {"7", 9.0}};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(3), 15.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(4), 16.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_command().values(5), 17.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddPositionsUsingEmptyVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> positions;
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_positions;
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestAddTorques) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> torques = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0};
  initial_control_signal.AddTorqueValues(torques.begin(), torques.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_torques = {2.0, 3.0, 4.0, 5.0, 6.0};
  initial_control_signal.AddTorqueValues(other_torques.begin(), other_torques.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_torque_command());
  EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(i), 12 + (double)i,
                D_TOLERANCE);
  }
}

TEST_F(TestControlSignal, TestAddTorquesMap) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::map<int, double> torques = {{0, 12.0}, {1, 13.0}, {2, 14.0},
                                   {3, 15.0}, {4, 16.0}, {5, 17.0}};
  initial_control_signal.AddTorqueValues(torques.begin(), torques.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::map<std::string, double> other_torques = {{"0", 2.0}, {"1", 3.0}, {"2", 4.0},
                                                 {"3", 5.0}, {"4", 6.0}, {"5", 7.0}};
  initial_control_signal.AddTorqueValues(other_torques.begin(), other_torques.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_torque_command());
  EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(i), 12 + (double)i,
                D_TOLERANCE);
  }
}

TEST_F(TestControlSignal, TestAddTorquesUsingSmallerVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> torques = {12.0, 13.0, 14.0};
  initial_control_signal.AddTorqueValues(torques.begin(), torques.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_torques = {2.0, 3.0, 4.0};
  initial_control_signal.AddTorqueValues(other_torques.begin(), other_torques.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_torque_command());
  EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_torque_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(3), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(4), 0.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(5), 0.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddTorquesUsingLargerVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> torques = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
  initial_control_signal.AddTorqueValues(torques.begin(), torques.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_torques = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  initial_control_signal.AddTorqueValues(other_torques.begin(), other_torques.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_torque_command());
  EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  EXPECT_NEAR(result.control_signal().joint_torque_command().values(0), 12.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(1), 13.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(2), 14.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(3), 15.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(4), 16.0, D_TOLERANCE);
  EXPECT_NEAR(result.control_signal().joint_torque_command().values(5), 17.0, D_TOLERANCE);
}

TEST_F(TestControlSignal, TestAddTorquesUsingEmptyVector) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> torques;
  initial_control_signal.AddTorqueValues(torques.begin(), torques.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_torques;
  initial_control_signal.AddTorqueValues(other_torques.begin(), other_torques.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestAddIpoc) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(30, 0);

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 30);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestAddControlMode) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 1);
  EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_POSITION_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 2);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::JOINT_IMPEDANCE_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 3);
  EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_VELOCITY_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 4);
  EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_TORQUE_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 5);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::CARTESIAN_POSITION_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 6);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::CARTESIAN_IMPEDANCE_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 7);
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::CARTESIAN_VELOCITY_CONTROL);

  result = *initial_control_signal.CreateProtobufControlSignal(0, 8);
  EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::WRENCH_CONTROL);
}

TEST_F(TestControlSignal, TestStop) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0, true);

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_TRUE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());
}

TEST_F(TestControlSignal, TestOverridePreviousPositions) {
  kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
  kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

  std::vector<double> positions = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0};
  initial_control_signal.AddJointPositionValues(positions.begin(), positions.end());

  kuka::ecs::v1::ControlSignalExternal result =
      *initial_control_signal.CreateProtobufControlSignal(0, 0);

  std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0};
  initial_control_signal.AddJointPositionValues(other_positions.begin(), other_positions.end());

  EXPECT_TRUE(result.has_header());
  EXPECT_EQ(result.header().ipoc(), 0);
  EXPECT_TRUE(result.has_control_signal());
  EXPECT_FALSE(result.control_signal().stop_ipo());
  EXPECT_EQ(result.control_signal().control_mode(),
            kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
  EXPECT_TRUE(result.control_signal().has_joint_command());
  EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
  EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
  EXPECT_FALSE(result.control_signal().has_cartesian_command());
  EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
  EXPECT_FALSE(result.control_signal().has_wrench_command());

  for (int i = 0; i < 6; ++i) {
    EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, D_TOLERANCE);
  }
}
