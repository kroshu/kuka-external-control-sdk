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

class iiQKARobot : public ::testing::Test {
 protected:
  kuka::external::control::iiqka::Configuration eci_config_;
  std::unique_ptr<kuka::external::control::iiqka::Robot> robot_;
  std::unique_ptr<kuka::external::control::test::FakeCommandHandlingService> service_;

  iiQKARobot(){};

  virtual ~iiQKARobot() = default;

  virtual void SetUp() {
    eci_config_.client_ip_address = "127.0.0.1";
    eci_config_.koni_ip_address = "127.0.0.3";
    robot_ = std::make_unique<kuka::external::control::iiqka::Robot>(eci_config_);
    service_ = std::make_unique<kuka::external::control::test::FakeCommandHandlingService>();
    service_->Setup(eci_config_.koni_ip_address);
  }

  virtual void TearDown() {
    robot_.reset();
    service_.reset();
  }
};

TEST_F(iiQKARobot, CheckSendReplyNotInitialized) {
  kuka::external::control::ReturnCode start_control = robot_->StartControlling().return_code;
  EXPECT_EQ(start_control, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode send_ret = robot_->SendControlSignal().return_code;
  EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, CheckMonitoringNotInitialized) {
  kuka::external::control::ReturnCode start_monitoring = robot_->StartMonitoring().return_code;
  EXPECT_EQ(start_monitoring, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, CheckMonitoring) {
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_monitoring = robot_->StartMonitoring().return_code;
  EXPECT_EQ(start_monitoring, kuka::external::control::ReturnCode::OK);

  std::vector<double> measured_positions(6, 1);
  std::vector<double> measured_torques(6, 0);

  kuka::external::control::ReturnCode create_sub =
      robot_
          ->CreateMonitoringSubscription(
              [&](kuka::external::control::BaseMotionState& incoming_motion_state) {
                std::copy_n(incoming_motion_state.GetMeasuredPositions()->begin(), 6,
                            measured_positions.begin());
                std::copy_n(incoming_motion_state.GetMeasuredTorques()->begin(), 6,
                            measured_torques.begin());
              })
          .return_code;

  EXPECT_EQ(create_sub, kuka::external::control::ReturnCode::OK);
  std::this_thread::sleep_for(std::chrono::seconds(1));

  kuka::external::control::ReturnCode unsub = robot_->CancelMonitoringSubscription().return_code;
  EXPECT_EQ(unsub, kuka::external::control::ReturnCode::OK);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_EQ(measured_positions, std::vector<double>({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));
  EXPECT_EQ(measured_torques, std::vector<double>({12, 12, 12, 12, 12, 12}));

  kuka::external::control::ReturnCode stop_monitoring = robot_->StopMonitoring().return_code;
  EXPECT_EQ(stop_monitoring, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, StartAndStopControllingBad) {
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling = robot_->StartControlling().return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  // Waiting to timeout
  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, StartAndStopControllingGood) {
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling = robot_->StartControlling().return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
      robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, StartControllingTwice) {
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling = robot_->StartControlling().return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
      robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  // Waiting to timeout
  start_controlling = robot_->StartControlling().return_code;
  EXPECT_EQ(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

TEST_F(iiQKARobot, CheckControlling) {
  kuka::external::control::ReturnCode setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::OK);

  kuka::external::control::ReturnCode start_controlling = robot_->StartControlling().return_code;
  EXPECT_NE(start_controlling, kuka::external::control::ReturnCode::ERROR);

  kuka::external::control::ReturnCode receive_motion_state =
      robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
  EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);

  auto& last_motion_state = robot_->GetLastMotionState();
  EXPECT_EQ(*(last_motion_state.GetMeasuredPositions()),
            std::vector<double>({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));

  EXPECT_EQ(*(last_motion_state.GetMeasuredTorques()),
            std::vector<double>({12, 12, 12, 12, 12, 12}));

  std::vector<double> send_positions(6, 0);
  std::vector<double> send_torques(6, 12);

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(*(robot_->GetLastMotionState().GetMeasuredPositions()),
              std::vector<double>({0.0 + i * 3., 0, 0, 0, 0, 0}));
    EXPECT_EQ(*(robot_->GetLastMotionState().GetMeasuredTorques()),
              std::vector<double>({12, 12, 12, 12, 12, 12 + i * 5.0}));

    send_positions[0] = last_motion_state.GetMeasuredPositions()->at(0) + 3.0;
    send_torques[5] = last_motion_state.GetMeasuredTorques()->at(5) + 5.0;

    robot_->GetControlSignal().AddJointPositionValues(send_positions);
    robot_->GetControlSignal().AddTorqueValues(send_torques);

    auto send_ret = robot_->SendControlSignal().return_code;
    EXPECT_EQ(send_ret, kuka::external::control::ReturnCode::OK);

    receive_motion_state = robot_->ReceiveMotionState(std::chrono::seconds(8)).return_code;
    EXPECT_EQ(receive_motion_state, kuka::external::control::ReturnCode::OK);
  }

  kuka::external::control::ReturnCode stop_controlling = robot_->StopControlling().return_code;
  EXPECT_EQ(stop_controlling, kuka::external::control::ReturnCode::OK);
}

// Test Setup with invalid IP
TEST_F(iiQKARobot, TestSetup) {
  eci_config_.client_ip_address = "Invalid client IP";
  robot_ = std::make_unique<kuka::external::control::iiqka::Robot>(eci_config_);

  auto setup_ret = robot_->Setup().return_code;
  EXPECT_EQ(setup_ret, kuka::external::control::ReturnCode::ERROR);
}

TEST_F(iiQKARobot, TestEmptyQoS) {
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
