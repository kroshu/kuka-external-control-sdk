// Copyright 2025 KUKA Hungaria Kft.
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

#include <array>
#include <iostream>
#include <memory>
#include <thread>

#include "event-handlers/control_event_handler.hpp"
#include "event-handlers/eki_event_handler.hpp"
#include "kuka/external-control-sdk/kss/eki/robot_interface.h"

using external_control_sdk_example::ControlEventHandler;
using external_control_sdk_example::EventHandlerExtension;
using external_control_sdk_example::StatusUpdateHandler;
using kuka::external::control::ControlMode;
using kuka::external::control::ReturnCode;
using kuka::external::control::Status;
using kuka::external::control::kss::Configuration;
using kuka::external::control::kss::CycleTime;
using kuka::external::control::kss::eki::Robot;

void ControlRobot(Robot & robot, std::size_t robot_index);

int main()
{
  std::cout << "Starting control of 2 robots..." << std::endl;

  // Create two robot interface instances with different configurations
  std::array<Robot, 2> robots{
    Robot(Configuration{.kli_ip_address = "172.31.1.147", .client_port = 59152}),
    Robot(Configuration{.kli_ip_address = "172.33.1.147", .client_port = 59153})};

  // Create threads for each robot
  std::cout << "Creating control threads..." << std::endl;
  std::array<std::thread, 2> robot_threads{
    std::thread(ControlRobot, std::ref(robots[0]), 0),
    std::thread(ControlRobot, std::ref(robots[1]), 1)};

  // Wait for all threads to complete
  std::cout << "Threads created, waiting for completion..." << std::endl;
  for (auto & thread : robot_threads)
  {
    thread.join();
  }

  std::cout << "All robot control threads completed successfully!" << std::endl;
}

void ControlRobot(Robot & robot, std::size_t robot_index)
{
  using namespace std::chrono_literals;

  robot.RegisterEventHandler(std::make_unique<ControlEventHandler>());
  robot.RegisterEventHandlerExtension(std::make_unique<EventHandlerExtension>());
  robot.RegisterStatusResponseHandler(std::make_unique<StatusUpdateHandler>());
  robot.Setup();
  robot.TurnOnDrives();

  robot.StartControlling(ControlMode::JOINT_POSITION_CONTROL);
  robot.ReceiveMotionState(10s);
  auto positions = robot.GetLastMotionState().GetMeasuredPositions();

  robot.GetControlSignal().AddJointPositionValues(positions.cbegin(), positions.cend());
  robot.SendControlSignal();

  constexpr std::size_t iter_cnt = 1'000;
  std::size_t joint_index = robot_index % 2 == 0 ? 5 : 4;
  for (std::size_t j = 0; j < iter_cnt; ++j)
  {
    robot.ReceiveMotionState(40ms);

    // Update the last joint position
    if (j < iter_cnt / 2)
    {
      positions[joint_index] += 0.1 / iter_cnt;
    }
    else
    {
      positions[joint_index] -= 0.1 / iter_cnt;
    }

    robot.GetControlSignal().AddJointPositionValues(positions.cbegin(), positions.cend());
    robot.SendControlSignal();
  }

  robot.StopControlling();
  robot.TurnOffDrives();
}
