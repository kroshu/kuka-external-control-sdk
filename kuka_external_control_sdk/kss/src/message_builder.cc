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

#include "kuka/external-control-sdk/kss/message_builder.h"

#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>

namespace kuka::external::control::kss
{

static double RadiansToDegrees(const double radians) { return radians * 180 / M_PI; }
static double DegreesToRadians(const double degrees) { return degrees * M_PI / 180; }
static double MetersToMillimetres(const double meters) { return meters * 1'000; }
static double MillimetresToMeters(const double millimetres) { return millimetres / 1'000; }

// Use std::strtod because floating-point std::from_chars is not available
// on GCC versions shipped with Debian Bullseye or RHEL 8. Consider no longer supporting these.
// std::stod is not used because it allocates memory when casting from char* to std::string
std::size_t MotionState::ParseDouble(const char * start, const char * end, double & out)
{
  errno = 0;  // required: strtod uses errno for range errors
  char * parse_end = nullptr;

  // strtod stops early on invalid input, does not allocate, and is very fast
  out = std::strtod(start, &parse_end);

  // No characters consumed → invalid number
  if (parse_end == start)
  {
    throw std::invalid_argument("Received XML contains an invalid numeric value");
  }

  // Range error (underflow/overflow)
  if (errno == ERANGE)
  {
    throw std::out_of_range("Received XML numeric value is out of range");
  }

  // Do not allow parsing past the XML buffer
  if (parse_end > end)
  {
    throw std::invalid_argument("Received XML contains an overly long numeric value");
  }

  return static_cast<std::size_t>(parse_end - start);
}

void MotionState::CreateFromXML(const char * incoming_xml)
{
  if (incoming_xml == nullptr)
  {
    throw std::invalid_argument("Received XML can not be null");
  }

  const std::string_view xml(incoming_xml);

  has_positions_ = false;
  has_torques_ = false;
  has_velocities_ = false;
  has_cartesian_positions_ = false;

  for (const auto & order_entry : parse_plan_.parse_order)
  {
    switch (order_entry.field_type)
    {
      case MotionStateXmlFieldType::CARTESIAN:
        if (!parse_plan_.cartesian_entry.has_value())
        {
          throw std::logic_error("Cartesian parse entry is not configured");
        }
        ParseCartesianField(xml, parse_plan_.cartesian_entry.value());
        has_cartesian_positions_ = true;
        break;
      case MotionStateXmlFieldType::JOINT:
        ParseJointField(xml, order_entry.index);
        break;
      case MotionStateXmlFieldType::DELAY:
        ParseDelayField(xml);
        break;
      case MotionStateXmlFieldType::GPIO:
        ParseGpioField(xml, order_entry.index);
        break;
      case MotionStateXmlFieldType::IPOC:
        ParseIpocField(xml);
        break;
      default:
        throw std::invalid_argument("Unsupported parse order entry type");
    }
  }
}

MotionStateXmlConfiguration MotionState::CreateDefaultXmlConfiguration(
  const std::vector<JointConfiguration> & joint_configs,
  const std::vector<GPIOConfiguration> & gpio_configs)
{
  MotionStateXmlConfiguration config;
  config.cartesian.enabled = true;
  config.cartesian.xml_element = "RIst";
  config.cartesian.xml_attributes = {"X", "Y", "Z", "A", "B", "C"};
  config.delay_xml_element = "Delay";
  config.delay_xml_attribute = "D";
  config.gpio_xml_element = "GPIO";
  config.ipoc_xml_element = "IPOC";

  std::size_t internal_idx = 1;
  std::size_t external_idx = 1;
  for (const auto & joint : joint_configs)
  {
    MotionStateJointFieldConfiguration field;
    field.joint_identifier = joint.name;
    field.signal_type = MotionStateSignalType::POSITION;
    if (joint.is_external)
    {
      field.xml_element = "EIPos";
      field.xml_attribute = "E" + std::to_string(external_idx++);
    }
    else
    {
      field.xml_element = "AIPos";
      field.xml_attribute = "A" + std::to_string(internal_idx++);
    }
    config.joint_fields.push_back(std::move(field));
  }

  config.gpio_xml_attributes.reserve(gpio_configs.size());
  for (const auto & gpio : gpio_configs)
  {
    config.gpio_xml_attributes.push_back(gpio.name);
  }

  config.field_order.reserve(
    1 + config.joint_fields.size() + 1 + config.gpio_xml_attributes.size() + 1);
  config.field_order.push_back({MotionStateXmlFieldType::CARTESIAN, 0});
  for (std::size_t i = 0; i < config.joint_fields.size(); ++i)
  {
    config.field_order.push_back({MotionStateXmlFieldType::JOINT, i});
  }
  config.field_order.push_back({MotionStateXmlFieldType::DELAY, 0});
  for (std::size_t i = 0; i < config.gpio_xml_attributes.size(); ++i)
  {
    config.field_order.push_back({MotionStateXmlFieldType::GPIO, i});
  }
  config.field_order.push_back({MotionStateXmlFieldType::IPOC, 0});

  return config;
}

void MotionState::InitializeParsePlan(
  std::optional<MotionStateXmlConfiguration> xml_config,
  const std::vector<GPIOConfiguration> & gpio_configs)
{
  MotionStateXmlConfiguration runtime_config =
    xml_config.has_value() ? std::move(xml_config.value())
                           : CreateDefaultXmlConfiguration(joint_configs_, gpio_configs);

  if (runtime_config.delay_xml_element.empty() || runtime_config.delay_xml_attribute.empty())
  {
    throw std::invalid_argument("Delay XML configuration must not be empty");
  }
  if (runtime_config.ipoc_xml_element.empty())
  {
    throw std::invalid_argument("IPOC XML element must not be empty");
  }
  if (runtime_config.cartesian.enabled && runtime_config.cartesian.xml_element.empty())
  {
    throw std::invalid_argument("Cartesian XML element must not be empty when enabled");
  }

  auto get_or_add_element_index = [this](const std::string & element_name) -> std::size_t
  {
    const auto it =
      std::find(parse_plan_.element_names.begin(), parse_plan_.element_names.end(), element_name);
    if (it != parse_plan_.element_names.end())
    {
      return static_cast<std::size_t>(std::distance(parse_plan_.element_names.begin(), it));
    }
    parse_plan_.element_names.push_back(element_name);
    return parse_plan_.element_names.size() - 1;
  };

  parse_plan_.delay_element_name = runtime_config.delay_xml_element;
  parse_plan_.delay_attribute_name = runtime_config.delay_xml_attribute;
  parse_plan_.ipoc_element_name = runtime_config.ipoc_xml_element;
  parse_plan_.ipoc_opening_tag = "<" + parse_plan_.ipoc_element_name + ">";
  parse_plan_.ipoc_closing_tag = "</" + parse_plan_.ipoc_element_name + ">";

  if (runtime_config.cartesian.enabled)
  {
    CartesianParseEntry entry;
    entry.element_index = get_or_add_element_index(runtime_config.cartesian.xml_element);
    entry.attribute_names = runtime_config.cartesian.xml_attributes;
    parse_plan_.cartesian_entry = std::move(entry);
  }

  parse_plan_.joint_entries.reserve(runtime_config.joint_fields.size());
  for (const auto & field : runtime_config.joint_fields)
  {
    if (field.joint_identifier.empty() || field.xml_element.empty() || field.xml_attribute.empty())
    {
      throw std::invalid_argument("Joint field configuration entries must not be empty");
    }

    const auto joint_it = std::find_if(
      joint_configs_.cbegin(), joint_configs_.cend(),
      [&](const JointConfiguration & c) { return c.name == field.joint_identifier; });
    if (joint_it == joint_configs_.cend())
    {
      throw std::invalid_argument("Joint field refers to unknown joint identifier");
    }
    const std::size_t joint_index =
      static_cast<std::size_t>(std::distance(joint_configs_.cbegin(), joint_it));

    JointParseEntry entry;
    switch (field.signal_type)
    {
      case MotionStateSignalType::POSITION:
        entry.quantity = ParsedQuantity::POSITION;
        break;
      case MotionStateSignalType::VELOCITY:
        entry.quantity = ParsedQuantity::VELOCITY;
        break;
      case MotionStateSignalType::TORQUE:
        entry.quantity = ParsedQuantity::TORQUE;
        break;
      default:
        throw std::invalid_argument("Unsupported motion-state signal type");
    }
    entry.joint_index = joint_index;
    entry.element_index = get_or_add_element_index(field.xml_element);
    entry.attribute_name = field.xml_attribute;
    parse_plan_.joint_entries.push_back(std::move(entry));
  }

  if (runtime_config.gpio_xml_attributes.empty())
  {
    runtime_config.gpio_xml_attributes = gpio_attribute_names_;
  }
  if (!measured_gpio_values_.empty())
  {
    if (runtime_config.gpio_xml_element.empty())
    {
      throw std::invalid_argument("GPIO XML element must not be empty when GPIO is configured");
    }
    if (runtime_config.gpio_xml_attributes.size() != measured_gpio_values_.size())
    {
      throw std::invalid_argument("GPIO XML attributes count must match configured GPIO count");
    }
    parse_plan_.gpio_element_index = get_or_add_element_index(runtime_config.gpio_xml_element);
    parse_plan_.gpio_attribute_names = std::move(runtime_config.gpio_xml_attributes);
  }

  if (runtime_config.field_order.empty())
  {
    if (parse_plan_.cartesian_entry.has_value())
    {
      parse_plan_.parse_order.push_back({MotionStateXmlFieldType::CARTESIAN, 0});
    }
    for (std::size_t i = 0; i < parse_plan_.joint_entries.size(); ++i)
    {
      parse_plan_.parse_order.push_back({MotionStateXmlFieldType::JOINT, i});
    }
    parse_plan_.parse_order.push_back({MotionStateXmlFieldType::DELAY, 0});
    for (std::size_t i = 0; i < parse_plan_.gpio_attribute_names.size(); ++i)
    {
      parse_plan_.parse_order.push_back({MotionStateXmlFieldType::GPIO, i});
    }
    parse_plan_.parse_order.push_back({MotionStateXmlFieldType::IPOC, 0});
  }
  else
  {
    parse_plan_.parse_order.reserve(runtime_config.field_order.size());
    for (const auto & entry : runtime_config.field_order)
    {
      parse_plan_.parse_order.push_back({entry.field_type, entry.index});
    }
  }

  ValidateAndFinalizeParsePlan();
}

void MotionState::ValidateAndFinalizeParsePlan()
{
  std::vector<uint8_t> parsed_joint_entries(parse_plan_.joint_entries.size(), 0);
  std::vector<uint8_t> parsed_gpio_entries(parse_plan_.gpio_attribute_names.size(), 0);
  bool has_delay = false;
  bool has_ipoc = false;
  bool has_cartesian = false;

  for (const auto & order_entry : parse_plan_.parse_order)
  {
    switch (order_entry.field_type)
    {
      case MotionStateXmlFieldType::CARTESIAN:
        if (!parse_plan_.cartesian_entry.has_value())
        {
          throw std::invalid_argument("Parse order references disabled Cartesian field");
        }
        if (order_entry.index != 0 || has_cartesian)
        {
          throw std::invalid_argument("Cartesian field must appear at most once in parse order");
        }
        has_cartesian = true;
        break;
      case MotionStateXmlFieldType::JOINT:
        if (order_entry.index >= parse_plan_.joint_entries.size())
        {
          throw std::invalid_argument("Parse order joint index is out of range");
        }
        if (parsed_joint_entries[order_entry.index] != 0)
        {
          throw std::invalid_argument("Parse order contains duplicate joint field entries");
        }
        parsed_joint_entries[order_entry.index] = 1;
        break;
      case MotionStateXmlFieldType::DELAY:
        if (order_entry.index != 0 || has_delay)
        {
          throw std::invalid_argument("Delay field must appear exactly once in parse order");
        }
        has_delay = true;
        break;
      case MotionStateXmlFieldType::GPIO:
        if (order_entry.index >= parse_plan_.gpio_attribute_names.size())
        {
          throw std::invalid_argument("Parse order GPIO index is out of range");
        }
        if (parsed_gpio_entries[order_entry.index] != 0)
        {
          throw std::invalid_argument("Parse order contains duplicate GPIO entries");
        }
        parsed_gpio_entries[order_entry.index] = 1;
        break;
      case MotionStateXmlFieldType::IPOC:
        if (order_entry.index != 0 || has_ipoc)
        {
          throw std::invalid_argument("IPOC field must appear exactly once in parse order");
        }
        has_ipoc = true;
        break;
      default:
        throw std::invalid_argument("Unsupported parse order field type");
    }
  }

  if (!has_delay || !has_ipoc)
  {
    throw std::invalid_argument("Parse order must contain both Delay and IPOC fields");
  }
  if (parse_plan_.cartesian_entry.has_value() && !has_cartesian)
  {
    throw std::invalid_argument("Cartesian parsing is enabled but not present in parse order");
  }
  if (!std::all_of(
        parsed_joint_entries.cbegin(), parsed_joint_entries.cend(),
        [](uint8_t v) { return v != 0; }))
  {
    throw std::invalid_argument("Parse order must include all configured joint field entries");
  }
  if (!std::all_of(
        parsed_gpio_entries.cbegin(), parsed_gpio_entries.cend(), [](uint8_t v) { return v != 0; }))
  {
    throw std::invalid_argument("Parse order must include all configured GPIO entries");
  }
}

std::size_t MotionState::FindElementStart(
  std::string_view xml, std::string_view element_name, std::size_t start_pos)
{
  if (element_name.empty())
  {
    return std::string_view::npos;
  }

  std::size_t pos = start_pos;
  while (pos < xml.size())
  {
    const std::size_t tag_start = xml.find('<', pos);
    if (tag_start == std::string_view::npos)
    {
      return tag_start;
    }

    const std::size_t name_start = tag_start + 1;
    if (name_start + element_name.size() > xml.size())
    {
      return std::string_view::npos;
    }
    if (xml.compare(name_start, element_name.size(), element_name) == 0)
    {
      const std::size_t next = name_start + element_name.size();
      if (
        next < xml.size() && (xml[next] == ' ' || xml[next] == '\t' || xml[next] == '\r' ||
                              xml[next] == '\n' || xml[next] == '>'))
      {
        return tag_start;
      }
    }
    pos = tag_start + 1;
  }

  return std::string_view::npos;
}

std::size_t MotionState::FindElementEnd(std::string_view xml, std::size_t element_start)
{
  const std::size_t element_end = xml.find("/>", element_start);
  if (element_end == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML contains an element without '/>' termination");
  }
  return element_end + 2;
}

std::size_t MotionState::FindAttributeValueStart(
  std::string_view xml, std::size_t element_start, std::size_t element_end,
  std::string_view attribute_name)
{
  std::size_t search_pos = element_start;
  while (search_pos < element_end)
  {
    const std::size_t name_pos = xml.find(attribute_name, search_pos);
    if (name_pos == std::string_view::npos || name_pos >= element_end)
    {
      break;
    }

    const std::size_t value_quote = name_pos + attribute_name.size();
    if (value_quote + 1 < element_end && xml[value_quote] == '=' && xml[value_quote + 1] == '"')
    {
      return value_quote + 2;
    }
    search_pos = name_pos + 1;
  }

  throw std::invalid_argument("Received XML is missing a configured attribute");
}

void MotionState::ParseJointField(std::string_view xml, std::size_t joint_entry_index)
{
  const auto & entry = parse_plan_.joint_entries.at(joint_entry_index);
  const std::string & element_name = parse_plan_.element_names.at(entry.element_index);
  const std::size_t element_start = FindElementStart(xml, element_name, 0);
  if (element_start == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML is missing a configured joint element");
  }
  const std::size_t element_end = FindElementEnd(xml, element_start);
  const std::size_t value_start =
    FindAttributeValueStart(xml, element_start, element_end, entry.attribute_name);

  double parsed = 0.0;
  const std::size_t parsed_len =
    ParseDouble(xml.data() + value_start, xml.data() + xml.size(), parsed);

  if (value_start + parsed_len >= element_end || xml[value_start + parsed_len] != '"')
  {
    throw std::invalid_argument("Received XML contains malformed numeric attributes");
  }

  const auto & joint_config = joint_configs_.at(entry.joint_index);
  switch (entry.quantity)
  {
    case ParsedQuantity::POSITION:
      switch (joint_config.type)
      {
        case JointConfiguration::Type::REVOLUTE:
          measured_positions_[entry.joint_index] = DegreesToRadians(parsed);
          break;
        case JointConfiguration::Type::PRISMATIC:
          measured_positions_[entry.joint_index] = MillimetresToMeters(parsed);
          break;
        default:
          throw std::invalid_argument("Unknown joint type in position parser");
      }
      has_positions_ = true;
      break;
    case ParsedQuantity::VELOCITY:
      switch (joint_config.type)
      {
        case JointConfiguration::Type::REVOLUTE:
          measured_velocities_[entry.joint_index] = DegreesToRadians(parsed);
          break;
        case JointConfiguration::Type::PRISMATIC:
          measured_velocities_[entry.joint_index] = MillimetresToMeters(parsed);
          break;
        default:
          throw std::invalid_argument("Unknown joint type in velocity parser");
      }
      has_velocities_ = true;
      break;
    case ParsedQuantity::TORQUE:
      measured_torques_[entry.joint_index] =
        parsed;  // TODO: The unit of torque is not specified in the XML, so we assume it is in Nm.
                 // If the unit is different, conversion may be needed here.
      has_torques_ = true;
      break;
    default:
      throw std::invalid_argument("Unknown joint field quantity");
  }
}

void MotionState::ParseCartesianField(std::string_view xml, const CartesianParseEntry & entry)
{
  const std::string & element_name = parse_plan_.element_names.at(entry.element_index);
  const std::size_t element_start = FindElementStart(xml, element_name, 0);
  if (element_start == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML is missing configured Cartesian element");
  }
  const std::size_t element_end = FindElementEnd(xml, element_start);

  for (std::size_t i = 0; i < kCartesianDimensions; ++i)
  {
    const std::size_t value_start =
      FindAttributeValueStart(xml, element_start, element_end, entry.attribute_names[i]);

    double parsed = 0.0;
    const std::size_t parsed_len =
      ParseDouble(xml.data() + value_start, xml.data() + xml.size(), parsed);
    if (value_start + parsed_len >= element_end || xml[value_start + parsed_len] != '"')
    {
      throw std::invalid_argument("Received XML contains malformed Cartesian attribute");
    }

    measured_cartesian_positions_[i] = (i > 2) ? DegreesToRadians(parsed) : parsed;
  }
}

void MotionState::ParseDelayField(std::string_view xml)
{
  const std::size_t element_start = FindElementStart(xml, parse_plan_.delay_element_name, 0);
  if (element_start == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML is missing configured Delay element");
  }
  const std::size_t element_end = FindElementEnd(xml, element_start);
  const std::size_t value_start =
    FindAttributeValueStart(xml, element_start, element_end, parse_plan_.delay_attribute_name);

  errno = 0;
  char * endptr = nullptr;
  delay_ = std::strtoull(xml.data() + value_start, &endptr, 0);
  if (errno != 0 || endptr == xml.data() + value_start)
  {
    throw std::invalid_argument("Received XML Delay value is not a valid integer");
  }
}

void MotionState::ParseGpioField(std::string_view xml, std::size_t gpio_index)
{
  if (!parse_plan_.gpio_element_index.has_value())
  {
    throw std::logic_error("GPIO parse entry exists but GPIO element is not configured");
  }
  const std::size_t element_index = parse_plan_.gpio_element_index.value();
  const std::string & element_name = parse_plan_.element_names.at(element_index);
  const std::size_t element_start = FindElementStart(xml, element_name, 0);
  if (element_start == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML is missing configured GPIO element");
  }
  const std::size_t element_end = FindElementEnd(xml, element_start);
  const std::size_t value_start = FindAttributeValueStart(
    xml, element_start, element_end, parse_plan_.gpio_attribute_names.at(gpio_index));

  double parsed = 0.0;
  const std::size_t parsed_len =
    ParseDouble(xml.data() + value_start, xml.data() + xml.size(), parsed);
  if (value_start + parsed_len >= element_end || xml[value_start + parsed_len] != '"')
  {
    throw std::invalid_argument("Received XML contains malformed GPIO attribute");
  }
  measured_gpio_values_.at(gpio_index)->SetValue(parsed);
}

void MotionState::ParseIpocField(std::string_view xml)
{
  const std::size_t value_start = xml.find(parse_plan_.ipoc_opening_tag);
  if (value_start == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML is missing configured IPOC element");
  }
  const std::size_t numeric_start = value_start + parse_plan_.ipoc_opening_tag.size();
  const std::size_t value_end = xml.find(parse_plan_.ipoc_closing_tag, numeric_start);
  if (value_end == std::string_view::npos)
  {
    throw std::invalid_argument("Received XML contains malformed IPOC element");
  }

  errno = 0;
  char * endptr = nullptr;
  ipoc_ = std::strtoull(xml.data() + numeric_start, &endptr, 0);
  if (
    errno != 0 || endptr == xml.data() + numeric_start ||
    static_cast<std::size_t>(endptr - xml.data()) > value_end)
  {
    throw std::invalid_argument("Received XML IPOC value is not a valid integer");
  }
}

void ControlSignal::AppendToXMLString(std::string_view str)
{
  strncat(xml_string_, str.data(), kBufferSize - strnlen(xml_string_, kBufferSize) - 1);
}

void ControlSignal::InitializeWritePlan(
  std::optional<ControlSignalXmlConfiguration> xml_config,
  const std::vector<GPIOConfiguration> & gpio_configs)
{
  ControlSignalXmlConfiguration cfg =
    xml_config.has_value() ? std::move(xml_config.value()) : ControlSignalXmlConfiguration{};

  if (cfg.joint_xml_element.empty())
  {
    throw std::invalid_argument("Joint XML element name must not be empty");
  }
  if (num_external_axes_ > 0 && cfg.ext_joint_xml_element.empty())
  {
    throw std::invalid_argument(
      "External joint XML element name must not be empty when external axes are configured");
  }
  if (!gpio_configs.empty() && cfg.gpio_xml_element.empty())
  {
    throw std::invalid_argument(
      "GPIO XML element name must not be empty when GPIO commands are configured");
  }
  if (cfg.ipoc_xml_element.empty())
  {
    throw std::invalid_argument("IPOC XML element name must not be empty");
  }

  write_plan_.joint_element_prefix = "<" + cfg.joint_xml_element;

  if (cfg.joint_xml_attributes.empty())
  {
    for (std::size_t i = 1; i <= num_internal_axes_; ++i)
    {
      write_plan_.joint_attrib_prefixes.push_back(" A" + std::to_string(i) + "=\"");
    }
  }
  else
  {
    if (cfg.joint_xml_attributes.size() != num_internal_axes_)
    {
      throw std::invalid_argument(
        "Joint XML attribute count must match the number of internal axes");
    }
    for (const auto & attr : cfg.joint_xml_attributes)
    {
      if (attr.empty())
      {
        throw std::invalid_argument("Joint XML attribute names must not be empty");
      }
      write_plan_.joint_attrib_prefixes.push_back(" " + attr + "=\"");
    }
  }

  write_plan_.ext_joint_element_prefix = "<" + cfg.ext_joint_xml_element;

  if (cfg.ext_joint_xml_attributes.empty())
  {
    for (std::size_t i = 1; i <= num_external_axes_; ++i)
    {
      write_plan_.ext_joint_attrib_prefixes.push_back(" E" + std::to_string(i) + "=\"");
    }
  }
  else
  {
    if (cfg.ext_joint_xml_attributes.size() != num_external_axes_)
    {
      throw std::invalid_argument(
        "External joint XML attribute count must match the number of external axes");
    }
    for (const auto & attr : cfg.ext_joint_xml_attributes)
    {
      if (attr.empty())
      {
        throw std::invalid_argument("External joint XML attribute names must not be empty");
      }
      write_plan_.ext_joint_attrib_prefixes.push_back(" " + attr + "=\"");
    }
  }

  write_plan_.gpio_element_prefix = "<" + cfg.gpio_xml_element;
  for (const auto & gpio_cfg : gpio_configs)
  {
    write_plan_.gpio_attrib_prefixes.push_back(" " + gpio_cfg.name + "=\"");
  }

  write_plan_.ipoc_opening_tag = "<" + cfg.ipoc_xml_element + ">";
  write_plan_.ipoc_closing_tag = "</" + cfg.ipoc_xml_element + ">";

  if (cfg.field_order.empty())
  {
    write_plan_.write_order.push_back(ControlSignalXmlFieldType::JOINT);
    if (num_external_axes_ > 0)
    {
      write_plan_.write_order.push_back(ControlSignalXmlFieldType::EXT_JOINT);
    }
    if (!gpio_configs.empty())
    {
      write_plan_.write_order.push_back(ControlSignalXmlFieldType::GPIO);
    }
    write_plan_.write_order.push_back(ControlSignalXmlFieldType::IPOC);
  }
  else
  {
    write_plan_.write_order.reserve(cfg.field_order.size());
    for (const auto & entry : cfg.field_order)
    {
      write_plan_.write_order.push_back(entry.field_type);
    }
  }

  ValidateAndFinalizeWritePlan();
}

void ControlSignal::ValidateAndFinalizeWritePlan()
{
  bool has_joint = false;
  bool has_ext_joint = false;
  bool has_gpio = false;
  bool has_ipoc = false;

  for (const auto & field_type : write_plan_.write_order)
  {
    switch (field_type)
    {
      case ControlSignalXmlFieldType::JOINT:
        if (has_joint)
        {
          throw std::invalid_argument("Write order must contain JOINT field at most once");
        }
        has_joint = true;
        break;
      case ControlSignalXmlFieldType::EXT_JOINT:
        if (has_ext_joint)
        {
          throw std::invalid_argument("Write order must contain EXT_JOINT field at most once");
        }
        has_ext_joint = true;
        break;
      case ControlSignalXmlFieldType::GPIO:
        if (has_gpio)
        {
          throw std::invalid_argument("Write order must contain GPIO field at most once");
        }
        has_gpio = true;
        break;
      case ControlSignalXmlFieldType::IPOC:
        if (has_ipoc)
        {
          throw std::invalid_argument("Write order must contain IPOC field at most once");
        }
        has_ipoc = true;
        break;
      default:
        throw std::invalid_argument("Unsupported field type in write order");
    }
  }

  if (!has_ipoc)
  {
    throw std::invalid_argument("Write order must contain the IPOC field");
  }
  if (!has_joint)
  {
    throw std::invalid_argument("Write order must contain the JOINT field");
  }
  if (num_external_axes_ > 0 && !has_ext_joint)
  {
    throw std::invalid_argument(
      "Write order must contain EXT_JOINT when external axes are configured");
  }
  if (num_external_axes_ == 0 && has_ext_joint)
  {
    throw std::invalid_argument(
      "Write order contains EXT_JOINT but no external axes are configured");
  }
  if (!write_plan_.gpio_attrib_prefixes.empty() && !has_gpio)
  {
    throw std::invalid_argument("Write order must contain GPIO when GPIO commands are configured");
  }
  if (write_plan_.gpio_attrib_prefixes.empty() && has_gpio)
  {
    throw std::invalid_argument("Write order contains GPIO but no GPIO commands are configured");
  }
}

std::optional<std::string_view> ControlSignal::CreateXMLString(
  uint64_t last_ipoc, bool stop_control)
{
  std::memset(xml_string_, 0, sizeof(xml_string_));

  AppendToXMLString(kMessagePrefix);

  AppendToXMLString(kStopNodePrefix);
  AppendToXMLString(stop_control ? "1" : "0");
  AppendToXMLString(kStopNodeSuffix);

  for (const auto & field_type : write_plan_.write_order)
  {
    switch (field_type)
    {
      case ControlSignalXmlFieldType::JOINT:
        AppendToXMLString(write_plan_.joint_element_prefix);
        if (!WritePositions(
              write_plan_.joint_attrib_prefixes, num_internal_axes_, num_external_axes_))
        {
          return std::nullopt;
        }
        break;
      case ControlSignalXmlFieldType::EXT_JOINT:
        AppendToXMLString(write_plan_.ext_joint_element_prefix);
        if (!WritePositions(write_plan_.ext_joint_attrib_prefixes, num_external_axes_))
        {
          return std::nullopt;
        }
        break;
      case ControlSignalXmlFieldType::GPIO:
        AppendToXMLString(write_plan_.gpio_element_prefix);
        if (!WriteGpioValues())
        {
          return std::nullopt;
        }
        break;
      case ControlSignalXmlFieldType::IPOC:
      {
        AppendToXMLString(write_plan_.ipoc_opening_tag);
        char ipoc_buf[32];
        if (
          std::snprintf(
            ipoc_buf, sizeof(ipoc_buf), "%llu", static_cast<unsigned long long>(last_ipoc)) < 0)
        {
          return std::nullopt;
        }
        AppendToXMLString(ipoc_buf);
        AppendToXMLString(write_plan_.ipoc_closing_tag);
        break;
      }
      default:
        return std::nullopt;
    }
  }

  AppendToXMLString(kMessageSuffix);

  return xml_string_;
}

bool ControlSignal::WriteGpioValues()
{
  for (std::size_t i = 0; i < write_plan_.gpio_attrib_prefixes.size(); ++i)
  {
    AppendToXMLString(write_plan_.gpio_attrib_prefixes[i]);
    switch (gpio_values_[i]->GetGPIOConfig()->GetValueType())
    {
      case GPIOValueType::BOOL:
      {
        auto value = gpio_values_[i]->GetBoolValue();
        if (!value.has_value())
        {
          return false;
        }
        AppendToXMLString(value.value() ? "1" : "0");
        break;
      }
      case GPIOValueType::DOUBLE:
      {
        char double_buffer[kPrecision + 19 + 1 + 1 + 1];
        auto value = gpio_values_[i]->GetDoubleValue();
        if (!value.has_value())
        {
          return false;
        }
        int ret = std::snprintf(
          double_buffer, sizeof(double_buffer), kDoubleAttributeFormat.data(), value.value());
        if (ret <= 0)
        {
          return false;
        }
        AppendToXMLString(double_buffer);
        break;
      }
      case GPIOValueType::LONG:
      {
        char long_buffer[19 + 1 + 1];
        auto value = gpio_values_[i]->GetLongValue();
        if (!value.has_value())
        {
          return false;
        }
        int ret = std::snprintf(long_buffer, sizeof(long_buffer), "%ld", value.value());
        if (ret <= 0)
        {
          return false;
        }
        AppendToXMLString(long_buffer);
        break;
      }
      default:
        return false;
    }
    AppendToXMLString("\"");
  }
  AppendToXMLString(kAttributeSuffix);
  return true;
}

bool ControlSignal::WritePositions(
  const std::vector<std::string> & attrib_prefixes, const std::size_t num_values,
  const std::size_t offset)
{
  using JointType = JointConfiguration::Type;

  for (std::size_t i = 0; i < num_values; ++i)
  {
    char
      double_buffer[kPrecision + 3 + 1 + 1 + 1];  // Precision + Digits + Comma + Null + Minus sign
    AppendToXMLString(attrib_prefixes[i]);

    const std::size_t idx = i + offset;
    const double value = joint_position_values_[idx] - initial_positions_[idx];
    double target_value;
    switch (joint_configs_[idx].type)
    {
      case JointType::REVOLUTE:
        target_value = RadiansToDegrees(value);
        break;
      case JointType::PRISMATIC:
        target_value = MetersToMillimetres(value);
        break;
      default:
        return false;
    }

    const int ret = std::snprintf(
      double_buffer, sizeof(double_buffer), kDoubleAttributeFormat.data(), target_value);

    if (ret <= 0)
    {
      return false;
    }

    AppendToXMLString(double_buffer);
    AppendToXMLString("\"");
  }
  AppendToXMLString(kAttributeSuffix);

  return true;
}

void ControlSignal::SetInitialPositions(const MotionState & initial_positions)
{
  has_initial_positions_ = true;
  std::copy(
    initial_positions.GetMeasuredPositions().cbegin(),
    initial_positions.GetMeasuredPositions().cend(), initial_positions_.begin());
}

}  // namespace kuka::external::control::kss
