#include <memory>
#include <vector>

#include "event-handlers/control_event_handler.hpp"
#include "event-handlers/mxa_event_handler.hpp"
#include "kuka/external-control-sdk/kss/mxa/robot_interface.h"

using external_control_sdk_example::ControlEventHandler;
using external_control_sdk_example::EventHandlerExtension;
using external_control_sdk_example::StatusUpdateHandler;
using kuka::external::control::ControlMode;
using kuka::external::control::ReturnCode;
using kuka::external::control::Status;
using kuka::external::control::kss::Configuration;
using kuka::external::control::kss::CycleTime;
using kuka::external::control::kss::mxa::Robot;

int main() {
  // Specify the IP address of the KLI interface and create a robot interface
  // instance
  Configuration config{.kli_ip_address = "192.168.38.8",
                       .mxa_client_port = 1337};
  Robot rob_if{config};

  // Holds status response from robot interface operations
  Status ret;

  // Register common event handler
  auto control_event_handler = std::make_unique<ControlEventHandler>();
  ret = rob_if.RegisterEventHandler(std::move(control_event_handler));
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to register event handler: " << ret.message
              << std::endl;
    return -1;
  }

  // Register event handler extension
  auto event_handler_extension = std::make_unique<EventHandlerExtension>();
  ret =
      rob_if.RegisterEventHandlerExtension(std::move(event_handler_extension));
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to register event handler extension: " << ret.message
              << std::endl;
    return -1;
  }

  // Register status update handler
  auto status_update_handler = std::make_unique<StatusUpdateHandler>();
  ret = rob_if.RegisterStatusResponseHandler(std::move(status_update_handler));
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to register status update handler: " << ret.message
              << std::endl;
    return -1;
  }

  // Setup network connection
  ret = rob_if.Setup();
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to setup robot interface: " << ret.message
              << std::endl;
    return -1;
  }

  // Turn on drives
  ret = rob_if.TurnOnDrives();
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to turn on drives: " << ret.message << std::endl;
    return -1;
  }

  // Set cycle time to 4ms
  ret = rob_if.SetCycleTime(CycleTime::RSI_4MS);
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to set cycle time: " << ret.message << std::endl;
    return -1;
  }

  // Start controlling the robot in joint position control mode
  ret = rob_if.StartControlling(ControlMode::JOINT_POSITION_CONTROL);
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to start controlling: " << ret.message << std::endl;
    return -1;
  }

  // Wait for a while to receive the first motion state
  using namespace std::chrono_literals;
  ret = rob_if.ReceiveMotionState(10s);
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to receive motion state: " << ret.message << std::endl;
    return -1;
  }

  // Create vector to hold initial joint positions
  std::vector<double> positions =
      rob_if.GetLastMotionState().GetMeasuredPositions();

  // Send first control signal
  rob_if.GetControlSignal().AddJointPositionValues(positions.cbegin(),
                                                   positions.cend());
  ret = rob_if.SendControlSignal();
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to send control signal: " << ret.message << std::endl;
    return -1;
  }

  // Example movement
  const std::size_t iter_cnt = 1'000;
  for (std::size_t i = 0; i < iter_cnt; i++) {
    // Receive the motion state in each iteration
    ret = rob_if.ReceiveMotionState(40ms);
    if (ret.return_code != ReturnCode::OK) {
      std::cerr << "Failed to receive motion state: " << ret.message
                << std::endl;
      return -1;
    }

    // Set the target positions for the last joint
    if (i < iter_cnt / 2) {
      positions[5] += 0.1 / iter_cnt;
    } else {
      positions[5] -= 0.1 / iter_cnt;
    }

    // Send the control signal with updated positions
    rob_if.GetControlSignal().AddJointPositionValues(positions.cbegin(),
                                                     positions.cend());
    ret = rob_if.SendControlSignal();
    if (ret.return_code != ReturnCode::OK) {
      std::cerr << "Failed to send control signal: " << ret.message
                << std::endl;
      return -1;
    }
  }

  // Stop controlling the robot
  ret = rob_if.StopControlling();
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to stop controlling: " << ret.message << std::endl;
    return -1;
  }

  // Turn off drives
  ret = rob_if.TurnOffDrives();
  if (ret.return_code != ReturnCode::OK) {
    std::cerr << "Failed to turn off drives: " << ret.message << std::endl;
    return -1;
  }

  // Wait for a while to ensure all messages arrive
  std::this_thread::sleep_for(10s);

  return 0;
}
