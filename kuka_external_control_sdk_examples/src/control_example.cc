#include <cmath>

#include "event-handlers/control_event_handler.hpp"
#include "kuka/external-control-sdk/iiqka/sdk.h"

int main(int argc, char const *argv[]) {
  // Configure general setup - IP addresses
  kuka::external::control::iiqka::Configuration eci_config;
  eci_config.client_ip_address = "127.0.0.1";
  eci_config.koni_ip_address = "127.0.0.1";

  // Create interface
  auto rob_if = std::make_shared<kuka::external::control::iiqka::Robot>(eci_config);

  kuka::external::control::Status setup_ret;
  // Initiate connection
  bool use_secure_setup = false;
  if (use_secure_setup) {
    eci_config.is_secure = true;
    eci_config.certificate_path = "cert.pem";
    eci_config.private_key_path = "key.pem";
  }

  setup_ret = rob_if->Setup();

  // Set QoS configurations
  kuka::external::control::iiqka::QoS_Configuration default_qos_config;
  // Test with weaker qos
  default_qos_config.consecutive_packet_loss_limit = 5;
  default_qos_config.packet_loss_in_timeframe_limit = 10;
  default_qos_config.timeframe_ms = 1000;
  rob_if->SetQoSProfile(default_qos_config);

  if (setup_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Setting up network failed: " << setup_ret.message << std::endl;
    return -1;
  }

  // Set timeout
  bool use_blocking_receive = true;
  int timeout = use_blocking_receive ? 0 : 4;

  // Register custom event handler
  std::unique_ptr<external_control_sdk_example::ControlEventHandler> control_event_handler =
      std::make_unique<external_control_sdk_example::ControlEventHandler>();
  rob_if->RegisterEventHandler(std::move(control_event_handler));

  // Start controlling the robot
  auto start_control_ret =
      rob_if->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL);
  if (start_control_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Opening control channel failed: " << start_control_ret.message << std::endl;
    return 0;
  }

  // Init variables
  int counter = 0;
  // Degree of freedom
  size_t dof = 6;
  kuka::external::control::BaseMotionState actual_state(dof);
  std::vector<double> start_pos(dof, 0);
  std::vector<double> reply_pos(dof, 0);
  double sin_ipoc = 0;

  std::cout << "Start ctrl loop\n";
  while (counter < 10000) {
    // Receive actual robot state, exit if does not arrive in time
    auto recv_ret = rob_if->ReceiveMotionState(std::chrono::milliseconds(timeout));

    std::cout << "Recv req\n";
    if (recv_ret.return_code != kuka::external::control::ReturnCode::OK) {
      std::cerr << "Recv req failed with ret code: " << static_cast<int>(recv_ret.return_code)
                << " and message: " << recv_ret.message << std::endl;
      return -1;
    }

    // Create sine control signal
    actual_state = rob_if->GetLastMotionState();

    // Add sine to goal positions
    for (int i = 0; i < dof; ++i) {
      if (counter == 0) {
        start_pos[i] = actual_state.GetMeasuredPositions()[i];
      }
      reply_pos[i] = start_pos[i] + sin_ipoc;
    }
    // Axis 2 has a limit of +50 degrees, stop sinus for that axis
    if (reply_pos[1] > 0.85) {
      reply_pos[1] = 0.85;
    }

    sin_ipoc = -sin(counter * 0.0004);
    // Set values in control signal
    rob_if->GetControlSignal().AddJointPositionValues(reply_pos.begin(), reply_pos.end());
    std::cout << "Set values\n";

    // Set constant joint impedance attributes before switching to impedance mode
    if (counter == 5000) {
      auto stiffness = std::vector<double>(6, 100);
      auto damping = std::vector<double>(6, 0.7);
      rob_if->GetControlSignal().AddStiffnessAndDampingValues(stiffness.begin(), stiffness.end(),
                                                              damping.begin(), damping.end());
    }

    // Send control signal (or switch control mode in case of the 5000th message)
    auto send_ret = counter == 5000
                        ? rob_if->SwitchControlMode(
                              kuka::external::control::ControlMode::JOINT_IMPEDANCE_CONTROL)
                        : rob_if->SendControlSignal();
    std::cout << "Sent reply\n";
    if (send_ret.return_code != kuka::external::control::ReturnCode::OK) {
      std::cerr << "Send req failed with ret code: " << static_cast<int>(send_ret.return_code)
                << " and message: " << send_ret.message << std::endl;
      return -1;
    }

    counter++;
    std::cout << "Counter: " << counter << "\n";
  }

  // Last receive - needed to be able to send stop signal
  auto recv_ret = rob_if->ReceiveMotionState(std::chrono::milliseconds(timeout));
  std::cout << "Recv req before stop\n";
  if (recv_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Recv req before stop failed with ret code: "
              << static_cast<int>(recv_ret.return_code) << " and message: " << recv_ret.message
              << std::endl;
    return -1;
  }

  // Send stop
  std::cout << "Sent stop\n";
  auto send_ret = rob_if->StopControlling();
  if (send_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Send stop failed with ret code: " << static_cast<int>(send_ret.return_code)
              << " and message: " << send_ret.message << std::endl;
    return -1;
  }

  std::cout << "End ctrl loop\n";
  return 0;
}
