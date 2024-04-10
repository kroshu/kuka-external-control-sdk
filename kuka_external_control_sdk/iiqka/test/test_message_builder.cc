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

#include "kuka/external-control-sdk/iiqka/message_builder.h"
#include "kuka/external-control-sdk/iiqka/arena_wrapper.h"


using ::testing::Test;

// Note that while the control signal / motion state values are expected to be filled by radians, the tests may not follow this rule
class TestMotionState : public ::testing::Test {
};

class TestControlSignal : public ::testing::Test {
};

TEST_F(TestMotionState, TestEmpty6Dof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestEmpty0Dof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(0);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAssignEmpty6Dof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal empty_ms;

    initial_motion_state = std::move(empty_ms);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddPositionsEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_positions;

    for (int i = 0; i < 6; ++i) {
        ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 + (double)i);
    }

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);


    initial_motion_state = std::move(ms_with_positions);

    EXPECT_EQ(*(initial_motion_state.GetMeasuredPositions()), std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddPositionsProtobufMSHasSmallerDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_positions;

    for (int i = 0; i < 4; ++i) {
        ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);


    initial_motion_state = std::move(ms_with_positions);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[4], 0.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[5], 0.0, 0.02);

    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddPositionsProtobufMSHasGreaterDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_positions;

    for (int i = 0; i < 15; ++i) {
        ms_with_positions.mutable_motion_state()->mutable_measured_positions()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);

    initial_motion_state = std::move(ms_with_positions);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[4], 16.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredPositions()))[5], 17.0, 0.02);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()->size(), 6);

    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddVelocitiesEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_velocities;

    for (int i = 0; i < 6; ++i) {
        ms_with_velocities.mutable_motion_state()->mutable_measured_velocities()->add_values(12.0 + (double)i);
    }

    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);


    initial_motion_state = std::move(ms_with_velocities);

    EXPECT_EQ(*(initial_motion_state.GetMeasuredVelocities()), std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddVelocitiesProtobufMSHasSmallerDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_velocities;

    for (int i = 0; i < 4; ++i) {
        ms_with_velocities.mutable_motion_state()->mutable_measured_velocities()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);

    initial_motion_state = std::move(ms_with_velocities);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[4], 0.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[5], 0.0, 0.02);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities()->size(), 6);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddVelocitiesProtobufMSHasGreaterDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_velocities;

    for (int i = 0; i < 15; ++i) {
        ms_with_velocities.mutable_motion_state()->mutable_measured_velocities()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);

    initial_motion_state = std::move(ms_with_velocities);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[4], 16.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredVelocities()))[5], 17.0, 0.02);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities()->size(), 6);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);
}

TEST_F(TestMotionState, TestAddTorquesEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_torques;

    for (int i = 0; i < 6; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 + (double)i);
    }

    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);


    initial_motion_state = std::move(ms_with_torques);

    EXPECT_EQ(*(initial_motion_state.GetMeasuredTorques()), std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
}

TEST_F(TestMotionState, TestAddTorquesProtobufMSHasSmallerDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_torques;

    for (int i = 0; i < 4; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);

    initial_motion_state = std::move(ms_with_torques);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[4], 0.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[5], 0.0, 0.02);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques()->size(), 6);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
}

TEST_F(TestMotionState, TestAddTorquesProtobufMSHasGreaterDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_torques;

    for (int i = 0; i < 15; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 + (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);

    initial_motion_state = std::move(ms_with_torques);
    
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[0], 12.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[1], 13.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[2], 14.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[3], 15.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[4], 16.0, 0.02);
    EXPECT_NEAR((*(initial_motion_state.GetMeasuredTorques()))[5], 17.0, 0.02);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques()->size(), 6);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
}


// Not possible to fill cartesian positions for iiQKA
TEST_F(TestMotionState, TestAddCartesianPositionsEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);

    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
}

