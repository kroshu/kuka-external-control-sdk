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
  MotionState(std::size_t dof, std::vector<GPIOConfiguration> gpio_config_list)
      : BaseMotionState(dof) {
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_velocities_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(
        6, std::numeric_limits<double>::quiet_NaN());

    first_cartesian_position_index_ += kMessagePrefix.length();
    first_cartesian_position_index_ += kCartesianPositionsPrefix.length() - 1;

    for (const auto &config : gpio_config_list) {
      measured_gpio_values_.push_back(
          std::move(std::make_unique<kuka::external::control::kss::GPIOValue>(
              std::move(std::make_unique<GPIOConfig>(config)))));
      gpioAttributePrefix.push_back(" " + config.name + "=\"");
    }
  }
  MotionState(const MotionState &other) = default;
  MotionState &operator=(const MotionState &other) = delete;

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
  const std::string kIpocNodePrefix = "<IPOC>";
  const std::string kIpocNodeSuffix = "</IPOC>";
  const std::string kMessageSuffix = "</Rob>";

  std::vector<std::string> gpioAttributePrefix;

  int first_cartesian_position_index_ = 0;

  long ipoc_ = 0;
  long delay_ = 0;

  static constexpr int kPrecision = 6;
};

class ControlSignal : public BaseControlSignal {
public:
  ControlSignal(std::size_t dof,
                std::vector<GPIOConfiguration> gpio_config_list)
      : BaseControlSignal(dof) {
    joint_position_values_.resize(dof, 0.0);
    initial_positions_.resize(dof, 0.0);
    cartesian_position_values_.resize(6, 0.0);

    for (const auto &config : gpio_config_list) {
      gpio_values_.push_back(
          std::move(std::make_unique<kuka::external::control::kss::GPIOValue>(
              std::move(std::make_unique<GPIOConfig>(config)))));
      gpioAttributePrefix.push_back(" " + config.name + "=\"");
    }

    for (int i = 1; i <= dof; ++i) {
      joint_position_attribute_prefixes_.push_back(" A" + std::to_string(i) +
                                                   "=\"");
    }
  }
  ControlSignal(const ControlSignal &other) = default;
  ControlSignal &operator=(const ControlSignal &other) = delete;

  // Create XML containing relative positions in rad
  std::optional<std::string_view> CreateXMLString(int last_ipoc,
                                                  bool stop_control = false);

  void SetInitialPositions(const MotionState &initial_positions);
  bool InitialPositionsSet() const { return has_initial_positions_; }
  void Reset() { has_initial_positions_ = false; }

private:
  void AppendToXMLString(std::string_view str);

  const std::string kMessagePrefix = "<Sen Type=\"KROSHU\">";
  const std::string kJointPositionsPrefix = "<AK";
  std::vector<std::string> joint_position_attribute_prefixes_;
  const std::string kDoubleAttributeFormat =
      "%." + std::to_string(kPrecision) + "f";
  const std::string kAttributeSuffix = "/>";
  const std::string kStopNodePrefix = "<Stop>";
  const std::string kStopNodeSuffix = "</Stop>";
  const std::string kGpioPrefix = "<GPIO";
  const std::string kIpocNodePrefix = "<IPOC>";
  const std::string kIpocNodeSuffix = "</IPOC>";
  const std::string kMessageSuffix = "</Sen>";

  std::vector<std::string> gpioAttributePrefix;

  bool has_initial_positions_ = false;
  std::vector<double> initial_positions_;

  static constexpr int kPrecision = 6;
  static constexpr int kBufferSize = 1024;
  char xml_string_[kBufferSize];
};
} // namespace kuka::external::control::kss

#endif // KUKA_EXTERNAL_CONTROL__KSS_MESSAGE_BUILDER_H_
