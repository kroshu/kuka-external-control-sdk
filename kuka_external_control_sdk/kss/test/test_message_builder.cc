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

#include <cmath>

#include "kuka/external-control-sdk/kss/message_builder.h"

using ::testing::Test;

static constexpr std::size_t kFixSixAxes = 6;

std::vector<kuka::external::control::kss::JointConfiguration> GetSixAxesConfig() {
  using JC = kuka::external::control::kss::JointConfiguration;
  std::vector<JC> joint_configs;
  joint_configs.reserve(kFixSixAxes);
  for (std::size_t i = 0; i < kFixSixAxes; ++i) {
    joint_configs.emplace_back("joint_"+ std::to_string(i+1), JC::Type::REVOLUTE, false);
  }
  return joint_configs;
}

class KSSControlSignal : public ::testing::Test {
protected:
  virtual ~KSSControlSignal() = default;

  virtual void SetUp() {}

  virtual void TearDown() {}
};

class KSSMotionState : public ::testing::Test {
protected:
  virtual ~KSSMotionState() = default;

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(KSSMotionState, TestZeroInit6Dof) {
  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes, {}, GetSixAxesConfig());
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto v : initial_motion_state.GetMeasuredCartesianPositions()) { EXPECT_FLOAT_EQ(v, 0.0); }

  for (auto v : initial_motion_state.GetMeasuredPositions()) { EXPECT_FLOAT_EQ(v, 0.0); }

  EXPECT_EQ(initial_motion_state.GetDelay(), 15);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestZeroInit6DofWith1ExternalAxis) {
  using JC = kuka::external::control::kss::JointConfiguration;
  std::vector<JC> joint_configs;
  joint_configs.emplace_back("rail_joint", JC::Type::PRISMATIC, true);

  std::vector<JC> six_axes_config = GetSixAxesConfig();
  joint_configs.insert(joint_configs.end(), six_axes_config.begin(), six_axes_config.end());

  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes + 1, {}, joint_configs);
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto v : initial_motion_state.GetMeasuredCartesianPositions()) { EXPECT_FLOAT_EQ(v, 0.0); }

  for (auto v : initial_motion_state.GetMeasuredPositions()) { EXPECT_FLOAT_EQ(v, 0.0); }

  EXPECT_EQ(initial_motion_state.GetDelay(), 15);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInitJointPositions6Dof) {
  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes, {}, GetSixAxesConfig());
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"5.32000\" A2=\"6.4\" A3=\"111.30000\" A4=\"12.20000\" A5=\"0.00000\" A6=\"12.50000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"0\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) { EXPECT_EQ(k, 0.0); }

  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 0.092851, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[1], 0.1117010, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[2], 1.9425514, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[3], 0.21331763, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[4], 0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[5], 0.218166156, 0.002);

  EXPECT_EQ(initial_motion_state.GetDelay(), 0);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInitCartesianPositions6Dof) {
  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes, {}, GetSixAxesConfig());
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" C=\"12.50000\"/><AIPos A1=\"0.000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"8\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto k : initial_motion_state.GetMeasuredPositions()) { EXPECT_EQ(k, 0.0); }

  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[0], 5.32, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[1], 6.4, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[2], 111.3, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.21293, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[4], 0.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[5], 0.218166, 0.002);

  EXPECT_EQ(initial_motion_state.GetDelay(), 8);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestFillEverything) {
  using JC = kuka::external::control::kss::JointConfiguration;
  std::vector<JC> joint_configs;
  for (std::size_t i = 0; i < kFixSixAxes; ++i) {
    joint_configs.emplace_back("ext_joint_" + std::to_string(i + 1), JC::Type::PRISMATIC, true);
  }

  std::vector<JC> six_axes_config = GetSixAxesConfig();
  joint_configs.insert(joint_configs.end(), six_axes_config.begin(), six_axes_config.end());

  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes * 2, {}, joint_configs);
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" C=\"12.50000\"/><AIPos A1=\"8.2\" A2=\"3.3\" A3=\"111.67\" A4=\"12.22220\" A5=\"-35.20000\" A6=\"-12.50000\"/><EIPos E1=\"1000.00000\" E2=\"2000.00000\" E3=\"3000.00000\" E4=\"4000.00000\" E5=\"5000.00000\" E6=\"6000.00000\"/><Delay D=\"11\"/><IPOC>357</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[0], 5.32, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[1], 6.4, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[2], 111.3, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.21293, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[4], 0.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[5], 0.218166, 0.002);

  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 1.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[1], 2.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[2], 3.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[3], 4.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[4], 5.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[5], 6.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[6], 0.14311699, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[7], 0.0575958, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[8], 1.9490091, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[9], 0.213317, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[10], -0.614355, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[11], -0.218166, 0.002);

  EXPECT_EQ(initial_motion_state.GetDelay(), 11);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 357);
}

