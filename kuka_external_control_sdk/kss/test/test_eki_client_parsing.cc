// Copyright 2026 KUKA Hungaria Kft.
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

#include <cstring>
#include <string>

#define private public
#include "kuka/external-control-sdk/kss/eki/client.h"
#undef private
#include "kuka/external-control-sdk/kss/eki/initialization_data.h"

using kuka::external::control::ControlMode;
using kuka::external::control::OperationMode;
using kuka::external::control::kss::CycleTime;
using kuka::external::control::kss::eki::Client;
using kuka::external::control::kss::eki::EKIInitializationData;

TEST(EKIClientParsing, TruncatesOversizedEventMessage)
{
  Client client("127.0.0.1", 1);
  const std::string oversized_message(512, 'A');
  std::string xml =
    "<Robot><Response EventID=\"4\">" + oversized_message + "</Response></Robot>";

  ASSERT_TRUE(client.ParseMessage(xml.data()));
  EXPECT_EQ(client.event_response_.event_type, Client::EventType::ERROR);
  EXPECT_EQ(std::strlen(client.event_response_.message), sizeof(client.event_response_.message) - 1);
  EXPECT_EQ(std::string(client.event_response_.message), oversized_message.substr(0, 127));
}

TEST(EKIClientParsing, RejectsStatusWithOutOfRangeBoolAttribute)
{
  Client client("127.0.0.1", 1);
  std::string xml =
    "<Robot><Response EventID=\"12\"></Response>"
    "<Status ControlMode=\"1\" CycleTime=\"1\" DrivesPowered=\"2\" EmergencyStop=\"0\" "
    "GuardStop=\"0\" InMotion=\"0\" MotionPossible=\"1\" OperationMode=\"4\" "
    "RobotStopped=\"0\"/></Robot>";

  EXPECT_FALSE(client.ParseMessage(xml.data()));
}

TEST(EKIClientParsing, ParsesStatusWithoutWritingThroughReinterpretedPointers)
{
  Client client("127.0.0.1", 1);
  std::string xml =
    "<Robot><Response EventID=\"12\"></Response>"
    "<Status ControlMode=\"1\" CycleTime=\"2\" DrivesPowered=\"1\" EmergencyStop=\"0\" "
    "GuardStop=\"1\" InMotion=\"0\" MotionPossible=\"1\" OperationMode=\"4\" "
    "RobotStopped=\"0\"/></Robot>";

  ASSERT_TRUE(client.ParseMessage(xml.data()));
  EXPECT_EQ(client.event_response_.event_type, Client::EventType::STATUS);
  EXPECT_EQ(client.status_update_.control_mode_, ControlMode::JOINT_POSITION_CONTROL);
  EXPECT_EQ(client.status_update_.cycle_time_, CycleTime::RSI_12MS);
  EXPECT_TRUE(client.status_update_.drives_powered_);
  EXPECT_FALSE(client.status_update_.emergency_stop_);
  EXPECT_TRUE(client.status_update_.guard_stop_);
  EXPECT_FALSE(client.status_update_.in_motion_);
  EXPECT_TRUE(client.status_update_.motion_possible_);
  EXPECT_EQ(client.status_update_.operation_mode_, OperationMode::EXT);
  EXPECT_FALSE(client.status_update_.robot_stopped_);
}

TEST(EKIInitializationDataParsing, RejectsMissingAttributes)
{
  EKIInitializationData init_data;
  const char missing_rob_ver[] =
    "<Robot><Init VER=\"1.0.0\" NumAxes=\"6\" NumExternalAxes=\"0\" Model=\"KR\"/>"
    "</Robot>";

  EXPECT_FALSE(init_data.Parse(missing_rob_ver));
}

TEST(EKIInitializationDataParsing, RejectsOutOfRangeAxisCounts)
{
  EKIInitializationData init_data;
  const char too_many_axes[] =
    "<Robot><Init VER=\"1.0.0\" NumAxes=\"300\" NumExternalAxes=\"0\" Model=\"KR\" "
    "RobVer=\"HW/SW\"/></Robot>";

  EXPECT_FALSE(init_data.Parse(too_many_axes));
}