TEST_F(TestMotionState, TestAddEverythingEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_torques;

    for (int i = 0; i < 6; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_positions()->add_values(0 + (double)i);
        ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 + (double)i);
        ms_with_torques.mutable_motion_state()->mutable_measured_velocities()->add_values(12.0 - (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);

    initial_motion_state = std::move(ms_with_torques);

    EXPECT_EQ(*(initial_motion_state.GetMeasuredPositions()), std::vector<double>({0.0, 1.0, 2.0, 3.0, 4.0, 5.0}));
    EXPECT_EQ(*(initial_motion_state.GetMeasuredTorques()), std::vector<double>({12.0, 13.0, 14.0, 15.0, 16.0, 17.0}));
    EXPECT_EQ(*(initial_motion_state.GetMeasuredVelocities()), std::vector<double>({12.0, 11.0, 10.0, 9.0, 8.0, 7.0}));

    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
}

TEST_F(TestMotionState, TestAddEverythingNotEqualDof) {
    kuka::external::control::iiqka::MotionState initial_motion_state(6);
    kuka::ecs::v1::MotionStateExternal ms_with_torques;

    for (int i = 0; i < 6; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_positions()->add_values(0 + (double)i);
    }

    for (int i = 0; i < 4; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_torques()->add_values(12.0 + (double)i);
    }

    for (int i = 0; i < 15; ++i) {
        ms_with_torques.mutable_motion_state()->mutable_measured_velocities()->add_values(12.0 - (double)i);
    }
    
    EXPECT_EQ(initial_motion_state.GetMeasuredVelocities(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions(), nullptr);
    EXPECT_EQ(initial_motion_state.GetMeasuredTorques(), nullptr);

    initial_motion_state = std::move(ms_with_torques);

    EXPECT_EQ(*(initial_motion_state.GetMeasuredPositions()), std::vector<double>({0.0, 1.0, 2.0, 3.0, 4.0, 5.0}));
    EXPECT_EQ(*(initial_motion_state.GetMeasuredTorques()), std::vector<double>({12.0, 13.0, 14.0, 15.0, 0.0, 0.0}));
    EXPECT_EQ(*(initial_motion_state.GetMeasuredVelocities()), std::vector<double>({12.0, 11.0, 10.0, 9.0, 8.0, 7.0}));

    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions(), nullptr);
}


TEST_F(TestControlSignal, TestEmpty6Dof) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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

    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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

    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
    initial_control_signal.AddJointPositionValues(positions);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0};
    initial_control_signal.AddJointPositionValues(other_positions);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
        EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, 0.02);
    }
}

TEST_F(TestControlSignal, TestAddPositionsUsingSmallerVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> positions = {12.0, 13.0, 14.0};
    initial_control_signal.AddJointPositionValues(positions);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_positions = {2.0, 3.0, 4.0};
    initial_control_signal.AddJointPositionValues(other_positions);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
    EXPECT_TRUE(result.control_signal().has_joint_command());
    EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
    EXPECT_FALSE(result.control_signal().has_cartesian_command());
    EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
    EXPECT_FALSE(result.control_signal().has_wrench_command());

    EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(3), 0.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(4), 0.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(5), 0.0, 0.02);
}

TEST_F(TestControlSignal, TestAddPositionsUsingLargerVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> positions = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
    initial_control_signal.AddJointPositionValues(positions);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    initial_control_signal.AddJointPositionValues(other_positions);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
    EXPECT_TRUE(result.control_signal().has_joint_command());
    EXPECT_NE(result.control_signal().joint_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_torque_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
    EXPECT_FALSE(result.control_signal().has_cartesian_command());
    EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
    EXPECT_FALSE(result.control_signal().has_wrench_command());

    EXPECT_NEAR(result.control_signal().joint_command().values(0), 12.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(1), 13.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(2), 14.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(3), 15.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(4), 16.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_command().values(5), 17.0, 0.02);
}

TEST_F(TestControlSignal, TestAddPositionsUsingEmptyVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> positions;
    initial_control_signal.AddJointPositionValues(positions);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_positions;
    initial_control_signal.AddJointPositionValues(other_positions);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
    initial_control_signal.AddTorqueValues(torques);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_torques = {2.0, 3.0, 4.0, 5.0, 6.0};
    initial_control_signal.AddTorqueValues(other_torques);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
        EXPECT_NEAR(result.control_signal().joint_torque_command().values(i), 12 + (double)i, 0.02);
    }
}

