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

#include "kuka/external-control-sdk/kss/mxa/client.h"

#include <cstring>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/publisher.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"

AXIS_GROUP_REF KRC_AXISGROUPREFARR[6];

using kuka::external::control::ControlMode;

namespace kuka::external::control::kss::mxa {

Client::Client(const std::string& controller_ip, bool error_reset_allowed)
    : error_reset_allowed_(error_reset_allowed) {
  udp_publisher_ = std::make_unique<os::core::udp::communication::Publisher>(
      os::core::udp::communication::SocketAddress(controller_ip, kMXAControllerPort),
      os::core::udp::communication::SocketAddress(), false);

  udp_subscriber_ = std::make_unique<os::core::udp::communication::Subscriber>(
      os::core::udp::communication::SocketAddress(kMXAClientPort),
      os::core::udp::communication::SocketAddress(), false);

  event_handler_ = std::make_unique<EventHandler>();
}

Client::~Client() {
  stop_requested_ = true;

  if (rsi_started_) {
    CancelRSI();
  }

  if (keep_alive_thread_.joinable()) {
    keep_alive_thread_.join();
  }
}

Status Client::Setup() {
  auto pub_setup_ret = udp_publisher_->Setup();
  if (pub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR,
            "UDP publisher setup failed with code " + static_cast<int>(pub_setup_ret)};
  }

  auto sub_setup_ret = udp_subscriber_->Setup();
  if (sub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR,
            "UDP subscriber setup failed with code " + static_cast<int>(sub_setup_ret)};
  }

  StartKeepAliveThread();

  return {ReturnCode::OK, "MXA client setup succeeded"};
}

Status Client::RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler) {
  if (event_handler == nullptr) {
    return {ReturnCode::ERROR, "Event handler cannot be null"};
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return {ReturnCode::OK, "Event handler registered successfully"};
};

Status Client::StartRSI(ControlMode control_mode, CycleTime cycle_time) {
  // Start CMD dispatcher on first start
  start_cmd_dispatcher_ = true;

  mxa_tech_function_m_.INT_DATA[1] = static_cast<int>(control_mode);
  mxa_tech_function_m_.INT_DATA[2] = static_cast<int>(cycle_time);
  rsi_started_notification_sent_ = false;
  rsi_started_ = true;

  // TODO maybe add a wait here for the program start?
  return event_handler_set_
             ? Status{ReturnCode::OK, "RSI program start requested"}
             : Status{ReturnCode::WARN, "RSI program start requested, but no event handler set"};
}

Status Client::CancelRSI() {
  // In some cases e.g. after a receive timeout, an immediate cancel wouldn't succeed,
  // So wait a bit here - TODO check why this is the case
  std::this_thread::sleep_for(std::chrono::milliseconds(kWaitBeforeCancelMs));
  cancelled_ = false;
  cancel_requested_ = true;

  std::unique_lock<std::mutex> cancel_lock(cancel_finished_mutex_);
  cancel_finished_cv_.wait(cancel_lock, [this] { return cancelled_; });
  ResetRSI();
  return {ReturnCode::OK, "RSI program cancel requested"};
}

void Client::SetToCancelled() {
  std::unique_lock<std::mutex> cancel_lock(cancel_finished_mutex_);
  cancelled_ = true;
  cancel_lock.unlock();
  cancel_finished_cv_.notify_one();
}

void Client::HandleBlockError(const std::string& fb_name, int error_id) {
  // If a function block error already occured, don't handle the same again / a new one
  // This way thread is still able to loop and finish cancellation if requested
  // User can still terminate immediately on MXA function block error if desired
  // TODO if other function block failed, don't return
  if (block_error_active_) {
    return;
  }

  event_handler_->OnError("Keep-alive thread: error by " + fb_name +
                          " with id: " + std::to_string(error_id));
  block_error_active_ = true;
}

void Client::ResetRSI() {
  cancel_requested_ = false;
  rsi_started_ = false;
  start_cmd_dispatcher_ = false;
  first_stopmess_ = true;
}

bool Client::ShouldRSIStop() { return should_rsi_stop_; }

Status Client::RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension) {
  if (extension == nullptr) {
    return {ReturnCode::ERROR, "Event handler extension cannot be null"};
  }

  event_handler_extension_ = std::move(extension);
  return {ReturnCode::OK, "Registered event handler extension"};
}

