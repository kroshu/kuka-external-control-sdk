#include "kuka/external-control-sdk/iiqka/robot.h"

int main(int argc, char const *argv[]) {
  // Configure general setup - IP addresses
  kuka::external::control::iiqka::Configuration eci_config;
  eci_config.client_ip_address = "127.0.0.1";
  eci_config.koni_ip_address = "127.0.0.1";

  // Create interface
  auto rob_if = std::make_shared<kuka::external::control::iiqka::Robot>(eci_config);

  // Set QoS configurations
  kuka::external::control::iiqka::QoS_Configuration default_qos_config;
  // Test with weaker qos
  default_qos_config.consecutive_packet_loss_limit = 10;
  rob_if->SetQoSProfile(default_qos_config);

  // Initiate connection
  auto setup_ret = rob_if->Setup();
  if (setup_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Setting up network failed: " << setup_ret.message << std::endl;
    return -1;
  }

  // Start monitoring the robot state
  auto start_mon_ret = rob_if->StartMonitoring();
  if (start_mon_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Starting monitoring failed: " << start_mon_ret.message << std::endl;
  }

  setup_ret = rob_if->CreateMonitoringSubscription(
      [](kuka::external::control::BaseMotionState motion_state) {
        printf(
            "Received motion state - A1: %f A2: %f A3: %f A4: %f A5: %f A6: %f\n",
            motion_state.GetMeasuredPositions()->at(0), motion_state.GetMeasuredPositions()->at(1),
            motion_state.GetMeasuredPositions()->at(2), motion_state.GetMeasuredPositions()->at(3),
            motion_state.GetMeasuredPositions()->at(4), motion_state.GetMeasuredPositions()->at(5));
      });
  if (setup_ret.return_code == kuka::external::control::ReturnCode::ERROR) {
    std::cerr << "Subscription failed: " << setup_ret.message << std::endl;
    return -1;
  }

  // Wait 10 seconds and stop monitoring afterwards
  std::this_thread::sleep_for(std::chrono::seconds(10));
  auto stop_mon_ret = rob_if->StopMonitoring();
  if (stop_mon_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Stopping monitoring failed: " << stop_mon_ret.message << std::endl;
    return -1;
  }

  std::cout << "Monitoring stopped, unsubscribing soon" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  stop_mon_ret = rob_if->CancelMonitoringSubscription();
  if (stop_mon_ret.return_code != kuka::external::control::ReturnCode::OK) {
    std::cerr << "Unsubscribe monitoring failed: " << stop_mon_ret.message << std::endl;
    return -1;
  }

  return 0;
}
