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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_
#define KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/common/status.h"
#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/eki/extension.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/tcp_client.h"

namespace kuka::external::control::kss::eki {

enum class CommandType : std::uint8_t {
  CONNECT = 0,
  START = 1,
  RESET = 2,
  CANCEL = 3,
  CHANGE = 4,
  CMD_NONE = 5,
  DRIVES_ON = 6,
  DRIVES_OFF = 7,
  CHANGE_CYCLE_TIME = 8,
};

class Client : public os::core::udp::communication::TCPClient {
 public:
  Client(const std::string& server_address, unsigned short server_port);
  virtual ~Client() override;

  // Initiates EKI connection
  Status Start();

  // Starts RSI program
  Status StartRSI(kuka::external::control::ControlMode control_mode);

  // Stops RSI program
  Status StopRSI();

  Status RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler);

  Status RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension);

  Status RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler>&& handler);

  // TODO implement functions to get certain data of the returned status
  // Specific to the needs of the application e.g. get error message

  Status TurnOnDrives();
  Status TurnOffDrives();
  Status SetCycleTime(CycleTime cycle_time);

 private:
  // Response structures
  enum EventType {
    STARTED = 0,
    STOPPED = 1,
    CANCELLED = 2,
    RESET_OK = 3,
    ERROR = 4,
    CONNECTED = 5,
    SWITCH_OK = 6,
    INVALID = 7,
    NONE = 8,
    DRIVES_TURNED_ON = 9,
    DRIVES_TURNED_OFF = 10,
    CYCLE_TIME_CHANGED = 11,
    STATUS = 12,
  };

  struct EventResponse {
    EventType event_type;
    char message[128];
  };

 private:
  // Send TCP message and wait for answer
  Status SendMessageAndWait();

  // Send EKI command with given request type
  Status SendCommand(const CommandType cmd_type);

  // Send EKI control mode change command with given control mode
  Status SendControlModeChange(kuka::external::control::ControlMode control_mode);

  // Send EKI cycle time change command with given cycle time
  Status SendCycleTimeChange(CycleTime cycle_time);

  // Start thread handling incoming events/status messages
  void StartReceiverThread();

  // Handle server event response
  void HandleEvent(const EventResponse& event);

  // Receives the EKI server response - with given timeout
  bool Receive(std::chrono::microseconds timeout);

  // Override dissect function of Dissector base class
  // Validates incoming packets (handles partial packets, too)
  int Dissect(char* cursor_ptr, std::size_t available_bytes) override;

 private:
  void TearDownConnection();
  bool IsCompatibleWithServer();
  bool ParseInitMessage(char* data_to_parse);
  bool ParseEvent(char* data_to_parse);
  bool ParseStatus(char* data_to_parse);
  bool ParseMessage(char* data_to_parse);

 private:
  static constexpr std::size_t kRecvBuffSize = 4096;
  static constexpr std::size_t kSendBuffSize = 4096;

  unsigned char recv_buff_[kRecvBuffSize];
  unsigned char send_buff_[kSendBuffSize];

  static constexpr char simple_req_format_[] = "<External REQTYPE=\"%d\"></External>";

  static constexpr char change_control_mode_req_format_[] =
      "<External REQTYPE=\"4\" ControlMode=\"%d\"></External>";

  static constexpr char change_cycle_time_req_format_[] =
      "<External REQTYPE=\"8\" CycleTime=\"%d\"></External>";

  static constexpr char event_resp_format_[] =
      "<Robot><Response EventID=\"%d\">%[^<]</Response></Robot>";

  static constexpr char status_report_format_[] =
      "<Robot><Status ControlMode=\"%hhu\" CycleTime=\"%hhu\" DrivesPowered=\"%hhu\" "
      "EmergencyStop=\"%hhu\" GuardStop=\"%hhu\" InMotion=\"%hhu\" "
      "MotionPossible=\"%hhu\" OperationMode=\"%hhu\" RobotStopped=\"%hhu\"></Status></Robot>";
  static constexpr uint8_t kStatusReportFieldCount = 9;

  static constexpr char kSemanticVersion[] = "1.0.0";

  InitializationData init_data_;
  EventResponse event_response_;
  StatusUpdate status_update_;

  std::thread receiver_thread_;
  std::condition_variable req_response_cv_;
  std::mutex req_response_cv_mutex_;
  std::atomic<bool> request_active_{false};

  bool is_last_event_status_ = false;
  bool rsi_running_ = false;

  // Event handling
  std::mutex event_handler_mutex_;
  std::unique_ptr<EventHandler> event_handler_;
  std::unique_ptr<IEventHandlerExtension> event_handler_extension_;
  std::unique_ptr<IStatusUpdateHandler> status_update_handler_;
  bool event_handler_set_ = false;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_