TEST_F(KSSControlSignal, TestZeroInit6Dof) {
  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes, {}, GetSixAxesConfig());
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"1.00000\" A2=\"1.00000\" A3=\"1.00000\" A4=\"1.00000\" A5=\"1.00000\" A6=\"1.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  kuka::external::control::kss::ControlSignal control_signal(kFixSixAxes, {}, GetSixAxesConfig());
  control_signal.SetInitialPositions(initial_motion_state);

  const char* expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK A1=\"-1.000000\" A2=\"-1.000000\" A3=\"-1.000000\" A4=\"-1.000000\" A5=\"-1.000000\" A6=\"-1.000000\"/><IPOC>0</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestFillEverything6Dof) {
  kuka::external::control::kss::ControlSignal control_signal(kFixSixAxes, {}, GetSixAxesConfig());

  std::vector<double> values = {3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
  control_signal.AddJointPositionValues(values.begin(), values.end());
  const char* expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>1</Stop><AK A1=\"194.805650\" A2=\"194.805650\" A3=\"194.805650\" A4=\"194.805650\" A5=\"194.805650\" A6=\"194.805650\"/><IPOC>543265442</IPOC></Sen>";

  EXPECT_STREQ(control_signal.CreateXMLString(543265442, true).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestFillEverything) {
  using JC = kuka::external::control::kss::JointConfiguration;
  std::vector<JC> joint_configs;
  for (std::size_t i = 0; i < kFixSixAxes; ++i) {
    joint_configs.emplace_back("ext_joint_" + std::to_string(i + 1), JC::Type::PRISMATIC, true);
  }

  std::vector<JC> six_axes_config = GetSixAxesConfig();
  joint_configs.insert(joint_configs.end(), six_axes_config.begin(), six_axes_config.end());

  kuka::external::control::kss::MotionState initial_motion_state(kFixSixAxes * 2, {}, joint_configs);
  const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.0\" Y=\"0.0\" Z=\"0.0\" A=\"0.0\" B=\"0.0\" C=\"0.0\"/><AIPos A1=\"0.0\" A2=\"0.0\" A3=\"0.0\" A4=\"0.0\" A5=\"0.0\" A6=\"0.0\"/><EIPos E1=\"0.0\" E2=\"0.0\" E3=\"0.0\" E4=\"0.0\" E5=\"0.0\" E6=\"0.0\"/><Delay D=\"0\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  kuka::external::control::kss::ControlSignal control_signal(kFixSixAxes * 2, {}, joint_configs);
  std::vector<double> values = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
  control_signal.AddJointPositionValues(values.begin(), values.end());
  const char* expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>1</Stop><AK A1=\"194.805650\" A2=\"194.805650\" A3=\"194.805650\" A4=\"194.805650\" A5=\"194.805650\" A6=\"194.805650\"/><EK E1=\"1000.000000\" E2=\"1000.000000\" E3=\"1000.000000\" E4=\"1000.000000\" E5=\"1000.000000\" E6=\"1000.000000\"/><IPOC>543265442</IPOC></Sen>";

  EXPECT_STREQ(control_signal.CreateXMLString(543265442, true).value().data(), expected_xml);
}
