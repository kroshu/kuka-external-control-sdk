#ifndef KUKA_EXTERNAL_CONTROL__KSS_EKI_EXTENSION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_EKI_EXTENSION_H_

#include <string>
#include <vector>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss::eki {

enum class AxisType {
  LINEAR,
  ROTATIONAL,
  ENDLESS,
  UNKOWN
};

struct InitializationData {
  std::string semantic_version;
  uint64_t ipoc;
  uint8_t num_axes;
  uint8_t num_external_axes;
  std::string model_name;
  std::string hw_version;
  std::string sw_version;
  std::vector<AxisType> axis_type;
  std::vector<int16_t> ratio_numerator;
  std::vector<int16_t> ratio_denominator;
  std::vector<int16_t> max_rpm;

  uint8_t GetTotalAxisCount() const {
    return num_axes + num_external_axes;
  }
};

struct StatusUpdate {
  ControlMode control_mode_;
  CycleTime cycle_time_;
  bool drives_enabled_;
  bool drives_powered_;
  bool emergency_stop_;
  bool guard_stop_;
  bool in_motion_;
  bool motion_possible_;
  OperationMode operation_mode_;

  void Reset() {
    control_mode_ = ControlMode::UNSPECIFIED;
    cycle_time_ = CycleTime::UNSPECIFIED;
    drives_enabled_ = false;
    drives_powered_ = false;
    emergency_stop_ = false;
    guard_stop_ = false;
    in_motion_ = false;
    motion_possible_ = false;
    operation_mode_ = OperationMode::UNSPECIFIED;
  }
};

class IEventHandlerExtension {
public:
  virtual void OnConnected(const InitializationData& init_data) = 0;
};

class IStatusUpdateHandler {
public:
  virtual void OnStatusUpdateReceived(const StatusUpdate& response) = 0;
};

}  // namespace kuka::external::control::kss::eki
#endif  // KUKA_EXTERNAL_CONTROL__KSS_EKI_EXTENSION_H_
