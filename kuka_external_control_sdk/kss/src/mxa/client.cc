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

AXIS_GROUP_REF KRC_AXISGROUPREFARR[6];

using kuka::external::control::ControlMode;

namespace kuka::external::control::kss::mxa
{

Client::Client(const std::string & controller_ip, int client_port)
{
  udp_publisher_ = std::make_unique<os::core::udp::communication::Publisher>(
    os::core::udp::communication::SocketAddress(controller_ip, kMXAServerPort),
    os::core::udp::communication::SocketAddress(kMXAClientSendPort), false);

  udp_subscriber_ = std::make_unique<os::core::udp::communication::Subscriber>(
    os::core::udp::communication::SocketAddress(client_port),
    os::core::udp::communication::SocketAddress(), false);

  event_handler_ = std::make_unique<EventHandler>();
}

Client::~Client()
{
  stop_requested_ = true;

  if (rsi_started_)
  {
    CancelRSI();
  }

  if (keep_alive_thread_.joinable())
  {
    keep_alive_thread_.join();
  }
}

Status Client::Setup()
{
  auto pub_setup_ret = udp_publisher_->Setup();
  if (pub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess)
  {
    return {
      ReturnCode::ERROR, "UDP publisher setup failed with code " + static_cast<int>(pub_setup_ret)};
  }

  auto sub_setup_ret = udp_subscriber_->Setup();
  if (sub_setup_ret != os::core::udp::communication::Publisher::ErrorCode::kSuccess)
  {
    return {
      ReturnCode::ERROR,
      "UDP subscriber setup failed with code " + static_cast<int>(sub_setup_ret)};
  }

  StartKeepAliveThread();

  return {ReturnCode::OK, "MXA client setup succeeded"};
}

Status Client::RegisterEventHandler(std::unique_ptr<EventHandler> && event_handler)
{
  if (event_handler == nullptr)
  {
    return {ReturnCode::ERROR, "Event handler cannot be null"};
  }

  std::lock_guard<std::mutex> lck(event_handler_mutex_);

  event_handler_ = std::move(event_handler);
  event_handler_set_ = true;

  return {ReturnCode::OK, "Event handler registered successfully"};
};

Status Client::StartRSI(ControlMode control_mode, CycleTime cycle_time)
{
  // Start CMD dispatcher on first start
  start_cmd_dispatcher_ = true;
  start_rsi_ = true;

  control_mode_ = control_mode;
  cycle_time_ = cycle_time;
  rsi_started_notification_sent_ = false;
  rsi_started_ = true;

  return event_handler_set_
           ? Status{ReturnCode::OK, "RSI program start requested"}
           : Status{ReturnCode::WARN, "RSI program start requested, but no event handler set"};
}

Status Client::CancelRSI()
{
  // Cancel only works, if program is not active, stop program by MOVE_DISABLE =
  // false Add short sleep to make sure RSI program is stopped gracefully
  // TODO(Svastits): consider using state variable instead of hard-coded sleep
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  mxa_wrapper_.moveDisable();
  cancelled_ = false;
  cancel_requested_ = true;

  std::unique_lock<std::mutex> cancel_lock(cancel_finished_mutex_);
  cancel_finished_cv_.wait(cancel_lock, [this] { return cancelled_; });
  ResetRSI();
  return {ReturnCode::OK, "RSI program cancel requested"};
}

void Client::SetToCancelled()
{
  std::unique_lock<std::mutex> cancel_lock(cancel_finished_mutex_);
  cancelled_ = true;
  cancel_lock.unlock();
  cancel_finished_cv_.notify_one();
}

void Client::ResetRSI()
{
  cancel_requested_ = false;
  rsi_started_ = false;
  start_cmd_dispatcher_ = false;
  start_rsi_ = false;
}

void Client::TurnOnDrives() { mxa_wrapper_.drivesOn(); }

void Client::TurnOffDrives() { mxa_wrapper_.drivesOff(); }

Status Client::RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension> && extension)
{
  if (extension == nullptr)
  {
    return {ReturnCode::ERROR, "Event handler extension cannot be null"};
  }

  event_handler_extension_ = std::move(extension);
  return {ReturnCode::OK, "Registered event handler extension"};
}

Status Client::RegisterStatusUpdateHandler(std::unique_ptr<IStatusUpdateHandler> && handler)
{
  if (handler == nullptr)
  {
    return {ReturnCode::ERROR, "Status update handler cannot be null"};
  }

  status_update_handler_ = std::move(handler);
  return {ReturnCode::OK, "Registered status update handler"};
}

