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

#include "kuka/external-control-sdk/iiqka/robot.h"
#include "test-assets/fake_command_handling_service.h"

using ::testing::Test;

// Note that while the control signal / motion state values are expected to be filled by radians,
// the tests may not follow this rule
class iiQKARobot : public ::testing::Test
{
protected:
  kuka::external::control::iiqka::Configuration eci_config_;
  std::unique_ptr<kuka::external::control::iiqka::Robot> robot_;
  std::unique_ptr<kuka::external::control::test::FakeCommandHandlingService> service_;

  iiQKARobot();

  virtual ~iiQKARobot() = default;

  virtual void SetUp()
  {
    eci_config_.client_ip_address = "127.0.0.1";
    eci_config_.koni_ip_address = "127.0.0.3";
    robot_ = std::make_unique<kuka::external::control::iiqka::Robot>(eci_config_);
    service_ = std::make_unique<kuka::external::control::test::FakeCommandHandlingService>();
    service_->Setup(eci_config_.koni_ip_address);
  }

  virtual void TearDown()
  {
    robot_.reset();
    service_.reset();
  }

  static constexpr double D_TOLERANCE = 0.01;
};

// Test Setup with invalid IP
TEST_F(iiQKARobot, TestSetupInvalidIP)
{
  eci_config_.client_ip_address = "Invalid client IP";
  robot_ = std::make_unique<kuka::external::control::iiqka::Robot>(eci_config_);

  auto setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, TestSetupValidIP)
{
  eci_config_.client_ip_address = "127.0.0.3";
  robot_ = std::make_unique<kuka::external::control::iiqka::Robot>(eci_config_);

  auto setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, TestEmptyQoS)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::ecs::v1::SetQoSProfileRequest request;
  kuka::ecs::v1::SetQoSProfileResponse response;
  grpc::ClientContext context;

  std::unique_ptr<kuka::ecs::v1::ExternalControlService::Stub> stub =
    kuka::ecs::v1::ExternalControlService::NewStub(
      grpc::CreateChannel("127.0.0.3:49335", grpc::InsecureChannelCredentials()));

  EXPECT_TRUE(!stub->SetQoSProfile(&context, request, &response).ok());
}

