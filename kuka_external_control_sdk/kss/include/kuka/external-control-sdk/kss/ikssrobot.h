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

#ifndef KUKA_EXTERNAL_CONTROL__IKSSROBOT_H_
#define KUKA_EXTERNAL_CONTROL__IKSSROBOT_H_

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss {

enum class AxisType {
  LINEAR,
  ROTATIONAL,
  ENDLESS,
  UNKOWN,
};

struct InitializationData {
  std::string semantic_version;
  u_int64_t ipoc;
  u_int8_t num_axes;
  u_int8_t num_external_axes;
  std::string model_name;
  std::string hw_version;
  std::string sw_version;
  std::vector<AxisType> axis_type;
  std::vector<int16_t> ratio_numerator;
  std::vector<int16_t> ratio_denominator;
  std::vector<int16_t> max_rpm;

  u_int8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }
};

class KssEventHandler : public EventHandler {
 public:
  virtual void OnConnected(const InitializationData& init_data) {}
};

// Interface for KSS-specific robot functionalities
class IKssRobot : public IRobot {
 public:
  virtual Status TurnOnDrives() = 0;
  virtual Status TurnOffDrives() = 0;
  virtual Status SetCycleTime(Configuration::CycleTime cycle_time) = 0;

  virtual Status RegisterEventHandler(std::unique_ptr<KssEventHandler>&& event_handler) = 0;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__IKSSROBOT_H_
