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
#include <cstring>

#include <tinyxml2.h>

#include "kuka/external-control-sdk/kss/eki/client.h"
#include "kuka/external-control-sdk/kss/rsi/robot_interface.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"


namespace kuka::external::control::kss::eki {

Client::Client(const std::string& server_address, unsigned short server_port)
    : os::core::udp::communication::TCPClient(
          kRecvBuffSize, os::core::udp::communication::SocketAddress(server_address, server_port)) {
  event_handler_ = std::make_unique<EventHandler>();
}

Client::~Client() {
  TearDownConnection();

  if (receiver_thread_.joinable()) {
    receiver_thread_.join();
  }
}

Status Client::Start() {
  StartReceiverThread();
  auto connect_status = SendCommand(CommandType::CONNECT);
  return connect_status.return_code == ReturnCode::OK
             ? (event_handler_set_
                    ? Status(ReturnCode::OK, "EKI communication started")
                    : Status(ReturnCode::WARN,
                             "EKI communication started but default event handler used"))
             : connect_status;
}

Status Client::StartRSI(kuka::external::control::ControlMode control_mode) {
  auto ctrl_change_resp = SendControlModeChange(control_mode);
  if (ctrl_change_resp.return_code != ReturnCode::OK) {
    return ctrl_change_resp;
  }

  auto start_resp = SendCommand(CommandType::START);
  if (start_resp.return_code != ReturnCode::OK) {
    return start_resp;
  }
  rsi_running_ = true;
  return {ReturnCode::OK, "RSI started"};
}

Status Client::StopRSI() {
  if (rsi_running_) {
    auto cancel_resp = SendCommand(CommandType::CANCEL);
    if (cancel_resp.return_code != ReturnCode::OK) {
      return cancel_resp;
    }
    rsi_running_ = false;
    return {ReturnCode::OK, "RSI stopped"};
  }
  return {ReturnCode::WARN, "RSI already stopped"};
}

Status Client::SendMessageAndWait() {
  if (!TCPClient::Send(send_buff_, kSendBuffSize)) {
    return {ReturnCode::ERROR, "Sending message failed"};
  }

  // Mark an active request - wait for it to be reset to inactive
  // By the receiver thread after getting a response
  request_active_ = true;
  std::unique_lock<std::mutex> recv_lk(req_response_cv_mutex_);
  bool req_success = req_response_cv_.wait_for(recv_lk, std::chrono::seconds(4),
                                               [this] { return !request_active_; });
  return req_success ? Status(ReturnCode::OK, "Request sent and response arrived")
                     : Status(ReturnCode::TIMEOUT, "Request sent but response timeouted");
}

Status Client::SendCommand(const CommandType cmd_type) {
  sprintf(reinterpret_cast<char*>(send_buff_), general_req_format, static_cast<int>(cmd_type), 0, 0);
  return SendMessageAndWait();
}

Status Client::SendControlModeChange(kuka::external::control::ControlMode control_mode) {
  sprintf(reinterpret_cast<char*>(send_buff_), general_req_format, 4, 0, static_cast<int>(control_mode));
  return SendMessageAndWait();
}

Status Client::SendCycleTimeChange(CycleTime cycle_time) {
  int cycle_time_int = static_cast<int>(cycle_time);
  sprintf(reinterpret_cast<char*>(send_buff_), general_req_format, 8, cycle_time_int, 0);
  return SendMessageAndWait();
}

void Client::StartReceiverThread() {
  receiver_thread_ = std::thread([this] {
    while (true) {
      if (!Receive(std::chrono::microseconds(-1))) {
        return;
      }
      HandleEvent(event_response_);
      if (is_last_event_status_) {
        is_last_event_status_ = false;
        continue;
      }
      // Only signal event as request response if a request was issued
      if (request_active_) {
        request_active_ = false;
        req_response_cv_.notify_one();
      }
    }
  });
}

void Client::HandleEvent(const EventResponse& event) {
  std::lock_guard<std::mutex> lck(event_handler_mutex_);
  switch (event.event_type) {
    case EventType::STARTED:
      event_handler_->OnSampling();
      return;
    case EventType::STOPPED:
      event_handler_->OnStopped("RSI program stopped");
      return;
    case EventType::CANCELLED:
      event_handler_->OnStopped("RSI program cancelled");
      return;
    case EventType::ERROR:
      event_handler_->OnError(event.message);
      return;
    case EventType::SWITCH_OK:
      event_handler_->OnControlModeSwitch(event.message);
      return;
    case EventType::CONNECTED:
      if (event_handler_extension_ != nullptr) {
        event_handler_extension_->OnConnected(init_data_);
      }
      return;
    case EventType::STATUS:
      is_last_event_status_ = true;
      if (status_update_handler_ != nullptr) {
        status_update_handler_->OnStatusUpdateReceived(status_update_);
      }
      return;
    default:
      return;
  }
}

bool Client::Receive(std::chrono::microseconds timeout) {
  return TCPClient::Receive(recv_buff_, timeout);
}

int Client::Dissect(char* cursor_ptr, std::size_t available_bytes) {
  // TODO somehow propagate error causes in the different cases

  // Check opening tag (might be unnecessary) - return with failed if not found
  const char* opening_tag = "<Robot>";
  if (std::memcmp(cursor_ptr, opening_tag, strlen(opening_tag) != 0)) {
    return -1;
  }

  // Check whether closing tag is there - if not it's still a partial message
  const char* closing_tag = "</Robot>";
  char* start_ptr = cursor_ptr + available_bytes - strlen(closing_tag);
  if (std::memcmp(start_ptr, closing_tag, strlen(closing_tag) != 0)) {
    return available_bytes + 1;
  }

  // Parse event or status response with format string
  if (ParseMessage(cursor_ptr)) {
    return available_bytes;
  }

  // Return with error if parsing failed
  return -1;
}

void Client::TearDownConnection() {
  StopRSI();

  // Shutting down socket to interrupt blocking receive
  // In receiver thread
  socket_->Shutdown();
}

std::array<uint8_t, 3> ExtractNumbers(const std::string& version) {
  std::array<uint8_t, 3> numbers = {0, 0, 0};
  size_t start = 0, end = 0, index = 0;

  while ((end = version.find('.', start)) != std::string::npos) {
    numbers[index++] = static_cast<uint8_t>(std::stoi(version.substr(start, end - start)));
    start = end + 1;
  }

  return numbers;
}

bool Client::IsCompatibleWithServer() {
  const auto server_ver = ExtractNumbers(init_data_.semantic_version);
  const auto client_ver = ExtractNumbers(kSemanticVersion);
  return server_ver[0] == client_ver[0];
}

bool Client::ParseInitMessage(char* data_to_parse) {
  const bool parsed = init_data_.Parse(data_to_parse);
  if (parsed) {
    if (!IsCompatibleWithServer()) {
      TearDownConnection();
      event_response_.event_type = EventType::ERROR;
      sprintf(
        event_response_.message,
        "The server (%s) and client (%s) versions are not compatible",
        init_data_.semantic_version.c_str(),
        kSemanticVersion
      );
    }
  }
  return parsed;
}

bool Client::ParseEvent(char* data_to_parse) {
  // Reset event fields
  event_response_.event_type = EventType::NONE;
  event_response_.message[0] = '\0';

  const char *response_tag = std::strstr(data_to_parse, "<Response");
  if (!response_tag) return false;
  // Parse event message
  int eid = -1;
  int ret = std::sscanf(response_tag, event_resp_format_, &eid,
                        event_response_.message);
  event_response_.event_type = static_cast<EventType>(eid);
  if (ret <= 0) return false;
  if (ret != 2) {
    // Not all event fields scanned, might add a warning somehow later on
  }
  return true;
}

bool Client::ParseStatus(char* data_to_parse) {
  event_response_.event_type = EventType::STATUS;

  // Reset status fields
  status_update_.Reset();

  const char *status_tag = std::strstr(data_to_parse, "<Status");
  if (!status_tag) return false;

  // Parse status message
  int ret = std::sscanf(status_tag, status_report_format_,
    reinterpret_cast<uint8_t*>(&status_update_.control_mode_),
    reinterpret_cast<uint8_t*>(&status_update_.cycle_time_),
    reinterpret_cast<uint8_t*>(&status_update_.drives_powered_),
    reinterpret_cast<uint8_t*>(&status_update_.emergency_stop_),
    reinterpret_cast<uint8_t*>(&status_update_.guard_stop_),
    reinterpret_cast<uint8_t*>(&status_update_.in_motion_),
    reinterpret_cast<uint8_t*>(&status_update_.motion_possible_),
    reinterpret_cast<uint8_t*>(&status_update_.operation_mode_),
    reinterpret_cast<uint8_t*>(&status_update_.robot_stopped_));

  return ret == kStatusReportFieldCount; // Ensure all fields are read
}

bool Client::ParseMessage(char* data_to_parse) {
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLError error = doc.Parse(data_to_parse);
  if (error != tinyxml2::XMLError::XML_SUCCESS) {
    return false;
  }

  // From EKI 6.1 upwards, every xml tag is sent in every message
  // In this case we can decide evet type based on EventID

  tinyxml2::XMLElement* root = doc.RootElement();
  tinyxml2::XMLElement* response = root->FirstChildElement("Response");

  if (response != nullptr) {
    int event_id = 0;
    error = response->QueryIntAttribute("EventID", &event_id);
    if (error == tinyxml2::XML_SUCCESS)
    {
      switch (static_cast<EventType>(event_id))
      {
      case EventType::CONNECTED:
          event_response_.event_type = EventType::CONNECTED;
          return ParseInitMessage(data_to_parse);
        break;
      case EventType::STATUS:
          event_response_.event_type = EventType::STATUS;
          return ParseStatus(data_to_parse);
        break;
      default:
        // If not first connection or status update, response is an event
        // But it is possible that an event and status update is received with the same message, 
        //  therefore status is also parsed
        ParseStatus(data_to_parse);
        return ParseEvent(data_to_parse);
        break;
      }
      
      event_response_.event_type = EventType::CONNECTED;
      return ParseInitMessage(data_to_parse);
    }
    // Response should alwasy contain EventID
    else return false;
  }

  if (root->FirstChildElement("Init") != nullptr) {
    event_response_.event_type = EventType::CONNECTED;
    return ParseInitMessage(data_to_parse);
  }

  if (root->FirstChildElement("Status") != nullptr) {
    event_response_.event_type = EventType::STATUS;
    return ParseStatus(data_to_parse);
  }

  return false;
}

Status Client::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  if (event_handler == nullptr) {
    return Status(ReturnCode::ERROR,
                  "RegisterEventHandler failed: please provide a valid pointer.");
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return Status(ReturnCode::OK);
};

Status Client::RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) {
  if (extension == nullptr) {
    return {ReturnCode::ERROR, "RegisterEventHandlerExtension failed: please provide a valid pointer"};
  }

  event_handler_extension_ = std::move(extension);
  return Status(ReturnCode::OK);
}

Status Client::RegisterStatusResponseHandler(std::unique_ptr<IStatusUpdateHandler>&& handler) {
  if (handler == nullptr) {
    return {ReturnCode::ERROR, "RegisterStatusResponseHandler failed: please provide a valid pointer"};
  }

  status_update_handler_ = std::move(handler);
  return ReturnCode::OK;
}

Status Client::TurnOnDrives() {
  return SendCommand(CommandType::DRIVES_ON);
}

Status Client::TurnOffDrives() {
  return SendCommand(CommandType::DRIVES_OFF);
}

Status Client::SetCycleTime(CycleTime cycle_time) {
  return SendCycleTimeChange(cycle_time);
}

}  // namespace kuka::external::control::kss