Status Client::RegisterStatusUpdateHandler(std::unique_ptr<IStatusUpdateHandler>&& handler) {
  if (handler == nullptr) {
    return {ReturnCode::ERROR, "Status update handler cannot be null"};
  }

  status_update_handler_ = std::move(handler);
  return {ReturnCode::OK, "Registered status update handler"};
}

void Client::StartKeepAliveThread() {
  keep_alive_thread_ = std::thread([this] {
    int tick = 1;
    bool auto_start_reset = false;
    bool error_msg_present = false;
    bool connected = false;
    int present_error_id = 0;
    std::string error_msg;
    StatusUpdate status_update;

    // Set axis group id for every block
    mxa_read_.AXISGROUPIDX = axis_group_id_;
    mxa_init_.AXISGROUPIDX = axis_group_id_;
    mxa_read_status_.AXISGROUPIDX = axis_group_id_;
    mxa_aut_ext_.AXISGROUPIDX = axis_group_id_;
    mxa_auto_start_.AXISGROUPIDX = axis_group_id_;
    mxa_error_.AXISGROUPIDX = axis_group_id_;
    mxa_read_mxa_error_.AXISGROUPIDX = axis_group_id_;
    mxa_set_override_.AXISGROUPIDX = axis_group_id_;
    mxa_write_.AXISGROUPIDX = axis_group_id_;
    mxa_tech_function_m_.AXISGROUPIDX = axis_group_id_;
    mxa_tech_function_s_.AXISGROUPIDX = axis_group_id_;

    // Set AutExt block values
    mxa_aut_ext_.CONF_MESS = false;
    mxa_aut_ext_.DRIVES_ON = false;
    mxa_aut_ext_.DRIVES_OFF = true;
    mxa_aut_ext_.MOVE_ENABLE = true;
    mxa_aut_ext_.EXT_START = false;
    mxa_aut_ext_.RESET = false;
    mxa_aut_ext_.ENABLE_T1 = false;
    mxa_aut_ext_.ENABLE_T2 = false;
    mxa_aut_ext_.ENABLE_AUT = false;
    mxa_aut_ext_.ENABLE_EXT = true;

    // Set constant override
    mxa_set_override_.OVERRIDE = 100;

    // robot interpreter tech function
    BOOL tech_function_m_bool_data[kMxaTechFunctionParamSize] = {0};
    DINT tech_function_m_int_data[kMxaTechFunctionParamSize] = {0};
    REAL tech_function_m_real_data[kMxaTechFunctionParamSize] = {0.0};
    mxa_tech_function_m_.TECHFUNCTIONID = 2;
    mxa_tech_function_m_.PARAMETERCOUNT = 2;
    mxa_tech_function_m_.BUFFERMODE = 2;
    mxa_tech_function_m_.BOOL_DATA = tech_function_m_bool_data;
    mxa_tech_function_m_.INT_DATA = tech_function_m_int_data;
    mxa_tech_function_m_.REAL_DATA = tech_function_m_real_data;

    // submit interpreter tech function
    BOOL tech_function_s_bool_data[kMxaTechFunctionParamSize] = {0};
    DINT tech_function_s_int_data[kMxaTechFunctionParamSize] = {0};
    REAL tech_function_s_real_data[kMxaTechFunctionParamSize] = {0.0};
    mxa_tech_function_s_.TECHFUNCTIONID = 3;
    mxa_tech_function_s_.PARAMETERCOUNT = 1;  // must be >= 1, though not used
    mxa_tech_function_s_.BUFFERMODE = 0;
    mxa_tech_function_s_.BOOL_DATA = tech_function_s_bool_data;
    mxa_tech_function_s_.INT_DATA = tech_function_s_int_data;
    mxa_tech_function_s_.REAL_DATA = tech_function_s_real_data;

    while (!stop_requested_) {
      if (udp_subscriber_->WaitForAndReceive(kUDPTimeoutMs) ==
          os::core::udp::communication::Subscriber::ErrorCode::kSuccess) {
        std::memcpy(read_buffer_, udp_subscriber_->GetMessage().first,
                    udp_subscriber_->GetMessage().second);

        if (!connected && event_handler_extension_) {
          connected = true;
          event_handler_extension_->OnConnected(InitializationData());
        }
      } else if (tick > kInitTimeoutTicks) {
        // Mark MXA UDP timeout as an error except in the first tick, since that always occurs
        connected = false;
        event_handler_->OnError("Keep-alive thread: UDP subcriber receive timed out");
      }

      // ----------------------------------------------------------------------------
      // Read
      mxa_read_.KRC4_INPUT = read_buffer_;
      mxa_read_.OnCycle();
      if (mxa_read_.ERROR) {
        HandleBlockError("KRC_READAXISGROUP", mxa_read_.ERRORID);
      }

      // Initialize
      mxa_init_.OnCycle();
      if (mxa_init_.ERROR) {
        HandleBlockError("KRC_INITIALIZE", mxa_init_.ERRORID);
      }

      // Read status
      mxa_read_status_.OnCycle();
      if (mxa_read_status_.ERROR) {
        HandleBlockError("KRC_READMXASTATUS", mxa_read_status_.ERRORID);
      }

      // ----------------------------------------------------------------------------
      // Automatic external block
      // needed to turn MOVE_ENABLE, DRIVES_OFF and ENABLE_EXT on - cannot be done with any other
      // block
      mxa_aut_ext_.OnCycle();
      // Stop RSI if RSI started and ESTOP active
      if (!should_rsi_stop_ && mxa_tech_function_m_.BUSY && !mxa_aut_ext_.ALARM_STOP) {
        event_handler_->OnError("ESTOP active");
        should_rsi_stop_ = true;
      }

      // AutoStart - sets existing signals of AutomaticExternal in the correct sequence -
      // used to activate AutExt block easier...
      mxa_auto_start_.EXECUTERESET = auto_start_reset;
      mxa_auto_start_.OnCycle();
      if (mxa_auto_start_.ERROR) {
        HandleBlockError("KRC_AUTOSTART", mxa_auto_start_.ERRORID);
      }

      // Initiate resetting command dispatcher if requested
      if (auto_start_reset) {
        // Prepare reset - set signal to zero to be able to execute a rising edge
        if (!start_cmd_dispatcher_) {
          auto_start_reset = false;
        }
      } else {
        // Rising edge - reset dispatcher
        if (start_cmd_dispatcher_ && mxa_auto_start_.RESETVALID && !mxa_auto_start_.BUSY) {
          auto_start_reset = true;
        }
      }

      // ----------------------------------------------------------------------------
      // Check for errors
      // Reset errors at start if requested (after kInitTimeoutTicks+1 ticks)
      // Errors during execution stay present to be able to check them but can be eliminated after a
      // restart
      mxa_error_.MESSAGERESET =
          error_reset_allowed_ && tick <= kInitTimeoutTicks + 1 ? error_msg_present : false;
      mxa_error_.OnCycle();

      // Check whether mxa error present
      mxa_read_mxa_error_.OnCycle();

      if (mxa_error_.ERROR && !error_msg_present && present_error_id != mxa_error_.ERRORID) {
        if (mxa_error_.NOOPMODEEXT) {
          error_msg = "Robot not in Ext operation mode";
        } else if (mxa_read_mxa_error_.ERROR) {
          error_msg = "MXA error active with ID: ";
          // TODO probably a bug - if MXA UDP timeout is present at the start, we get error with ID
          // 83, but there isn't an error with that id, only 783, which is actually the UDP timeout
          // error. So it is assumed that error code 83 corresponds to error 783.
          error_msg += (mxa_read_mxa_error_.ERRORID == 83)
                           ? "783"
                           : std::to_string(mxa_read_mxa_error_.ERRORID);
        } else if (mxa_error_.ERRORID == 801) {
          error_msg = "STOPMESS active";
        } else if (mxa_error_.KRCERRORACTIVE) {
          error_msg = "KRC error active with ID: " + std::to_string(mxa_error_.ERRORID);
        } else {
          error_msg = "Error occured with ID: " + std::to_string(mxa_error_.ERRORID);
        }

        if (mxa_error_.ERRORID == 801 && first_stopmess_) {
          first_stopmess_ = false;
        } else {
          event_handler_->OnError(error_msg);
        }

        error_msg_present = true;
        present_error_id = mxa_error_.ERRORID;
      } else if (!mxa_error_.ERROR) {
        error_msg_present = false;
      }  // TODO maybe mark that error is still present

      // ----------------------------------------------------------------------------
      // Set program override - by default it is set to 0 and the robot will never move
      mxa_set_override_.OnCycle();
      if (mxa_set_override_.ERROR) {
        HandleBlockError("KRC_SETOVERRIDE", mxa_set_override_.ERRORID);
      }

      // Start program if MXA managed to switch to standby status and start requested
      mxa_tech_function_m_.EXECUTECMD = mxa_read_status_.STATUS >= 3 && rsi_started_;
      mxa_tech_function_m_.OnCycle();
      if (mxa_tech_function_m_.ERROR) {
        HandleBlockError("KRC_TECHFUNCTION2", mxa_tech_function_m_.ERRORID);
      }
      if (rsi_started_ && !rsi_started_notification_sent_) {
        event_handler_->OnSampling();
        rsi_started_notification_sent_ = true;
      }

      // cancel command dispatcher with tech function
      mxa_tech_function_s_.EXECUTECMD = cancel_requested_;
      mxa_tech_function_s_.OnCycle();
      if (mxa_tech_function_s_.ERROR) {
        HandleBlockError("KRC_TECHFUNCTION3", mxa_tech_function_s_.ERRORID);
      }
      if (mxa_tech_function_s_.DONE) {
        SetToCancelled();
      }

      // Before writing the output buffer, send status update
      if (status_update_handler_ != nullptr) {
        status_update.control_mode_ = static_cast<ControlMode>(mxa_tech_function_m_.INT_DATA[1]);
        status_update.cycle_time_ = static_cast<CycleTime>(mxa_tech_function_m_.INT_DATA[2]);
        status_update.drives_powered_ = mxa_aut_ext_.PERI_RDY;
        status_update.emergency_stop_ = !mxa_aut_ext_.ALARM_STOP;
        status_update.guard_stop_ = !mxa_aut_ext_.USER_SAFE;
        status_update.in_motion_ = mxa_aut_ext_.PRO_MOVE;
        status_update.motion_possible_ = mxa_aut_ext_.PRO_ACT;
        if (mxa_aut_ext_.T1) {
          status_update.operation_mode_ = OperationMode::T1;
        } else if (mxa_aut_ext_.T2) {
          status_update.operation_mode_ = OperationMode::T2;
        } else if (mxa_aut_ext_.AUT) {
          status_update.operation_mode_ = OperationMode::AUT;
        } else if (mxa_aut_ext_.EXT) {
          status_update.operation_mode_ = OperationMode::EXT;
        } else {
          status_update.operation_mode_ = OperationMode::UNSPECIFIED;
        }
        status_update.robot_stopped_ = mxa_aut_ext_.ROB_STOPPED;
        status_update_handler_->OnStatusUpdateReceived(status_update);
      }

      // ----------------------------------------------------------------------------
      // Write
      mxa_write_.KRC4_OUTPUT = write_buffer_;
      mxa_write_.OnCycle();
      if (mxa_write_.ERROR) {
        HandleBlockError("KRC_WRITEAXISGROUP", mxa_write_.ERRORID);
      }

      // Send command
      udp_publisher_->Send(write_buffer_, kMXABufferSize);

      // Count ticks until needed
      if (tick <= kInitTimeoutTicks + 1) {
        tick++;
      }
    }
  });
}

}  // namespace kuka::external::control::kss::mxa
