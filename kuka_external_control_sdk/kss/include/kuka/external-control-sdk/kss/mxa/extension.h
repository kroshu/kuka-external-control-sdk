#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_EXTENSION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_EXTENSION_H_

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss::mxa {

struct InitializationData {
  InitializationData (uint8_t num_ax, uint8_t num_ext_ax): num_axes(num_ax), num_external_axes(num_ext_ax)
  {}

  uint8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }

  uint8_t num_axes = 0;
  uint8_t num_external_axes = 0;
};

struct StatusUpdate {
  void Reset() {
    control_mode_ = ControlMode::UNSPECIFIED;
    cycle_time_ = CycleTime::UNSPECIFIED;
    drives_powered_ = false;
    emergency_stop_ = false;
    guard_stop_ = false;
    in_motion_ = false;
    motion_possible_ = false;
    operation_mode_ = OperationMode::UNSPECIFIED;
    robot_stopped_ = false;
  }

  bool operator== (const StatusUpdate& other) const noexcept
  {
    return std::tie(control_mode_, cycle_time_, drives_powered_, emergency_stop_, guard_stop_, in_motion_, motion_possible_, operation_mode_, robot_stopped_) == 
      std::tie(other.control_mode_, other.cycle_time_, other.drives_powered_, other.emergency_stop_, other.guard_stop_, other.in_motion_, other.motion_possible_, other.operation_mode_, robot_stopped_);
  }

  bool operator!=(const StatusUpdate& other) const noexcept
  {
    return !(*this == other);
  }

  ControlMode control_mode_;
  CycleTime cycle_time_;
  bool drives_powered_;
  bool emergency_stop_;
  bool guard_stop_;
  bool in_motion_;
  bool motion_possible_;
  OperationMode operation_mode_;
  bool robot_stopped_;
};

class IEventHandlerExtension {
public:
  virtual void OnConnected(const InitializationData &init_data) = 0;
};

class IStatusUpdateHandler {
public:
  virtual void OnStatusUpdateReceived(const StatusUpdate &response) = 0;
};

} // namespace kuka::external::control::kss::mxa
#endif // KUKA_EXTERNAL_CONTROL__KSS_EKI_EXTENSION_H_
