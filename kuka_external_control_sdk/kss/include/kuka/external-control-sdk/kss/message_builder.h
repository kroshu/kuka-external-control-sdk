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
#include <string_view>
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
    std::vector<JointConfiguration> joint_configs,
    const std::optional<MotionStateXmlConfiguration> & xml_config = std::nullopt)
  : BaseMotionState(dof), joint_configs_(std::move(joint_configs))
  {
    if (joint_configs_.size() != dof_)
    {
      throw std::invalid_argument(
        "Number of joint configurations does not match degrees of freedom");
    }
    measured_positions_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_torques_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_velocities_.resize(dof, std::numeric_limits<double>::quiet_NaN());
    measured_cartesian_positions_.resize(6, std::numeric_limits<double>::quiet_NaN());
    gpio_attribute_names_.reserve(gpio_configs.size());
    for (const auto & config : gpio_configs)
    {
      measured_gpio_values_.push_back(
        std::move(std::make_unique<kuka::external::control::kss::GPIOValue>(
          std::move(std::make_unique<GPIOConfig>(config)))));
      gpio_attribute_names_.push_back(config.name);
    }
    InitializeParsePlan(xml_config, gpio_configs);
  }
  MotionState(const MotionState & other) = default;
  MotionState & operator=(const MotionState & other) = delete;

  void CreateFromXML(const char * incoming_xml);
  uint64_t GetIpoc() const { return ipoc_; }
  uint64_t GetDelay() const { return delay_; }

private:
  static std::size_t ParseDouble(const char * start, const char * end, double & out);
  enum class ParsedQuantity : uint8_t
  {
    POSITION = 0,
    VELOCITY = 1,
    TORQUE = 2
  };
  static ParsedQuantity ToParsedQuantity(MotionStateSignalType signal_type);

  struct JointParseEntry
  {
    ParsedQuantity quantity = ParsedQuantity::POSITION;
    std::size_t joint_index = 0;
    std::size_t element_index = 0;
    std::string attribute_name;
  };

  struct CartesianParseEntry
  {
    std::size_t element_index = 0;
    std::array<std::string, 6> attribute_names;
  };

  struct ParseOrderEntry
  {
    MotionStateXmlFieldType field_type = MotionStateXmlFieldType::JOINT;
    std::size_t index = 0;
  };

  struct ParsePlan
  {
    std::vector<std::string> element_names;
    std::vector<JointParseEntry> joint_entries;
    std::optional<CartesianParseEntry> cartesian_entry;
    std::string delay_element_name = "Delay";
    std::string delay_attribute_name = "D";
    std::string ipoc_element_name = "IPOC";
    std::string ipoc_opening_tag = "<IPOC>";
    std::string ipoc_closing_tag = "</IPOC>";
    std::optional<std::size_t> gpio_element_index;
    std::vector<std::string> gpio_attribute_names;
    std::vector<ParseOrderEntry> parse_order;
  };

  static MotionStateXmlConfiguration CreateDefaultXmlConfiguration(
    const std::vector<JointConfiguration> & joint_configs,
    const std::vector<GPIOConfiguration> & gpio_configs);
  std::size_t GetOrAddParseElementIndex(const std::string & element_name);
  void InitializeCoreParsePlanFields(const MotionStateXmlConfiguration & config);
  void AddCartesianParseEntry(const MotionStateXmlConfiguration & config);
  void AddJointParseEntries(const MotionStateXmlConfiguration & config);
  void ConfigureGpioParseEntries(MotionStateXmlConfiguration & config);
  void BuildParseOrder(const MotionStateXmlConfiguration & config);
  std::size_t FindJointIndexByIdentifier(const std::string & joint_identifier) const;
  void InitializeParsePlan(
    const std::optional<MotionStateXmlConfiguration> & xml_config,
    const std::vector<GPIOConfiguration> & gpio_configs);
  void ValidateAndFinalizeParsePlan() const;
  static std::size_t FindElementStart(
    std::string_view xml, std::string_view element_name, std::size_t start_pos);
  static std::size_t FindElementEnd(std::string_view xml, std::size_t element_start);
  static std::size_t FindAttributeValueStart(
    std::string_view xml, std::size_t element_start, std::size_t element_end,
    std::string_view attribute_name);
  void ParseJointField(std::string_view xml, std::size_t joint_entry_index);
  void ParseCartesianField(std::string_view xml, const CartesianParseEntry & entry);
  void ParseDelayField(std::string_view xml);
  void ParseGpioField(std::string_view xml, std::size_t gpio_index);
  void ParseIpocField(std::string_view xml);

  uint64_t ipoc_ = 0;
  uint64_t delay_ = 0;

  std::vector<JointConfiguration> joint_configs_;
  ParsePlan parse_plan_;
  std::vector<std::string> gpio_attribute_names_;

  static constexpr std::size_t kCartesianDimensions = 6;
};

