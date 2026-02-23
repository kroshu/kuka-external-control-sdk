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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__KSS__MESSAGE_BUILDER_H_
#define KUKA__EXTERNAL_CONTROL_SDK__KSS__MESSAGE_BUILDER_H_

#include <algorithm>
#include <array>
#include <cstring>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "kuka/external-control-sdk/common/message_builder.h"
#include "kuka/external-control-sdk/kss/gpio_value.h"

namespace kuka::external::control::kss
{

static bool ExternalsPrecedeInternals(const std::vector<JointConfiguration> & joint_configs)
{
  const std::size_t num_configs = joint_configs.size();
  for (std::size_t i = 0; i < num_configs; ++i)
  {
    if (!joint_configs[i].is_external)
    {
      for (std::size_t j = i + 1; j < num_configs; ++j)
      {
        if (joint_configs[j].is_external)
        {
          return false;
        }
      }
      break;
    }
  }
  return true;
}

class MotionState : public BaseMotionState
{
public:
  MotionState(
    std::size_t dof, std::vector<GPIOConfiguration> gpio_configs,
    std::vector<JointConfiguration> joint_configs)
  : BaseMotionState(dof), joint_configs_(std::move(joint_configs))
  {
    if (joint_configs_.size() != dof_)
    {
      throw std::invalid_argument(
        "Number of joint configurations does not match degrees of freedom");
    }

    if (!ExternalsPrecedeInternals(joint_configs_))
    {
      throw std::invalid_argument("External axes must precede internal axes");
    }

    num_internal_axes_ = std::count_if(
      joint_configs_.cbegin(), joint_configs_.cend(),
      [](const auto & config) { return !config.is_external; });
    num_external_axes_ = dof_ - num_internal_axes_;
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_velocities_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(6, std::numeric_limits<double>::quiet_NaN());

    first_cartesian_position_index_ += kMessagePrefix.length();
    first_cartesian_position_index_ += kCartesianPositionsPrefix.length() - 1;

    for (const auto & config : gpio_configs)
    {
      measured_gpio_values_.push_back(
        std::move(std::make_unique<kuka::external::control::kss::GPIOValue>(
          std::move(std::make_unique<GPIOConfig>(config)))));
      gpioAttributePrefix.push_back(" " + config.name + "=\"");
    }
  }
  MotionState(const MotionState & other) = default;
  MotionState & operator=(const MotionState & other) = delete;

  void CreateFromXML(const char * incoming_xml);
  int GetIpoc() { return ipoc_; }
  int GetDelay() { return delay_; }

private:
  [[nodiscard]] bool ParseMeasuredPositions(
    const char * str, const std::size_t len, const std::size_t num_values,
    std::size_t & next_value_idx, const std::size_t offset = 0);

  const std::string kMessagePrefix = "<Rob Type=\"KUKA\">";

  const std::string kCartesianPositionsPrefix = "<RIst";
  const std::vector<std::string> kCartesianPositionAttributePrefixes = {" X=\"", " Y=\"", " Z=\"",
                                                                        " A=\"", " B=\"", " C=\""};
  const std::string kAttributeSuffix = "\"/>";

  const std::string kJointPositionsPrefix = "<AIPos";
  const std::string kExtJointPositionsPrefix = "<EIPos";

  const std::string kDelayNodePrefix = "<Delay D=\"";
  const std::string kGpioPrefix = "<GPIO";
  const std::string kIpocNodePrefix = "<IPOC>";
  const std::string kIpocNodeSuffix = "</IPOC>";
  const std::string kMessageSuffix = "</Rob>";

  std::vector<std::string> gpioAttributePrefix;

  int first_cartesian_position_index_ = 0;

  uint64_t ipoc_ = 0;
  uint64_t delay_ = 0;

  std::vector<JointConfiguration> joint_configs_;
  std::size_t num_internal_axes_ = -1;
  std::size_t num_external_axes_ = -1;

  static constexpr uint8_t kFixSixAxes = 6;
  static constexpr int kPrecision = 6;
};

class ControlSignal : public BaseControlSignal
{
public:
  ControlSignal(
    std::size_t dof, std::vector<GPIOConfiguration> gpio_configs,
    std::vector<JointConfiguration> joint_configs)
  : BaseControlSignal(dof), joint_configs_(std::move(joint_configs))
  {
    if (joint_configs_.size() != dof_)
    {
      throw std::invalid_argument(
        "Number of joint configurations does not match degrees of freedom");
    }

    if (!ExternalsPrecedeInternals(joint_configs_))
    {
      throw std::invalid_argument("External axes must precede internal axes");
    }

    num_internal_axes_ = std::count_if(
      joint_configs_.cbegin(), joint_configs_.cend(),
      [](const auto & config) { return !config.is_external; });
    num_external_axes_ = dof_ - num_internal_axes_;
    joint_position_values_.resize(dof, 0.0);
    initial_positions_.resize(dof, 0.0);
    cartesian_position_values_.resize(6, 0.0);

    for (const auto & config : gpio_configs)
    {
      gpio_values_.push_back(std::move(std::make_unique<kuka::external::control::kss::GPIOValue>(
        std::move(std::make_unique<GPIOConfig>(config)))));
      gpioAttributePrefix.push_back(" " + config.name + "=\"");
    }

    for (int i = 1; i <= num_internal_axes_; ++i)
    {
      joint_position_attribute_prefixes_.push_back(" A" + std::to_string(i) + "=\"");
    }

    for (int i = 1; i <= num_external_axes_; ++i)
    {
      ext_joint_position_attribute_prefixes_.push_back(" E" + std::to_string(i) + "=\"");
    }
  }
  ControlSignal(const ControlSignal & other) = default;
  ControlSignal & operator=(const ControlSignal & other) = delete;

  // Create XML containing relative positions in rad
  std::optional<std::string_view> CreateXMLString(int last_ipoc, bool stop_control = false);

  void SetInitialPositions(const MotionState & initial_positions);
  bool InitialPositionsSet() const { return has_initial_positions_; }
  void Reset() { has_initial_positions_ = false; }

private:
  void AppendToXMLString(std::string_view str);

  [[nodiscard]] bool WritePositions(
    const std::vector<std::string> & attrib_prefixes, const std::size_t num_values,
    const std::size_t offset = 0);

  const std::string kMessagePrefix = "<Sen Type=\"KROSHU\">";

  const std::string kStopNodePrefix = "<Stop>";
  const std::string kStopNodeSuffix = "</Stop>";
  const std::string kJointPositionsPrefix = "<AK";
  std::vector<std::string> joint_position_attribute_prefixes_;
  const std::string kDoubleAttributeFormat = "%." + std::to_string(kPrecision) + "f";
  const std::string kAttributeSuffix = "/>";
  const std::string kExtJointPositionsPrefix = "<EK";
  std::vector<std::string> ext_joint_position_attribute_prefixes_;
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

  const std::vector<JointConfiguration> joint_configs_;
  std::size_t num_internal_axes_ = -1;
  std::size_t num_external_axes_ = -1;
};
}  // namespace kuka::external::control::kss

#endif  // KUKA__EXTERNAL_CONTROL_SDK__KSS__MESSAGE_BUILDER_H_
