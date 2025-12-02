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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_COMM_CLIENT_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_COMM_CLIENT_H_

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/mxa/MxAutomationV3_3.h"
#include "kuka/external-control-sdk/kss/mxa/extension.h"
#include "kuka/external-control-sdk/kss/mxa/mxa_wrapper.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/publisher.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"

namespace kuka::external::control::kss::mxa {

// Class for communicating with the KRC via MXA
class Client {
public:
  Client(const std::string &controller_ip, bool error_reset_allowed);

  ~Client();

  // Initiates MXA connection and starts keep-alive thread
  Status Setup();

  // Starts RSI program
  Status StartRSI(ControlMode control_mode, CycleTime cycle_time);

  // Cancels RSI program and calls ResetRSI
  Status CancelRSI();

  // Reset class to be able to start RSI again
  void ResetRSI();

  // Registers an event handler
  Status RegisterEventHandler(std::unique_ptr<EventHandler> &&event_handler);

  // Check whether there are errors present which should cause the RSI
  // communication to stop
  bool ShouldRSIStop();

  Status RegisterEventHandlerExtension(
      std::unique_ptr<IEventHandlerExtension> &&extension);

  Status
  RegisterStatusUpdateHandler(std::unique_ptr<IStatusUpdateHandler> &&handler);

private:
  // Start keep-alive thread
  void StartKeepAliveThread();

  // UDP communication
  std::unique_ptr<os::core::udp::communication::Publisher> udp_publisher_;
  std::unique_ptr<os::core::udp::communication::Subscriber> udp_subscriber_;
  static constexpr int kMXAControllerPort = 1336;
  static constexpr int kMXAClientPort = 1337;
  static constexpr int kInitTimeoutTicks = 4;
  static constexpr std::chrono::milliseconds kUDPTimeoutMs{100};
  static constexpr std::chrono::milliseconds kWaitBeforeCancelMs{1000};

  // Event handling
  std::mutex event_handler_mutex_;
  std::unique_ptr<EventHandler> event_handler_;
  bool event_handler_set_ = false;

  // Keep-alive thread
  std::thread keep_alive_thread_;
  std::atomic<bool> stop_requested_{false};

  // MXA communication
  //------------------------------

  // Byte arrays for the communication
  static constexpr int kMXABufferSize = 256;
  BYTE read_buffer_[kMXABufferSize];
  BYTE write_buffer_[kMXABufferSize];

  mxAWrapper mxa_wrapper_;

  std::atomic<bool> should_rsi_stop_{false};
  const bool error_reset_allowed_;
  std::atomic<bool> start_cmd_dispatcher_{false};
  std::atomic<bool> rsi_started_{false};
  std::atomic<bool> rsi_started_notification_sent_{false};
  std::atomic<bool> first_stopmess_{true};

  std::atomic<bool> cancel_requested_{false};
  bool cancelled_{false};
  std::mutex cancel_finished_mutex_;
  std::condition_variable cancel_finished_cv_;

  void SetToCancelled();

  std::unique_ptr<IEventHandlerExtension> event_handler_extension_;

  std::unique_ptr<IStatusUpdateHandler> status_update_handler_;

  CycleTime cycle_time_ = CycleTime::UNSPECIFIED;
  ControlMode control_mode_ = ControlMode::UNSPECIFIED;

  int active_error_code_ = 0;

  static constexpr std::size_t kMxaTechFunctionParamSize = 41;
};

} // namespace kuka::external::control::kss::mxa

#endif // KUKA_EXTERNAL_CONTROL__KSS_MXA_COMM_CLIENT_H_
