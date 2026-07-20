// Copyright 2026 KUKA Deutschland GmbH
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
#include <cstdio>
#include <limits>

#include "kuka/external-control-sdk/kss/message_builder.h"

using kuka::external::control::kss::ControlSignal;
using kuka::external::control::kss::ControlSignalXmlConfiguration;
using kuka::external::control::kss::ControlSignalXmlFieldType;
using kuka::external::control::kss::JointConfiguration;
using kuka::external::control::kss::MotionState;
using kuka::external::control::kss::MotionStateSignalType;
using kuka::external::control::kss::MotionStateXmlConfiguration;
using kuka::external::control::kss::MotionStateXmlFieldType;
using ::testing::Test;

static constexpr std::size_t kFixSixAxes = 6;

std::vector<kuka::external::control::kss::JointConfiguration> GetJointConfig(
  const std::size_t num_external, const std::size_t num_internal)
{
  using JC = kuka::external::control::kss::JointConfiguration;
  std::vector<JC> joint_configs;
  joint_configs.reserve(num_external + num_internal);
  for (std::size_t i = 0; i < num_external; ++i)
  {
    joint_configs.emplace_back("ext_joint_" + std::to_string(i + 1), JC::Type::PRISMATIC, true);
  }
  for (std::size_t i = 0; i < num_internal; ++i)
  {
    joint_configs.emplace_back("joint_" + std::to_string(i + 1), JC::Type::REVOLUTE, false);
  }
  return joint_configs;
}

class KSSControlSignal : public ::testing::Test
{
protected:
  virtual ~KSSControlSignal() = default;

  virtual void SetUp() {}

  virtual void TearDown() {}
};

class KSSMotionState : public ::testing::Test
{
protected:
  virtual ~KSSMotionState() = default;

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(KSSMotionState, TestZeroInit6Dof)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" "
    "B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" "
    "A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" "
    "E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay "
    "D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto v : initial_motion_state.GetMeasuredCartesianPositions())
  {
    EXPECT_FLOAT_EQ(v, 0.0);
  }

  for (auto v : initial_motion_state.GetMeasuredPositions())
  {
    EXPECT_FLOAT_EQ(v, 0.0);
  }