TEST_F(TestControlSignal, TestAddTorquesUsingSmallerVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> torques = {12.0, 13.0, 14.0};
    initial_control_signal.AddTorqueValues(torques);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_torques = {2.0, 3.0, 4.0};
    initial_control_signal.AddTorqueValues(other_torques);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
    EXPECT_TRUE(result.control_signal().has_joint_torque_command());
    EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
    EXPECT_FALSE(result.control_signal().has_cartesian_command());
    EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
    EXPECT_FALSE(result.control_signal().has_wrench_command());

    EXPECT_NEAR(result.control_signal().joint_torque_command().values(0), 12.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(1), 13.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(2), 14.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(3), 0.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(4), 0.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(5), 0.0, 0.02);
}

TEST_F(TestControlSignal, TestAddTorquesUsingLargerVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> torques = {12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
    initial_control_signal.AddTorqueValues(torques);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_torques = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    initial_control_signal.AddTorqueValues(other_torques);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
    EXPECT_TRUE(result.control_signal().has_joint_torque_command());
    EXPECT_NE(result.control_signal().joint_torque_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_velocity_command().values_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().stiffness_size(), 0);
    EXPECT_EQ(result.control_signal().joint_attributes().damping_size(), 0);
    EXPECT_FALSE(result.control_signal().has_cartesian_command());
    EXPECT_FALSE(result.control_signal().has_cartesian_attributes());
    EXPECT_FALSE(result.control_signal().has_wrench_command());

    EXPECT_NEAR(result.control_signal().joint_torque_command().values(0), 12.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(1), 13.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(2), 14.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(3), 15.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(4), 16.0, 0.02);
    EXPECT_NEAR(result.control_signal().joint_torque_command().values(5), 17.0, 0.02);
}

TEST_F(TestControlSignal, TestAddTorquesUsingEmptyVector) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);

    std::vector<double> torques;
    initial_control_signal.AddTorqueValues(torques);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_torques;
    initial_control_signal.AddTorqueValues(other_torques);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(30, 0);

    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 30);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 1);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_POSITION_CONTROL);
    
    result = *initial_control_signal.CreateProtobufControlSignal(0, 2);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_IMPEDANCE_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 3);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_VELOCITY_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 4);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::JOINT_TORQUE_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 5);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::CARTESIAN_POSITION_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 6);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::CARTESIAN_IMPEDANCE_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 7);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::CARTESIAN_VELOCITY_CONTROL);

    result = *initial_control_signal.CreateProtobufControlSignal(0, 8);
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::WRENCH_CONTROL);
}

TEST_F(TestControlSignal, TestStop) {
    kuka::external::control::iiqka::ArenaWrapper<kuka::ecs::v1::ControlSignalExternal> arena;
    kuka::external::control::iiqka::ControlSignal initial_control_signal(&arena, 6);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0, true);

    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_TRUE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
    initial_control_signal.AddJointPositionValues(positions);
    
    kuka::ecs::v1::ControlSignalExternal result = *initial_control_signal.CreateProtobufControlSignal(0, 0);

    std::vector<double> other_positions = {2.0, 3.0, 4.0, 5.0, 6.0};
    initial_control_signal.AddJointPositionValues(other_positions);
    
    EXPECT_TRUE(result.has_header());
    EXPECT_EQ(result.header().ipoc(), 0);
    EXPECT_TRUE(result.has_control_signal());
    EXPECT_FALSE(result.control_signal().stop_ipo());
    EXPECT_EQ(result.control_signal().control_mode(), kuka::motion::external::EXTERNAL_CONTROL_MODE_UNSPECIFIED);
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
        EXPECT_NEAR(result.control_signal().joint_command().values(i), 12 + (double)i, 0.02);
    }
}