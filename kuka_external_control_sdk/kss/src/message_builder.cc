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

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace kuka::external::control::kss
{

static double RadiansToDegrees(const double radians) { return radians * 180 / M_PI; }
static double DegreesToRadians(const double degrees) { return degrees * M_PI / 180; }
static double MetersToMillimetres(const double meters) { return meters * 1'000; }
static double MillimetresToMeters(const double millimetres) { return millimetres / 1'000; }

void MotionState::CreateFromXML(const char * incoming_xml)
{
  if (incoming_xml == nullptr)
  {
    throw std::invalid_argument("Received XML can not be null");
  }

  int len = strlen(incoming_xml);
  std::size_t next_value_idx = first_cartesian_position_index_;
  for (int i = 0; i < kCartesianPositionAttributePrefixes.size(); ++i)
  {
    std::size_t dbl_length = 0;
    next_value_idx += kCartesianPositionAttributePrefixes[i].length() + 1;
    if (next_value_idx < len)
    {
      measured_cartesian_positions_[i] = std::stod(&incoming_xml[next_value_idx], &dbl_length);
      if (i > 2)
      {
        measured_cartesian_positions_[i] *= (M_PI / 180);
      }
    }
    else
    {
      throw std::invalid_argument("Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length;
  }

  next_value_idx += kAttributeSuffix.length();

  // Internal axes
  // This -1 is to account for that there is no " before the fist attribute
  next_value_idx += kJointPositionsPrefix.length() - 1;
  if (!ParseMeasuredPositions(
        incoming_xml, len, num_internal_axes_, next_value_idx, num_external_axes_))
  {
    throw std::runtime_error("Failed to parse internal axes values");
  }
  next_value_idx += kAttributeSuffix.length();

  // External axes
  // This -1 accounts for the lack of a quotation mark before the first attribute
  next_value_idx += kExtJointPositionsPrefix.length() - 1;
  if (!ParseMeasuredPositions(incoming_xml, len, num_external_axes_, next_value_idx))
  {
    throw std::runtime_error("Failed to parse external axes values");
  }
  next_value_idx += kAttributeSuffix.length();

  // Delay
  next_value_idx += kDelayNodePrefix.length();

  if (next_value_idx >= len)
  {
    throw std::invalid_argument(
      "Received XML is not valid for the given "
      "degree of freedom, Delay node is missing");
  }

  char * endptr = nullptr;
  delay_ = std::strtoull(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == nullptr)
  {
    throw std::invalid_argument(
      "Received XML is not valid for the given degree of freedom, Delay "
      "value is not a valid number");
  }

  next_value_idx += endptr - &incoming_xml[next_value_idx];
  next_value_idx += kAttributeSuffix.length();

  // GPIO
  if (!gpioAttributePrefix.empty())
  {
    next_value_idx += kGpioPrefix.length() - 1;
  }

  for (int i = 0; i < gpioAttributePrefix.size(); ++i)
  {
    std::size_t dbl_length = 0;
    next_value_idx += gpioAttributePrefix[i].length() + 1;
    if (next_value_idx < len)
    {
      measured_gpio_values_[i]->SetValue(std::stod(&incoming_xml[next_value_idx], &dbl_length));
    }
    else
    {
      throw std::invalid_argument("Received XML is not valid for the given GPIO configuration");
    }
    next_value_idx += dbl_length;  // length of the parsed double
  }
  if (!gpioAttributePrefix.empty())
  {
    next_value_idx += kAttributeSuffix.length();
  }
  next_value_idx += kIpocNodePrefix.length();

  if (next_value_idx >= len)
  {
    throw std::invalid_argument(
      "Received XML is not valid for the given "
      "degree of freedom, IPOC node is missing");
  }

  ipoc_ = std::strtoull(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == &incoming_xml[next_value_idx])
  {
    throw std::invalid_argument(
      "Received XML is not valid for the given degree of freedom, IPOC value "
      "is not a valid number");
  }

  has_positions_ = true;
  has_cartesian_positions_ = true;
};

bool MotionState::ParseMeasuredPositions(
  const char * str, const std::size_t len, const std::size_t num_values,
  std::size_t & next_value_idx, const std::size_t offset)
{
  using JointType = JointConfiguration::Type;

  // RSI always sends exactly six joint values regardless of actual axis count.
  // Values beyond num_values are skipped without storage.
  for (std::size_t i = 0; i < kFixSixAxes; ++i)
  {
    next_value_idx += 6;

    if (next_value_idx < len)
    {
      // Only set values for configured axes
      if (i < num_values)
      {
        std::size_t dbl_length = 0;
        const std::size_t idx = i + offset;
        const double value = std::stod(&str[next_value_idx], &dbl_length);
        next_value_idx += dbl_length;

        switch (joint_configs_[idx].type)
        {
          case JointType::REVOLUTE:
            measured_positions_[idx] = DegreesToRadians(value);
            break;
          case JointType::PRISMATIC:
            measured_positions_[idx] = MillimetresToMeters(value);
            break;
          default:
            return false;
        }
      }
      else
      {
        // Skip all values associated with unconfigured axes
        while (++next_value_idx < len && str[next_value_idx] != '"')
        {
          ;
        }
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

void ControlSignal::AppendToXMLString(std::string_view str)
{
  strncat(xml_string_, str.data(), kBufferSize - strnlen(xml_string_, kBufferSize) - 1);
}

std::optional<std::string_view> ControlSignal::CreateXMLString(int last_ipoc, bool stop_control)
{
  std::memset(xml_string_, 0, sizeof(xml_string_));

  AppendToXMLString(kMessagePrefix);

  // Stop
  AppendToXMLString(kStopNodePrefix);
  AppendToXMLString(stop_control ? "1" : "0");
  AppendToXMLString(kStopNodeSuffix);

  // Internal axes
  AppendToXMLString(kJointPositionsPrefix);
  if (!WritePositions(joint_position_attribute_prefixes_, num_internal_axes_, num_external_axes_))
  {
    return std::nullopt;
  }

  // External axes
  if (num_external_axes_ > 0)
  {
    AppendToXMLString(kExtJointPositionsPrefix);
    if (!WritePositions(ext_joint_position_attribute_prefixes_, num_external_axes_))
    {
      return std::nullopt;
    }
  }

  // GPIO
  if (!gpioAttributePrefix.empty())
  {
    AppendToXMLString(kGpioPrefix);
  }
  for (std::size_t i = 0; i < gpioAttributePrefix.size(); i++)
  {
    AppendToXMLString(gpioAttributePrefix[i]);
    switch (gpio_values_[i]->GetGPIOConfig()->GetValueType())
    {
      case GPIOValueType::BOOL:
      {
        // Append bool value
        auto value = gpio_values_[i]->GetBoolValue();
        if (value.has_value())
        {
          AppendToXMLString(value.value() ? "1" : "0");
        }
        else
        {
          return std::nullopt;
        }
        break;
      }
      case GPIOValueType::DOUBLE:
      {
        // Append double value
        char double_buffer[kPrecision + 19 + 1 + 1 + 1];  // Precision + Digits + Comma + Null +
                                                          // Minus sign
        auto value = gpio_values_[i]->GetDoubleValue();
        if (value.has_value())
        {
          int ret = std::snprintf(
            double_buffer, sizeof(double_buffer), kDoubleAttributeFormat.data(), value.value());
          if (ret <= 0)
          {
            return std::nullopt;
          }
          AppendToXMLString(double_buffer);
        }
        else
        {
          return std::nullopt;
        }
        break;
      }
      case GPIOValueType::LONG:
      {
        // Append double value
        char long_buffer[19 + 1 + 1];  // Digits + Null + Minus sign
        auto value = gpio_values_[i]->GetLongValue();
        if (value.has_value())
        {
          int ret = std::snprintf(long_buffer, sizeof(long_buffer), "%ld", value.value());
          if (ret <= 0)
          {
            return std::nullopt;
          }
          AppendToXMLString(long_buffer);
        }
        else
        {
          return std::nullopt;
        }
        break;
      }
      default:
        return std::nullopt;
        break;
    }
    AppendToXMLString("\"");
  }
  if (!gpioAttributePrefix.empty())
  {
    AppendToXMLString(kAttributeSuffix);
  }
  AppendToXMLString(kIpocNodePrefix);
  AppendToXMLString(std::to_string(last_ipoc).data());
  AppendToXMLString(kIpocNodeSuffix);
  AppendToXMLString(kMessageSuffix);

  return xml_string_;
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