  EXPECT_EQ(initial_motion_state.GetDelay(), 15);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestZeroInit6DofWith1ExternalAxis)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes + 1, {}, GetJointConfig(1, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" "
    "B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" "
    "A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" "
    "E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay "
    "D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto v : initial_motion_state.GetMeasuredCartesianPositions())
  {
    EXPECT_FLOAT_EQ(v, 0.0);
  }

  for (auto v : initial_motion_state.GetMeasuredPositions())
  {
    EXPECT_FLOAT_EQ(v, 0.0);
  }

  EXPECT_EQ(initial_motion_state.GetDelay(), 15);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInitJointPositions6Dof)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" "
    "B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"5.32000\" A2=\"6.4\" A3=\"111.30000\" "
    "A4=\"12.20000\" A5=\"0.00000\" A6=\"12.50000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" "
    "E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay "
    "D=\"0\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto k : initial_motion_state.GetMeasuredCartesianPositions())
  {
    EXPECT_EQ(k, 0.0);
  }

  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 0.092851, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[1], 0.1117010, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[2], 1.9425514, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[3], 0.21331763, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[4], 0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[5], 0.218166156, 0.002);

  EXPECT_EQ(initial_motion_state.GetDelay(), 0);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInitCartesianPositions6Dof)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" "
    "C=\"12.50000\"/><AIPos A1=\"0.000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" "
    "A5=\"0.00000\" A6=\"0.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" E3=\"0.00000\" "
    "E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay D=\"8\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  for (auto k : initial_motion_state.GetMeasuredPositions())
  {
    EXPECT_EQ(k, 0.0);
  }

  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[0], 5.32, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[1], 6.4, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[2], 111.3, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.21293, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[4], 0.0, 0.002);
  EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[5], 0.218166, 0.002);

  EXPECT_EQ(initial_motion_state.GetDelay(), 8);
  EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestFillEverything)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes * 2, {}, GetJointConfig(kFixSixAxes, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" "
    "C=\"12.50000\"/><AIPos A1=\"8.2\" A2=\"3.3\" A3=\"111.67\" A4=\"12.22220\" A5=\"-35.20000\" "
    "A6=\"-12.50000\"/><EIPos E1=\"1000.00000\" E2=\"2000.00000\" E3=\"3000.00000\" "
    "E4=\"4000.00000\" E5=\"5000.00000\" E6=\"6000.00000\"/><Delay "
    "D=\"11\"/><IPOC>357</IPOC></Rob>";
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

TEST_F(KSSMotionState, TestMotionStateAcceptsMixedJointOrder)
{
  auto joint_config = GetJointConfig(0, kFixSixAxes);
  auto ext_config = GetJointConfig(kFixSixAxes, 0);
  joint_config.insert(joint_config.end(), ext_config.begin(), ext_config.end());

  EXPECT_NO_THROW(kuka::external::control::kss::MotionState(kFixSixAxes * 2, {}, joint_config));
}

TEST_F(KSSMotionState, TestCustomXmlConfiguration)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
    {"joint_2", JointConfiguration::Type::PRISMATIC, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_1", MotionStateSignalType::VELOCITY, "Axes", "j1_vel"},
    {"joint_2", MotionStateSignalType::POSITION, "Axes", "j2_pos"},
    {"joint_2", MotionStateSignalType::VELOCITY, "Axes", "j2_vel"},
    {"joint_1", MotionStateSignalType::TORQUE, "Forces", "j1_trq"},
    {"joint_2", MotionStateSignalType::TORQUE, "Forces", "j2_trq"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0}, {MotionStateXmlFieldType::JOINT, 1},
    {MotionStateXmlFieldType::JOINT, 2}, {MotionStateXmlFieldType::JOINT, 3},
    {MotionStateXmlFieldType::JOINT, 4}, {MotionStateXmlFieldType::JOINT, 5},
  };

  MotionState motion_state(2, {}, joints, xml_cfg);
  const char * xml =
    "<Rob Type=\"KUKA\"><Axes j1_pos=\"90.0\" j1_vel=\"180.0\" j2_pos=\"1000.0\" "
    "j2_vel=\"2000.0\"/><Forces j1_trq=\"10.0\" j2_trq=\"12.5\"/><Delay D=\"3\"/><IPOC>9</IPOC>"
    "</Rob>";

  motion_state.CreateFromXML(xml);

  EXPECT_NEAR(motion_state.GetMeasuredPositions()[0], M_PI / 2.0, 0.0001);
  EXPECT_NEAR(motion_state.GetMeasuredVelocities()[0], M_PI, 0.0001);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredPositions()[1], 1.0);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredVelocities()[1], 2.0);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredTorques()[0], 10.0);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredTorques()[1], 12.5);
  EXPECT_EQ(motion_state.GetDelay(), 3);
  EXPECT_EQ(motion_state.GetIpoc(), 9);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsPartialVelocityFields)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
    {"joint_2", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_2", MotionStateSignalType::POSITION, "Axes", "j2_pos"},
    {"joint_1", MotionStateSignalType::VELOCITY, "Axes", "j1_vel"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::JOINT, 1},
    {MotionStateXmlFieldType::JOINT, 2},
  };

  EXPECT_THROW(MotionState(2, {}, joints, xml_cfg), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsPartialInternalTorqueFields)
{
  std::vector<JointConfiguration> joints = {
    {"ext_joint_1", JointConfiguration::Type::PRISMATIC, true},
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
    {"joint_2", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"ext_joint_1", MotionStateSignalType::POSITION, "Axes", "e1_pos"},
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_2", MotionStateSignalType::POSITION, "Axes", "j2_pos"},
    {"joint_1", MotionStateSignalType::TORQUE, "Forces", "j1_trq"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::JOINT, 1},
    {MotionStateXmlFieldType::JOINT, 2},
    {MotionStateXmlFieldType::JOINT, 3},
  };

  EXPECT_THROW(MotionState(3, {}, joints, xml_cfg), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsPartialExternalTorqueFields)
{
  std::vector<JointConfiguration> joints = {
    {"ext_joint_1", JointConfiguration::Type::PRISMATIC, true},
    {"ext_joint_2", JointConfiguration::Type::PRISMATIC, true},
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"ext_joint_1", MotionStateSignalType::POSITION, "Axes", "e1_pos"},
    {"ext_joint_2", MotionStateSignalType::POSITION, "Axes", "e2_pos"},
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"ext_joint_1", MotionStateSignalType::TORQUE, "Forces", "e1_trq"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::JOINT, 1},
    {MotionStateXmlFieldType::JOINT, 2},
    {MotionStateXmlFieldType::JOINT, 3},
  };

  EXPECT_THROW(MotionState(3, {}, joints, xml_cfg), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationAllowsExternalTorqueWithoutInternalTorque)
{
  std::vector<JointConfiguration> joints = {
    {"ext_joint_1", JointConfiguration::Type::PRISMATIC, true},
    {"ext_joint_2", JointConfiguration::Type::PRISMATIC, true},
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
    {"joint_2", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"ext_joint_1", MotionStateSignalType::POSITION, "Axes", "e1_pos"},
    {"ext_joint_2", MotionStateSignalType::POSITION, "Axes", "e2_pos"},
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_2", MotionStateSignalType::POSITION, "Axes", "j2_pos"},
    {"ext_joint_1", MotionStateSignalType::TORQUE, "Forces", "e1_trq"},
    {"ext_joint_2", MotionStateSignalType::TORQUE, "Forces", "e2_trq"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0}, {MotionStateXmlFieldType::JOINT, 1},
    {MotionStateXmlFieldType::JOINT, 2}, {MotionStateXmlFieldType::JOINT, 3},
    {MotionStateXmlFieldType::JOINT, 4}, {MotionStateXmlFieldType::JOINT, 5},
  };

  MotionState motion_state(4, {}, joints, xml_cfg);
  const char * xml =
    "<Rob Type=\"KUKA\"><Axes e1_pos=\"1000.0\" e2_pos=\"2000.0\" j1_pos=\"90.0\" "
    "j2_pos=\"45.0\"/><Forces e1_trq=\"10.0\" e2_trq=\"11.0\"/><Delay D=\"3\"/><IPOC>9</IPOC>"
    "</Rob>";

  motion_state.CreateFromXML(xml);

  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredPositions()[0], 1.0);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredPositions()[1], 2.0);
  EXPECT_NEAR(motion_state.GetMeasuredPositions()[2], M_PI / 2.0, 0.0001);
  EXPECT_NEAR(motion_state.GetMeasuredPositions()[3], M_PI / 4.0, 0.0001);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredTorques()[0], 10.0);
  EXPECT_DOUBLE_EQ(motion_state.GetMeasuredTorques()[1], 11.0);
  EXPECT_TRUE(std::isnan(motion_state.GetMeasuredTorques()[2]));
  EXPECT_TRUE(std::isnan(motion_state.GetMeasuredTorques()[3]));
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsAttributePrefixMatch)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "A"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
  };

  MotionState motion_state(1, {}, joints, xml_cfg);
  const char * xml = "<Rob Type=\"KUKA\"><Axes AAA=\"90.0\"/><Delay D=\"0\"/><IPOC>1</IPOC></Rob>";

  EXPECT_THROW(motion_state.CreateFromXML(xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationAcceptsFieldOrderWithoutDelayAndIpoc)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
  };
  EXPECT_NO_THROW(MotionState(1, {}, joints, xml_cfg));
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsDelayAndIpocInFieldOrder)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::DELAY, 0},
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::IPOC, 0},
    {MotionStateXmlFieldType::IPOC, 0},
  };

  EXPECT_THROW(MotionState(1, {}, joints, xml_cfg), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsMissingPositionForJoint)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
    {"joint_2", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_2", MotionStateSignalType::TORQUE, "Forces", "j2_trq"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::JOINT, 1},
  };

  EXPECT_THROW(MotionState(2, {}, joints, xml_cfg), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationRejectsMissingDelayElementInMessage)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
    {"joint_1", MotionStateSignalType::TORQUE, "Forces", "t1"},
  };
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::JOINT, 1},
  };

  MotionState motion_state(1, {}, joints, xml_cfg);
  const char * xml =
    "<Rob Type=\"KUKA\"><Axes j1_pos=\"0.0\"/><Forces t1=\"12.5\"/><IPOC>9</IPOC></Rob>";

  EXPECT_THROW(motion_state.CreateFromXML(xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCustomXmlConfigurationParsesDelayAfterGpio)
{
  std::vector<JointConfiguration> joints = {
    {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  };
  std::vector<kuka::external::control::kss::GPIOConfiguration> gpio_configs = {
    {"g1", kuka::external::control::GPIOValueType::BOOL},
  };

  MotionStateXmlConfiguration xml_cfg;
  xml_cfg.cartesian.enabled = false;
  xml_cfg.joint_fields = {
    {"joint_1", MotionStateSignalType::POSITION, "Axes", "j1_pos"},
  };
  xml_cfg.gpio_xml_element = "Io";
  xml_cfg.gpio_xml_attributes = {"g1"};
  xml_cfg.field_order = {
    {MotionStateXmlFieldType::JOINT, 0},
    {MotionStateXmlFieldType::GPIO, 0},
  };

  MotionState motion_state(1, gpio_configs, joints, xml_cfg);
  const char * xml =
    "<Rob Type=\"KUKA\"><Axes j1_pos=\"90.0\"/><Io g1=\"1\"/><Delay D=\"4\"/><IPOC>5</IPOC></Rob>";
  EXPECT_NO_THROW(motion_state.CreateFromXML(xml));
  EXPECT_NEAR(motion_state.GetMeasuredPositions()[0], M_PI / 2.0, 0.0001);
  EXPECT_EQ(motion_state.GetDelay(), 4);
  EXPECT_EQ(motion_state.GetIpoc(), 5);
}

TEST_F(KSSMotionState, TestCreateFromXMLParsesConsecutiveMessages)
{
  MotionState motion_state(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));

  const char * first_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.0\" Y=\"0.0\" Z=\"0.0\" A=\"0.0\" B=\"0.0\" C=\"0.0\"/>"
    "<AIPos A1=\"0.0\" A2=\"0.0\" A3=\"0.0\" A4=\"0.0\" A5=\"0.0\" A6=\"0.0\"/>"
    "<EIPos E1=\"0.0\" E2=\"0.0\" E3=\"0.0\" E4=\"0.0\" E5=\"0.0\" E6=\"0.0\"/>"
    "<Delay D=\"0\"/><IPOC>10</IPOC></Rob>";
  const char * second_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.0\" Y=\"0.0\" Z=\"0.0\" A=\"0.0\" B=\"0.0\" C=\"0.0\"/>"
    "<AIPos A1=\"1.0\" A2=\"2.0\" A3=\"3.0\" A4=\"4.0\" A5=\"5.0\" A6=\"6.0\"/>"
    "<EIPos E1=\"0.0\" E2=\"0.0\" E3=\"0.0\" E4=\"0.0\" E5=\"0.0\" E6=\"0.0\"/>"
    "<Delay D=\"1\"/><IPOC>11</IPOC></Rob>";

  EXPECT_NO_THROW(motion_state.CreateFromXML(first_xml));
  EXPECT_NO_THROW(motion_state.CreateFromXML(second_xml));

  EXPECT_EQ(motion_state.GetIpoc(), 11);
  EXPECT_EQ(motion_state.GetDelay(), 1);
  EXPECT_NEAR(motion_state.GetMeasuredPositions()[0], 1.0 * M_PI / 180.0, 0.0001);
  EXPECT_NEAR(motion_state.GetMeasuredPositions()[5], 6.0 * M_PI / 180.0, 0.0001);
}

TEST_F(KSSControlSignal, TestZeroInit6Dof)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" "
    "B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"1.00000\" A2=\"1.00000\" A3=\"1.00000\" "
    "A4=\"1.00000\" A5=\"1.00000\" A6=\"1.00000\"/><EIPos E1=\"0.00000\" E2=\"0.00000\" "
    "E3=\"0.00000\" E4=\"0.00000\" E5=\"0.00000\" E6=\"0.00000\"/><Delay "
    "D=\"15\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  kuka::external::control::kss::ControlSignal control_signal(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));
  control_signal.SetInitialPositions(initial_motion_state);

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK A1=\"-1.000000\" A2=\"-1.000000\" A3=\"-1.000000\" "
    "A4=\"-1.000000\" A5=\"-1.000000\" A6=\"-1.000000\"/><IPOC>0</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestFillEverything6Dof)
{
  kuka::external::control::kss::ControlSignal control_signal(
    kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));

  std::vector<double> values = {3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
  control_signal.AddJointPositionValues(values.begin(), values.end());
  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>1</Stop><AK A1=\"194.805650\" A2=\"194.805650\" A3=\"194.805650\" "
    "A4=\"194.805650\" A5=\"194.805650\" A6=\"194.805650\"/><IPOC>543265442</IPOC></Sen>";

  EXPECT_STREQ(control_signal.CreateXMLString(543265442, true).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestTorqueValuesAreNotIncludedByDefault)
{
  ControlSignal control_signal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes));

  std::vector<double> positions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::vector<double> torques = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" "
    "A4=\"0.000000\" A5=\"0.000000\" A6=\"0.000000\"/><IPOC>9</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(9).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestTorqueValuesAreIncludedWhenEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  xml_cfg.torque_xml_element = "TK";
  xml_cfg.torque_xml_attributes = {"A1", "A2", "A3", "A4", "A5", "A6"};

  ControlSignal control_signal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg);

  std::vector<double> positions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::vector<double> torques = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" "
    "A4=\"0.000000\" A5=\"0.000000\" A6=\"0.000000\"/><TK A1=\"1.000000\" A2=\"2.000000\" "
    "A3=\"3.000000\" A4=\"4.000000\" A5=\"5.000000\" A6=\"6.000000\"/><IPOC>11</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(11).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestVelocityValuesAreIncludedWhenEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_velocity_values = true;
  xml_cfg.velocity_xml_element = "VK";
  xml_cfg.velocity_xml_attributes = {"A1", "A2", "A3", "A4", "A5", "A6"};

  ControlSignal control_signal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg);

  std::vector<double> positions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::vector<double> velocities = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddVelocityValues(velocities.begin(), velocities.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" "
    "A4=\"0.000000\" A5=\"0.000000\" A6=\"0.000000\"/><VK A1=\"57.295780\" A2=\"114.591559\" "
    "A3=\"171.887339\" A4=\"229.183118\" A5=\"286.478898\" "
    "A6=\"343.774677\"/><IPOC>12</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(12).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestTorqueValuesInternalOnlyWithExternalAxes)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  // include_ext_torque_values intentionally left false

  ControlSignal control_signal(kFixSixAxes + 2, {}, GetJointConfig(2, kFixSixAxes), xml_cfg);

  std::vector<double> positions(8, 0.0);
  std::vector<double> torques = {100.0, 200.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<EK E1=\"0.000000\" E2=\"0.000000\"/>"
    "<TK A1=\"1.000000\" A2=\"2.000000\" A3=\"3.000000\" A4=\"4.000000\" A5=\"5.000000\" "
    "A6=\"6.000000\"/>"
    "<IPOC>5</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(5).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestExternalTorqueValuesWithoutInternalTorqueAreIncludedWhenEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_ext_torque_values = true;

  ControlSignal control_signal(kFixSixAxes + 2, {}, GetJointConfig(2, kFixSixAxes), xml_cfg);

  std::vector<double> positions(8, 0.0);
  std::vector<double> torques = {100.0, 200.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<EK E1=\"0.000000\" E2=\"0.000000\"/>"
    "<ETK E1=\"100.000000\" E2=\"200.000000\"/>"
    "<IPOC>8</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(8).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestExternalVelocityValuesWithoutInternalVelocityAreIncludedWhenEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_ext_velocity_values = true;

  ControlSignal control_signal(kFixSixAxes + 2, {}, GetJointConfig(2, kFixSixAxes), xml_cfg);

  std::vector<double> positions(8, 0.0);
  std::vector<double> velocities = {0.1, 0.2, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddVelocityValues(velocities.begin(), velocities.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<EK E1=\"0.000000\" E2=\"0.000000\"/>"
    "<EVK E1=\"100.000000\" E2=\"200.000000\"/>"
    "<IPOC>13</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(13).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestTorqueValuesWithExternalAxesWhenEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  xml_cfg.include_ext_torque_values = true;

  ControlSignal control_signal(kFixSixAxes + 2, {}, GetJointConfig(2, kFixSixAxes), xml_cfg);

  std::vector<double> positions(8, 0.0);
  std::vector<double> torques = {100.0, 200.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<EK E1=\"0.000000\" E2=\"0.000000\"/>"
    "<TK A1=\"1.000000\" A2=\"2.000000\" A3=\"3.000000\" A4=\"4.000000\" A5=\"5.000000\" "
    "A6=\"6.000000\"/>"
    "<ETK E1=\"100.000000\" E2=\"200.000000\"/>"
    "<IPOC>6</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(6).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestFillEverything)
{
  kuka::external::control::kss::MotionState initial_motion_state(
    kFixSixAxes * 2, {}, GetJointConfig(kFixSixAxes, kFixSixAxes));
  const char * rsi_xml =
    "<Rob Type=\"KUKA\"><RIst X=\"0.0\" Y=\"0.0\" Z=\"0.0\" A=\"0.0\" B=\"0.0\" C=\"0.0\"/><AIPos "
    "A1=\"0.0\" A2=\"0.0\" A3=\"0.0\" A4=\"0.0\" A5=\"0.0\" A6=\"0.0\"/><EIPos E1=\"0.0\" "
    "E2=\"0.0\" E3=\"0.0\" E4=\"0.0\" E5=\"0.0\" E6=\"0.0\"/><Delay D=\"0\"/><IPOC>0</IPOC></Rob>";
  initial_motion_state.CreateFromXML(rsi_xml);

  kuka::external::control::kss::ControlSignal control_signal(
    kFixSixAxes * 2, {}, GetJointConfig(kFixSixAxes, kFixSixAxes));
  std::vector<double> values = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
  control_signal.AddJointPositionValues(values.begin(), values.end());
  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>1</Stop><AK A1=\"194.805650\" A2=\"194.805650\" A3=\"194.805650\" "
    "A4=\"194.805650\" A5=\"194.805650\" A6=\"194.805650\"/><EK E1=\"1000.000000\" "
    "E2=\"1000.000000\" E3=\"1000.000000\" E4=\"1000.000000\" E5=\"1000.000000\" "
    "E6=\"1000.000000\"/><IPOC>543265442</IPOC></Sen>";

  EXPECT_STREQ(control_signal.CreateXMLString(543265442, true).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestInvalidJointConfigOrder)
{
  auto joint_config = GetJointConfig(0, kFixSixAxes);
  auto ext_config = GetJointConfig(kFixSixAxes, 0);
  joint_config.insert(joint_config.end(), ext_config.begin(), ext_config.end());

  EXPECT_THROW(
    kuka::external::control::kss::ControlSignal(kFixSixAxes * 2, {}, joint_config),
    std::invalid_argument);
}

TEST_F(KSSControlSignal, TestCustomElementNames)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.joint_xml_element = "JointCmd";

  ControlSignal control_signal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg);

  std::vector<double> values = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  control_signal.AddJointPositionValues(values.begin(), values.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><JointCmd A1=\"0.000000\" A2=\"0.000000\" "
    "A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" A6=\"0.000000\"/><IPOC>7</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(7).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestCustomAttributeNames)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.joint_xml_attributes = {"j1", "j2", "j3", "j4", "j5", "j6"};

  ControlSignal control_signal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg);

  std::vector<double> values = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  control_signal.AddJointPositionValues(values.begin(), values.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop><AK j1=\"0.000000\" j2=\"0.000000\" "
    "j3=\"0.000000\" j4=\"0.000000\" j5=\"0.000000\" j6=\"0.000000\"/><IPOC>1</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(1).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestCustomFieldOrderRejectsLegacyIpocEntry)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.field_order = {
    {ControlSignalXmlFieldType::POSITION, 0},
    {ControlSignalXmlFieldType::IPOC, 0},
  };

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}

TEST_F(KSSControlSignal, TestCustomConfigWithExternalAxes)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.joint_xml_element = "IntAxes";
  xml_cfg.joint_xml_attributes = {"q1", "q2", "q3", "q4", "q5", "q6"};
  xml_cfg.ext_joint_xml_element = "ExtAxes";
  xml_cfg.ext_joint_xml_attributes = {"e1", "e2"};

  ControlSignal control_signal(kFixSixAxes + 2, {}, GetJointConfig(2, kFixSixAxes), xml_cfg);

  std::vector<double> values(8, 0.0);
  control_signal.AddJointPositionValues(values.begin(), values.end());

  const char * expected_xml =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<IntAxes q1=\"0.000000\" q2=\"0.000000\" q3=\"0.000000\" q4=\"0.000000\" "
    "q5=\"0.000000\" q6=\"0.000000\"/>"
    "<ExtAxes e1=\"0.000000\" e2=\"0.000000\"/>"
    "<IPOC>0</IPOC></Sen>";
  EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestGpioSerialization)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  xml_cfg.include_velocity_values = true;

  std::vector<double> positions(kFixSixAxes, 0.0);
  std::vector<double> velocities(kFixSixAxes, 0.0);
  std::vector<double> torques = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  std::vector<kuka::external::control::kss::GPIOConfiguration> gpio_configs = {
    {"b_out", kuka::external::control::GPIOValueType::BOOL},
    {"analog_out", kuka::external::control::GPIOValueType::DOUBLE},
    {"count_out", kuka::external::control::GPIOValueType::LONG},
  };
  ControlSignal control_signal_with_gpio(
    kFixSixAxes, gpio_configs, GetJointConfig(0, kFixSixAxes), xml_cfg);
  std::vector<double> gpio_values = {1.0, 12.5, 42.0};
  control_signal_with_gpio.AddJointPositionValues(positions.begin(), positions.end());
  control_signal_with_gpio.AddVelocityValues(velocities.begin(), velocities.end());
  control_signal_with_gpio.AddTorqueValues(torques.begin(), torques.end());
  EXPECT_TRUE(control_signal_with_gpio.AddGPIOValues(gpio_values.begin(), gpio_values.end()));

  const char * expected_xml_with_gpio =
    "<Sen Type=\"KROSHU\"><Stop>0</Stop>"
    "<AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<VK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" "
    "A6=\"0.000000\"/>"
    "<TK A1=\"1.000000\" A2=\"2.000000\" A3=\"3.000000\" A4=\"4.000000\" A5=\"5.000000\" "
    "A6=\"6.000000\"/>"
    "<GPIO b_out=\"1\" analog_out=\"12.500000\" count_out=\"42\"/>"
    "<IPOC>21</IPOC></Sen>";
  EXPECT_STREQ(control_signal_with_gpio.CreateXMLString(21).value().data(), expected_xml_with_gpio);
}

TEST_F(KSSControlSignal, TestLargeNumericValuesAreSerializedCompletely)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  xml_cfg.include_velocity_values = true;

  std::vector<kuka::external::control::kss::GPIOConfiguration> gpio_configs = {
    {"analog_out", kuka::external::control::GPIOValueType::DOUBLE},
    {"count_out", kuka::external::control::GPIOValueType::LONG},
  };
  ControlSignal control_signal(1, gpio_configs, GetJointConfig(0, 1), xml_cfg);

  constexpr int kPrecision = 6;
  constexpr double kLargeValue = 12345.6789;
  std::vector<double> positions = {kLargeValue};
  std::vector<double> velocities = {kLargeValue};
  std::vector<double> torques = {kLargeValue};
  std::vector<double> gpio_values = {kLargeValue, 123456.0};

  control_signal.AddJointPositionValues(positions.begin(), positions.end());
  control_signal.AddVelocityValues(velocities.begin(), velocities.end());
  control_signal.AddTorqueValues(torques.begin(), torques.end());
  ASSERT_TRUE(control_signal.AddGPIOValues(gpio_values.begin(), gpio_values.end()));

  auto xml = control_signal.CreateXMLString(77);
  ASSERT_TRUE(xml.has_value());

  std::array<char, 512> position_buf;
  const int position_len = std::snprintf(
    position_buf.data(), position_buf.size(), "%.*f", kPrecision, kLargeValue * 180.0 / M_PI);
  ASSERT_GT(position_len, 0);
  ASSERT_LT(position_len, static_cast<int>(position_buf.size()));

  std::array<char, 512> torque_buf;
  const int torque_len =
    std::snprintf(torque_buf.data(), torque_buf.size(), "%.*f", kPrecision, kLargeValue);
  ASSERT_GT(torque_len, 0);
  ASSERT_LT(torque_len, static_cast<int>(torque_buf.size()));

  std::string serialized(xml.value());
  EXPECT_NE(
    serialized.find(std::string("<AK A1=\"") + position_buf.data() + "\"/>"), std::string::npos);
  EXPECT_NE(
    serialized.find(std::string("<VK A1=\"") + position_buf.data() + "\"/>"), std::string::npos);
  EXPECT_NE(
    serialized.find(std::string("<TK A1=\"") + torque_buf.data() + "\"/>"), std::string::npos);
  EXPECT_NE(
    serialized.find("<GPIO analog_out=\"12345.678900\" count_out=\"123456\"/>"), std::string::npos);
}

TEST_F(KSSControlSignal, TestCreateXmlReturnsNulloptOnBufferOverflow)
{
  std::vector<kuka::external::control::kss::GPIOConfiguration> gpio_configs;
  gpio_configs.reserve(120);
  for (std::size_t i = 0; i < 120; ++i)
  {
    gpio_configs.push_back(
      {"gpio_" + std::to_string(i), kuka::external::control::GPIOValueType::BOOL});
  }

  ControlSignal control_signal(1, gpio_configs, GetJointConfig(0, 1));

  std::vector<double> positions = {0.0};
  control_signal.AddJointPositionValues(positions.begin(), positions.end());

  std::vector<double> gpio_values(120, 1.0);
  ASSERT_TRUE(control_signal.AddGPIOValues(gpio_values.begin(), gpio_values.end()));

  EXPECT_FALSE(control_signal.CreateXMLString(42).has_value());
}

TEST_F(KSSControlSignal, TestInvalidConfigMissingJoint)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.field_order = {
    {ControlSignalXmlFieldType::GPIO, 0},
  };

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}

TEST_F(KSSControlSignal, TestInvalidConfigExtJointWithoutExternalAxes)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.field_order = {
    {ControlSignalXmlFieldType::POSITION, 0},
    {ControlSignalXmlFieldType::EXT_POSITION, 0},
  };

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}

