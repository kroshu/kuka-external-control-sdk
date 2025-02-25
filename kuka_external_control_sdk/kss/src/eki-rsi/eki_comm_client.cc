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

#include "kuka/external-control-sdk/kss/eki-rsi/eki_comm_client.h"

#include <cstdio>
#include <cstring>
#include <iostream>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace kuka::external::control::kss {

EKICommClient::EKICommClient(const std::string& server_address, unsigned short server_port)
    : os::core::udp::communication::TCPClient(
          kRecvBuffSize, os::core::udp::communication::SocketAddress(server_address, server_port)) {
  event_handler_ = std::make_unique<EventHandler>();
}

EKICommClient::~EKICommClient() {
  StopRSI();
  // Shutting down socket to interrupt blocking receive
  // In receiver thread
  socket_->Shutdown();
  if (receiver_thread_.joinable()) {
    receiver_thread_.join();
  }
}

Status EKICommClient::Start() {
  StartReceiverThread();
  auto connect_status = SendCommand("CON");
  return connect_status.return_code == ReturnCode::OK
             ? (event_handler_set_
                    ? Status(ReturnCode::OK, "EKI communication started")
                    : Status(ReturnCode::WARN,
                             "EKI communication started but default event handler used"))
             : connect_status;
}

Status EKICommClient::StartRSI(kuka::external::control::ControlMode control_mode) {
  auto ctrl_change_resp = SendControlModeChange(control_mode);
  if (ctrl_change_resp.return_code != ReturnCode::OK) {
    return ctrl_change_resp;
  }

  auto start_resp = SendCommand("START");
  if (start_resp.return_code != ReturnCode::OK) {
    return start_resp;
  }
  rsi_running_ = true;
  return {ReturnCode::OK, "RSI started"};
}

Status EKICommClient::StopRSI() {
  if (rsi_running_) {
    auto cancel_resp = SendCommand("CANCEL");
    if (cancel_resp.return_code != ReturnCode::OK) {
      return cancel_resp;
    }
    rsi_running_ = false;
    return {ReturnCode::OK, "RSI stopped"};
  }
  return {ReturnCode::WARN, "RSI already stopped"};
}

Status EKICommClient::SendMessageAndWait() {
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

Status EKICommClient::SendCommand(const std::string& req_type, int id) {
  sprintf(reinterpret_cast<char*>(send_buff_), simple_req_format_, req_type.data(), id);
  return SendMessageAndWait();
}

Status EKICommClient::SendControlModeChange(kuka::external::control::ControlMode control_mode,
                                            int id) {
  sprintf(reinterpret_cast<char*>(send_buff_), change_control_mode_req_format_, id, control_mode);
  return SendMessageAndWait();
}

void EKICommClient::StartReceiverThread() {
  receiver_thread_ = std::thread([this] {
    while (true) {
      if (!Receive(std::chrono::microseconds(-1))) {
        return;
      }
      HandleEvent(event_response_);
      // Only signal event as request response if a request was issued
      if (request_active_) {
        {
          std::lock_guard<std::mutex> recv_lk(req_response_cv_mutex_);
          request_active_ = false;
        }
        req_response_cv_.notify_one();
      }
    }
  });
}

void EKICommClient::HandleEvent(const EventResponse& event) {
  std::lock_guard<std::mutex> lck(event_handler_mutex_);
  switch (event.event_type) {
    case EventType::STARTED:
      event_handler_->OnSampling();
      return;
    case EventType::SWITCH_OK:
      event_handler_->OnControlModeSwitch(event.message);
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

    default:
      return;
  }
}

bool EKICommClient::Receive(std::chrono::microseconds timeout) {
  return TCPClient::Receive(recv_buff_, timeout);
}

int EKICommClient::Dissect(char* cursor_ptr, std::size_t available_bytes) {
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

  // Parse event or status response with format string - return with error if failed
  if (ParseEvent(cursor_ptr) || ParseStatus(cursor_ptr)) {
    return available_bytes;
  } else {
    return -1;
  }
}

bool EKICommClient::ParseEvent(char* data_to_parse) {
  // Reset event fields
  event_response_.event_type = EventType::NONE;
  strcpy(event_response_.message, "");

  // Parse event message
  int ret = std::sscanf(data_to_parse, event_resp_format_, &event_response_.event_type,
                        event_response_.message);
  if (ret <= 0) return false;
  if (ret != 2) {
    // Not all event fields scanned, might add a warning somehow later on
  }
  return true;
}

bool EKICommClient::ParseStatus(char* data_to_parse) {
  // Reset status fields
  status_response_.mode = -1;
  status_response_.control_mode = ControlMode::UNSPECIFIED;
  status_response_.e_stop = false;
  status_response_.error_code = -1;

  // Parse status message
  int ret = std::sscanf(data_to_parse, status_resp_format_, &status_response_.mode,
                        &status_response_.control_mode, &status_response_.e_stop,
                        &status_response_.error_code);

  if (ret <= 0) return false;
  if (ret != 4) {
    // Not all event fields scanned, might add a warning somehow later on
  }
  return true;
}

Status EKICommClient::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  if (event_handler == nullptr) {
    return Status(ReturnCode::ERROR,
                  "RegisterEventHandler failed: please provide a valid pointer.");
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return Status(ReturnCode::OK);
};

}  // namespace kuka::external::control::kss