class ControlSignal : public BaseControlSignal
{
public:
  ControlSignal(
    std::size_t dof, std::vector<GPIOConfiguration> gpio_configs,
    std::vector<JointConfiguration> joint_configs,
    const std::optional<ControlSignalXmlConfiguration> & xml_config = std::nullopt)
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
    }

    InitializeWritePlan(xml_config, gpio_configs);
  }
  ControlSignal(const ControlSignal & other) = default;
  ControlSignal & operator=(const ControlSignal & other) = delete;

  // Create XML containing relative positions in rad
  std::optional<std::string_view> CreateXMLString(uint64_t last_ipoc, bool stop_control = false);

  void SetInitialPositions(const MotionState & initial_positions);
  bool InitialPositionsSet() const { return has_initial_positions_; }
  void Reset() { has_initial_positions_ = false; }

private:
  void AppendToXMLString(std::string_view str);

  [[nodiscard]] bool WritePositions(
    const std::vector<std::string> & attrib_prefixes, const std::size_t num_values,
    const std::size_t offset = 0);

  [[nodiscard]] bool WriteGpioValues();

  struct WritePlan
  {
    std::string joint_element_prefix;
    std::vector<std::string> joint_attrib_prefixes;
    std::string ext_joint_element_prefix;
    std::vector<std::string> ext_joint_attrib_prefixes;
    std::string gpio_element_prefix;
    std::vector<std::string> gpio_attrib_prefixes;
    std::string ipoc_opening_tag;
    std::string ipoc_closing_tag;
    std::vector<ControlSignalXmlFieldType> write_order;
  };

  void InitializeWritePlan(
    const std::optional<ControlSignalXmlConfiguration> & xml_config,
    const std::vector<GPIOConfiguration> & gpio_configs);
  void InitializeJointWritePrefixes(const ControlSignalXmlConfiguration & cfg);
  void InitializeExternalJointWritePrefixes(const ControlSignalXmlConfiguration & cfg);
  void InitializeGpioWritePrefixes(const std::vector<GPIOConfiguration> & gpio_configs);
  void BuildWriteOrder(
    const ControlSignalXmlConfiguration & cfg, const std::vector<GPIOConfiguration> & gpio_configs);
  void ValidateAndFinalizeWritePlan() const;

  const std::string kMessagePrefix = "<Sen Type=\"KROSHU\">";
  const std::string kStopNodePrefix = "<Stop>";
  const std::string kStopNodeSuffix = "</Stop>";
  const std::string kAttributeSuffix = "/>";
  const std::string kMessageSuffix = "</Sen>";

  WritePlan write_plan_;

  bool has_initial_positions_ = false;
  std::vector<double> initial_positions_;

  static constexpr int kPrecision = 6;
  static constexpr int kBufferSize = 1024;
  char xml_string_[kBufferSize];

  const std::vector<JointConfiguration> joint_configs_;
  std::size_t num_internal_axes_ = 0;
  std::size_t num_external_axes_ = 0;
};
}  // namespace kuka::external::control::kss

#endif  // KUKA__EXTERNAL_CONTROL_SDK__KSS__MESSAGE_BUILDER_H_
