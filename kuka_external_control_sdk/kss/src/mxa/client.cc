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

#include "kuka/external-control-sdk/kss/mxa/client.h"

#include <cstring>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/publisher.h"
#include "kuka/external-control-sdk/utils/os-core-udp-communication/subscriber.h"

AXIS_GROUP_REF KRC_AXISGROUPREFARR[6];

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
  // Cancel RSI program if still running
  if (rsi_started_) CancelRSI();
  stop_requested_ = true;
  if (keep_alive_thread_.joinable()) {
    keep_alive_thread_.join();
  }
}

Status Client::Setup() {
  auto pub_setup_ret = udp_publisher_->Setup();
  if (pub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR, "Setup of UDP publisher failed with code"};
  }

  auto sub_setup_ret = udp_subscriber_->Setup();
  if (sub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess) {
    return {ReturnCode::ERROR,
            "Setup of UDP subscriber failed with code: " + static_cast<int>(sub_setup_ret)};
  }

  StartKeepAliveThread();

  return {ReturnCode::OK, "Setup of MXA client succeeded"};
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

Status Client::StartRSI(kuka::external::control::ControlMode control_mode) {
  // Start CMD dispatcher on first start
  start_cmd_dispatcher_ = true;
  mxa_write_sys_var_.VALUE6 = static_cast<int>(control_mode);
  rsi_started_ = true;

  // TODO maybe add a wait here for the program start?
  return event_handler_set_
             ? Status(ReturnCode::OK, "RSI program start requested")
             : Status(ReturnCode::WARN,
                      "Warning: StartControlling called with default event handler.");
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
  return {ReturnCode::OK, "RSI program cancel request sent"};
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
  if (block_error_active_) return;
  std::string error_msg =
      "Keep-alive thread: error by " + fb_name + " with id: " + std::to_string(error_id);
  event_handler_->OnError(error_msg);
  block_error_active_ = true;
}

void Client::ResetRSI() {
  cancel_requested_ = false;
  rsi_started_ = false;
}

bool Client::ShouldRSIStop() { return should_rsi_stop_; }

void Client::StartKeepAliveThread() {
  keep_alive_thread_ = std::thread([this] {
    int tick = 1;
    bool auto_start_reset = false;
    bool error_msg_present = false;
    int present_error_id = 0;
    std::string error_msg;

    // Set axis group id for every block
    mxa_read_.AXISGROUPIDX = axis_group_id_;
    mxa_init_.AXISGROUPIDX = axis_group_id_;
    mxa_read_status_.AXISGROUPIDX = axis_group_id_;
    mxa_aut_ext_.AXISGROUPIDX = axis_group_id_;
    mxa_auto_start_.AXISGROUPIDX = axis_group_id_;
    mxa_error_.AXISGROUPIDX = axis_group_id_;
    mxa_read_mxa_error_.AXISGROUPIDX = axis_group_id_;
    mxa_set_override_.AXISGROUPIDX = axis_group_id_;
    mxa_write_sys_var_.AXISGROUPIDX = axis_group_id_;
    mxa_write_sys_var_cancel_.AXISGROUPIDX = axis_group_id_;
    mxa_write_.AXISGROUPIDX = axis_group_id_;

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

    // Set constant values of write sys var block
    // Select RSI program via system variable (control mode set already in StartRSI)
    mxa_write_sys_var_.INDEX = 6;
    mxa_write_sys_var_.BUFFERMODE = 2;  // TODO: consider 1 (Aborting)
    mxa_write_sys_var_.BCONTINUE = false;

    // Set constant values for cancelling via write sys var
    mxa_write_sys_var_cancel_.INDEX = 6;
    mxa_write_sys_var_cancel_.VALUE6 = 0;
    mxa_write_sys_var_cancel_.BUFFERMODE = 0;

    while (!stop_requested_) {
      if (udp_subscriber_->WaitForAndReceive(std::chrono::milliseconds(kUDPTimeoutMs)) ==
          os::core::udp::communication::Subscriber::ErrorCode::kSuccess) {
        std::memcpy(read_buffer_, udp_subscriber_->GetMessage().first,
                    udp_subscriber_->GetMessage().second);
      } else if (tick > kInitTimeoutTicks) {
        // Mark MXA UDP timeout as an error except in the first tick, since that always occurs
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
      if (!should_rsi_stop_ && mxa_write_sys_var_.BUSY && !mxa_aut_ext_.ALARM_STOP) {
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
        if (!start_cmd_dispatcher_ && mxa_auto_start_.DISPACTIVE) {
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
          error_reset_allowed_ && (tick <= (kInitTimeoutTicks + 1)) ? error_msg_present : false;
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

        event_handler_->OnError(error_msg);
        error_msg_present = true;
        present_error_id = mxa_error_.ERRORID;
      } else if (!mxa_error_.ERROR) {
        error_msg_present = false;
      }  // TODO maybe mark that error is still present

      // ----------------------------------------------------------------------------
      // Set program override - by defalt it is set to 0 and the robot will never move
      mxa_set_override_.OnCycle();
      if (mxa_set_override_.ERROR) {
        HandleBlockError("KRC_SETOVERRIDE", mxa_set_override_.ERRORID);
      }

      // Start program if MXA managed to switch to standby status and start requested
      mxa_write_sys_var_.EXECUTECMD = mxa_read_status_.STATUS >= 3 && rsi_started_;
      mxa_write_sys_var_.OnCycle();
      if (mxa_write_sys_var_.ERROR) {
        HandleBlockError("KRC_WRITESYSVAR - start", mxa_write_sys_var_.ERRORID);
      }

      // Cancel program if requested
      mxa_write_sys_var_cancel_.EXECUTECMD = cancel_requested_;
      mxa_write_sys_var_cancel_.OnCycle();
      if (mxa_write_sys_var_cancel_.ERROR) {
        HandleBlockError("KRC_WRITESYSVAR - cancel", mxa_write_sys_var_cancel_.ERRORID);
      }
      if (mxa_write_sys_var_cancel_.DONE) {
        SetToCancelled();
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
      if (tick <= kInitTimeoutTicks + 1) tick++;
    }
  });
}

}  // namespace kuka::external::control::kss