TEST_F(iiQKARobot, TestSendReplyNotInitialized)
{
  kuka::external::control::ReturnCode start_control =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_EQ(start_control, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, TestMonitoringNotInitialized)
{
  kuka::external::control::ReturnCode start_monitoring = robot_->StartMonitoring().return_code;
  EXPECT_EQ(start_monitoring, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, TestMonitoring)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_monitoring = robot_->StartMonitoring().return_code;
  EXPECT_EQ(start_monitoring, kuka::external::control::ReturnCode::OK);

  std::vector<double> measured_positions(6, 1);
  std::vector<double> measured_torques(6, 0);

  kuka::external::control::ReturnCode create_sub =
    robot_
      ->CreateMonitoringSubscription(
        [&](kuka::external::control::BaseMotionState & incoming_motion_state)
        {
          std::copy_n(
            incoming_motion_state.GetMeasuredPositions().begin(), 6, measured_positions.begin());
          std::copy_n(
            incoming_motion_state.GetMeasuredTorques().begin(), 6, measured_torques.begin());
        })
      .return_code;

  EXPECT_EQ(create_sub, kuka::external::control::ReturnCode::OK);
  std::this_thread::sleep_for(std::chrono::seconds(1));

  kuka::external::control::ReturnCode unsub = robot_->CancelMonitoringSubscription().return_code;
  EXPECT_EQ(unsub, kuka::external::control::ReturnCode::OK);

  EXPECT_EQ(measured_positions, std::vector<double>({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));
  EXPECT_EQ(measured_torques, std::vector<double>({12, 12, 12, 12, 12, 12}));

  kuka::external::control::ReturnCode stop_monitoring = robot_->StopMonitoring().return_code;
  EXPECT_EQ(stop_monitoring, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, StopControllingWithoutPreviousRequest)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  // StopControlling now also receives if necessary
  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, StopControllingWithPreviousRequestReceived)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, StartControllingTwice)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  // Waiting to timeout
  start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_EQ(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, TestControllingLoop)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  auto & last_motion_state = robot_->GetLastMotionState();
  EXPECT_EQ(
    last_motion_state.GetMeasuredPositions(), std::vector<double>({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));

  EXPECT_EQ(last_motion_state.GetMeasuredTorques(), std::vector<double>({12, 12, 12, 12, 12, 12}));

  std::vector<double> send_positions(6, 0);

  for (int i = 0; i < 15; ++i)
  {
    EXPECT_EQ(
      robot_->GetLastMotionState().GetMeasuredPositions(),
      std::vector<double>({0.0 + i * 3., 0, 0, 0, 0, 0}));

    send_positions[0] = last_motion_state.GetMeasuredPositions()[0] + 3.0;

    robot_->GetControlSignal().AddJointPositionValues(send_positions.begin(), send_positions.end());

    auto send_ret = robot_->SendControlSignal().return_code;
    EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

    receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
    EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);
  }

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

// Velocity values should be ignored
TEST_F(iiQKARobot, TestAddVelocity)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_VELOCITY_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_velocities;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_velocities =
    robot_->GetLastMotionState().GetMeasuredVelocities();
  for (int i = 0; i < motion_state_velocities.size(); ++i)
  {
    EXPECT_NEAR(motion_state_velocities[i], 0.0, D_TOLERANCE);
  }

  send_velocities = std::vector<double>{7.0, 7.0, 7.0, 7.0, 7.0, 7.0};
  robot_->GetControlSignal().AddVelocityValues(send_velocities.begin(), send_velocities.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_velocities = robot_->GetLastMotionState().GetMeasuredVelocities();
  for (int i = 0; i < motion_state_velocities.size(); ++i)
  {
    EXPECT_NEAR(motion_state_velocities[i], 0.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}

TEST_F(iiQKARobot, TestAddVelocityInPositionControl)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_velocities;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_velocities =
    robot_->GetLastMotionState().GetMeasuredVelocities();
  for (int i = 0; i < motion_state_velocities.size(); ++i)
  {
    EXPECT_NEAR(motion_state_velocities[i], 0.0, D_TOLERANCE);
  }

  send_velocities = std::vector<double>{7.0, 7.0, 7.0, 7.0, 7.0, 7.0};
  robot_->GetControlSignal().AddVelocityValues(send_velocities.begin(), send_velocities.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_velocities = robot_->GetLastMotionState().GetMeasuredVelocities();
  for (int i = 0; i < motion_state_velocities.size(); ++i)
  {
    EXPECT_NEAR(motion_state_velocities[i], 0.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}

TEST_F(iiQKARobot, TestAddPositions)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_IMPEDANCE_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_positions;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  send_positions = std::vector<double>{7.0, 7.0, 7.0, 7.0, 7.0, 7.0};
  robot_->GetControlSignal().AddJointPositionValues(send_positions.begin(), send_positions.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 7.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}

TEST_F(iiQKARobot, TestAddPositionsWithOversizedVector)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_IMPEDANCE_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_positions;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  send_positions = std::vector<double>{7.0, 7.0, 7.0, 7.0, 7.0, 7.0, 4.0, 9.0, 12.0};
  robot_->GetControlSignal().AddJointPositionValues(send_positions.begin(), send_positions.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 7.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}

TEST_F(iiQKARobot, TestAddPositionsWithUndersizedVector)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_IMPEDANCE_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_positions;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  send_positions = std::vector<double>{1.0, 2.3, 5.7};
  robot_->GetControlSignal().AddJointPositionValues(send_positions.begin(), send_positions.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  EXPECT_NEAR(motion_state_positions[0], 1.0, 0.1);
  EXPECT_NEAR(motion_state_positions[1], 2.3, 0.1);
  EXPECT_NEAR(motion_state_positions[2], 5.7, 0.1);
  for (int i = 3; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}

TEST_F(iiQKARobot, TestAddPositionsWithEmptydVector)
{
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling =
    robot_->StartControlling(kuka::external::control::ControlMode::JOINT_IMPEDANCE_CONTROL)
      .return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  std::vector<double> send_positions;

  kuka::external::control::ReturnCode receive_motion_state =
    robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  std::vector<double> motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  robot_->GetControlSignal().AddJointPositionValues(send_positions.begin(), send_positions.end());
  auto send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

  receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(3)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  motion_state_positions = robot_->GetLastMotionState().GetMeasuredPositions();
  for (int i = 0; i < motion_state_positions.size(); ++i)
  {
    EXPECT_NEAR(motion_state_positions[i], 0.0, D_TOLERANCE);
  }

  robot_->StopControlling();
}
