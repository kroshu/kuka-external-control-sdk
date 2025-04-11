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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_
#define KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/tcp_client.h"

namespace kuka::external::control::kss::eki {

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

  // TODO implement functions to get certain data of the returned status
  // Specific to the needs of the application e.g. get error message

 private:
  // Response structures
  enum EventType {
    STARTED,
    STOPPED,
    CANCELLED,
    RESET_OK,
    ERROR,
    CONNECTED,
    SWITCH_OK,
    INVALID,
    NONE
  };

  struct EventResponse {
    EventType event_type;
    char message[128];
  };

  struct StatusResponse {
    int mode;  // TODO use enum
    kuka::external::control::ControlMode control_mode;
    bool e_stop;
    int error_code;
  };

 private:
  // Send TCP message and wait for answer
  Status SendMessageAndWait();

  // Send EKI command with given request type
  Status SendCommand(const std::string& req_type, int id = 0);

  // Send EKI control mode change command with given control mode
  Status SendControlModeChange(kuka::external::control::ControlMode control_mode, int id = 0);

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
  bool ParseEvent(char* data_to_parse);
  bool ParseStatus(char* data_to_parse);

 private:
  static constexpr std::size_t kRecvBuffSize = 4096;
  static constexpr std::size_t kSendBuffSize = 4096;

  unsigned char recv_buff_[kRecvBuffSize];
  unsigned char send_buff_[kSendBuffSize];

  static constexpr char simple_req_format_[] = "<External REQTYPE=\"%s\" ID=\"%d\"></External>";
  static constexpr char change_control_mode_req_format_[] =
      "<External REQTYPE=\"CHANGE\" ID=\"%d\" ControlMode=\"%d\"></External>";

  static constexpr char event_resp_format_[] =
      "<Robot><Event EventID=\"%d\" Message=\"%[^\"]\"></Event></Robot>";
  static constexpr char status_resp_format_[] =
      "<Robot><Status Mode=\"%d\" ControlMode=\"%d\" EStop=\"%d\" "
      "ErrorCode=\"%d\"></Status></Robot>";

  EventResponse event_response_;
  StatusResponse status_response_;

  std::thread receiver_thread_;
  std::condition_variable req_response_cv_;
  std::mutex req_response_cv_mutex_;
  std::atomic<bool> request_active_{false};

  bool rsi_running_ = false;

  // Event handling
  std::mutex event_handler_mutex_;
  std::unique_ptr<EventHandler> event_handler_;
  bool event_handler_set_ = false;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_EKI_COMM_CLIENT_H_
