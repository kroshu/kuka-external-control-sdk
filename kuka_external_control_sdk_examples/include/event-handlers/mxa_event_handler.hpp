#ifndef EXTERNAL_CONTROL_SDK_EXAMPLE__MXA_EVENT_HANDLER_H_
#define EXTERNAL_CONTROL_SDK_EXAMPLE__MXA_EVENT_HANDLER_H_

#include <iostream>

#include "kuka/external-control-sdk/kss/mxa/initialization_data.h"
#include "kuka/external-control-sdk/kss/status_update.h"

using kuka::external::control::kss::mxa::IEventHandlerExtension;
using kuka::external::control::kss::mxa::InitializationData;
using kuka::external::control::kss::IStatusUpdateHandler;
using kuka::external::control::kss::StatusUpdate;

namespace external_control_sdk_example {
class EventHandlerExtension : public IEventHandlerExtension {
 public:
  void OnConnected(const InitializationData& init_data) override {
    std::cout << "Established connection to KRC:" << std::endl;
    std::cout << "  Number of axes: " << init_data.num_axes << std::endl;
    std::cout << "  Number of external axes: " << init_data.num_external_axes << std::endl;
  }
};

class StatusUpdateHandler : public IStatusUpdateHandler {
 public:
  void OnStatusUpdateReceived(const StatusUpdate& status) override {
    std::cout << "Received status update from KRC:" << std::endl;
    std::cout << "  Control mode: " << static_cast<int>(status.control_mode_) << std::endl;
    std::cout << "  Cycle time: " << static_cast<int>(status.cycle_time_) << std::endl;
    std::cout << "  Drives powered: " << (status.drives_powered_ ? "true" : "false") << std::endl;
    std::cout << "  Emergency stop: " << (status.emergency_stop_ ? "true" : "false") << std::endl;
    std::cout << "  Guard stop: " << (status.guard_stop_ ? "true" : "false") << std::endl;
    std::cout << "  In motion: " << (status.in_motion_ ? "true" : "false") << std::endl;
    std::cout << "  Motion possible: " << (status.motion_possible_ ? "true" : "false") << std::endl;
    std::cout << "  Operation mode: " << static_cast<int>(status.operation_mode_) << std::endl;
  }
};
}  // namespace external_control_sdk_example

#endif  // EXTERNAL_CONTROL_SDK_EXAMPLE__MXA_EVENT_HANDLER_H_