TEST_F(KSSControlSignal, TestInvalidConfigDuplicateField)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.field_order = {
    {ControlSignalXmlFieldType::POSITION, 0},
    {ControlSignalXmlFieldType::POSITION, 0},
  };

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}

TEST_F(KSSControlSignal, TestInvalidConfigExternalTorqueFieldWhenNotEnabled)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.include_torque_values = true;
  xml_cfg.field_order = {
    {ControlSignalXmlFieldType::POSITION, 0},
    {ControlSignalXmlFieldType::EXT_POSITION, 0},
    {ControlSignalXmlFieldType::TORQUE, 0},
    {ControlSignalXmlFieldType::EXT_TORQUE, 0},
  };

  EXPECT_THROW(
    ControlSignal(kFixSixAxes + 1, {}, GetJointConfig(1, kFixSixAxes), xml_cfg),
    std::invalid_argument);
}

TEST_F(KSSControlSignal, TestInvalidConfigWrongAttributeCount)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.joint_xml_attributes = {"a1", "a2"};  // only 2 but 6 internal axes

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}

TEST_F(KSSControlSignal, TestInvalidConfigEmptyElementName)
{
  ControlSignalXmlConfiguration xml_cfg;
  xml_cfg.joint_xml_element = "";

  EXPECT_THROW(
    ControlSignal(kFixSixAxes, {}, GetJointConfig(0, kFixSixAxes), xml_cfg), std::invalid_argument);
}