void Client::StartKeepAliveThread()
{
  keep_alive_thread_ = std::thread(
    [this]
    {
      int tick = 1;
      bool connected = false;
      std::string error_msg;
      StatusUpdate status_update;
      StatusUpdate prev_status_update;

      while (!stop_requested_)
      {
        if (
          udp_subscriber_->WaitForAndReceive(kUDPTimeoutMs) ==
          os::core::udp::communication::Subscriber::ErrorCode::kSuccess)
        {
          std::memcpy(
            read_buffer_, udp_subscriber_->GetMessage().first,
            udp_subscriber_->GetMessage().second);

          connected = true;
        }
        else if (tick > kInitTimeoutTicks)
        {
          // Mark MXA UDP timeout as an error except in the first ticks, since
          // that always occurs
          connected = false;
          event_handler_->OnError("Keep-alive thread: UDP subscriber receive timed out");
        }
        if (connected)
        {
          // ----------------------------------------------------------------------------
          // Read
          mxa_wrapper_.getmxAOutput(read_buffer_);

          // Initialize & handle errors
          int error_code = mxa_wrapper_.mxACycle();
          if (
            mxa_wrapper_.isInitialized() && event_handler_extension_ &&
            !connected_notification_sent_)
          {
            event_handler_extension_->OnConnected(
              InitializationData(mxa_wrapper_.getNumAxes(), mxa_wrapper_.getNumExtAxes()));
            connected_notification_sent_ = true;
          }
          else if (!mxa_wrapper_.isInitialized())
          {
            connected_notification_sent_ = false;
          }
          switch (error_code)
          {
            case 0:
              break;
            // do not trigger error for a previous UDP timeout
            case 83:
              error_code = 0;
              break;
            case 801:
              error_msg = "STOPMESS active";
              break;
            case 523:
              error_msg = "Robot not in Ext operation mode";
              break;
            case 525:
              error_msg = "ESTOP is active";
              break;
            default:
              error_msg = "Keep-alive thread error occurred with ID: " + std::to_string(error_code);
              break;
          }

          // Only trigger errors if server has started
          if (error_code != 0 && active_error_code_ != error_code)
          {
            event_handler_->OnError(error_msg);
          }

          active_error_code_ = error_code;

          // Reset initial error messages
          if (tick <= kInitTimeoutTicks + 1)
          {
            mxa_wrapper_.resetErrors();
          }

          // ----------------------------------------------------------------------------
          // AutoStart - sets existing signals of AutomaticExternal in the correct
          // sequence - used to activate AutExt block easier...
          if (start_cmd_dispatcher_)
          {
            auto result = mxa_wrapper_.startMxAServer();
            if (result.block_state == BLOCKSTATE::DONE)
            {
              start_cmd_dispatcher_ = false;
            }
          }

          // Call program starting RSI
          if (mxa_wrapper_.isServerActive() && start_rsi_)
          {
            auto process_rsi_res = mxa_wrapper_.processRSI(
              static_cast<int>(control_mode_), static_cast<int>(cycle_time_));
            if (
              process_rsi_res.block_state == BLOCKSTATE::ACTIVE && !rsi_started_notification_sent_)
            {
              rsi_started_notification_sent_ = true;
              event_handler_->OnSampling();
            }
            if (process_rsi_res.block_state == BLOCKSTATE::DONE)
            {
              start_rsi_ = false;
            }
          }
          // ----------------------------------------------------------------------------
          if (cancel_requested_)
          {
            auto cancel_result = mxa_wrapper_.cancelProgram();

            if (cancel_result.block_state == BLOCKSTATE::DONE)
            {
              SetToCancelled();
            }
          }

          // Before writing the output buffer, send status update
          if (status_update_handler_ != nullptr)
          {
            status_update.control_mode_ = control_mode_;
            status_update.cycle_time_ = cycle_time_;
            status_update.drives_powered_ = mxa_wrapper_.drivesPowered();
            status_update.emergency_stop_ = mxa_wrapper_.emergencyStop();
            status_update.guard_stop_ = mxa_wrapper_.guardStop();
            status_update.in_motion_ = mxa_wrapper_.inMotion();
            status_update.motion_possible_ = mxa_wrapper_.motionPossible();
            status_update.operation_mode_ = static_cast<OperationMode>(mxa_wrapper_.getOpMode());
            status_update.robot_stopped_ = mxa_wrapper_.robotStopped();
            if (status_update != prev_status_update)
            {
              status_update_handler_->OnStatusUpdateReceived(status_update);
              prev_status_update = status_update;
            }
          }

          // ----------------------------------------------------------------------------
          // Write
          mxa_wrapper_.setmxAInput(write_buffer_);
        }
        // Send command
        udp_publisher_->Send(write_buffer_, kMXABufferSize);

        // Count ticks until needed
        if (tick <= kInitTimeoutTicks + 1)
        {
          tick++;
        }
      }
    });
}

}  // namespace kuka::external::control::kss::mxa
