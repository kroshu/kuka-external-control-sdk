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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_

#include <algorithm>
#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <string>

#include "kuka/external-control-sdk/common/message_builder.h"
#include "kuka/external-control-sdk/kss/gpio_value.h"

namespace kuka::external::control::kss {

class MotionState : public BaseMotionState {
public:
  MotionState(std::size_t dof, std::size_t gpio_size) : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_velocities_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(
        6, std::numeric_limits<double>::quiet_NaN());

    first_cartesian_position_index_ += kMessagePrefix.length();
    first_cartesian_position_index_ += kCartesianPositionsPrefix.length() - 1;

    // TODO (Komaromi): Create GPIO config list
    // Add GPIO Configuration list for state interfaces
    std::unique_ptr<GPIOConfig> gpio_config_list[] = {
        // std::make_unique<GPIOConfig>(0, "GPIO_01",
        // GPIOValueType::BOOL_VALUE),
        // std::make_unique<GPIOConfig>(1, "GPIO_02", GPIOValueType::BOOL_VALUE)
    };
    for (size_t i = 0; i < gpio_size; i++) {
      measured_gpio_values_.push_back(
          std::make_shared<kuka::external::control::kss::GPIOValue>(
              std::move(gpio_config_list[i])));
    }
  }

  MotionState(const MotionState &other) = default;

  void CreateFromXML(const char *incoming_xml);
  int GetIpoc() { return ipoc_; }
  int GetDelay() { return delay_; }

private:
  const std::string kMessagePrefix = "<Rob Type=\"KUKA\">";

  const std::string kCartesianPositionsPrefix = "<RIst";
  const std::vector<std::string> kCartesianPositionAttributePrefixes = {
      " X=\"", " Y=\"", " Z=\"", " A=\"", " B=\"", " C=\""};
  const std::string kAttributeSuffix = "\"/>";

  const std::string kJointPositionsPrefix = "<AIPos";

  const std::string kDelayNodePrefix = "<Delay D=\"";
  const std::string kGpioPrefix = "<GPIO";
  // Add GPIO names for xml parsing
  const std::vector<std::string> kGpioAttributePrefix = {
      /*" 01=\"", " 02=\""*/};
  const std::string kIpocNodePrefix = "<IPOC>";
  const std::string kIpocNodeSuffix = "</IPOC>";
  const std::string kMessageSuffix = "</Rob>";

  int first_cartesian_position_index_ = 0;

  long ipoc_ = 0;
  long delay_ = 0;

  static constexpr int kPrecision = 6;
};

class ControlSignal : public BaseControlSignal {
public:
  ControlSignal(std::size_t dof, std::size_t gpio_size,
                const MotionState &initial_positions)
      : BaseControlSignal(dof), kInitialPositions(initial_positions) {
    joint_position_values_.resize(dof, 0.0);
    cartesian_position_values_.resize(6, 0.0);

    // TODO (Komaromi): Create GPIO config list
    // Add GPIO Configuration list for command interfaces
    std::unique_ptr<GPIOConfig> gpio_config_list[] = {
        // std::make_unique<GPIOConfig>(0, "GPIO_01", GPIOValueType::BOOL_VALUE)
    };
    for (size_t i = 0; i < gpio_size; i++) {
      gpio_values_.push_back(
          std::make_shared<kuka::external::control::kss::GPIOValue>(
              std::move(gpio_config_list[i])));
    }

    for (int i = 1; i <= dof; ++i) {
      joint_position_attribute_prefixes_.push_back(" A" + std::to_string(i) +
                                                   "=\"");
    }
  }

  // Create XML containing relative positions in rad
  std::optional<std::string_view> CreateXMLString(int last_ipoc,
                                                  bool stop_control = false);

private:
  void AppendToXMLString(std::string_view str);

  const std::string kMessagePrefix = "<Sen Type=\"KROSHU\">";
  const std::string kJointPositionsPrefix = "<AK";
  std::vector<std::string> joint_position_attribute_prefixes_;
  const std::string kJointPositionAttributeFormat =
      "%." + std::to_string(kPrecision) + "f";
  const std::string kAttributeSuffix = "/>";
  const std::string kStopNodePrefix = "<Stop>";
  const std::string kStopNodeSuffix = "</Stop>";
  const std::string kGpioPrefix = "<GPIO";
  // Add GPIO names for xml parsing
  const std::vector<std::string> kGpioAttributePrefix = {/*" 01=\""*/};
  const std::string kIpocNodePrefix = "<IPOC>";
  const std::string kIpocNodeSuffix = "</IPOC>";
  const std::string kMessageSuffix = "</Sen>";

  const MotionState &kInitialPositions;

  static constexpr int kPrecision = 6;
  static constexpr int kBufferSize = 1024;
  char xml_string_[kBufferSize];
};
} // namespace kuka::external::control::kss

#endif // KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_
