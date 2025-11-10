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

namespace kuka::external::control::kss {

void MotionState::CreateFromXML(const char *incoming_xml) {
  if (incoming_xml == nullptr) {
    throw std::invalid_argument("Received XML can not be null");
  }

  int len = strlen(incoming_xml);
  std::size_t next_value_idx = first_cartesian_position_index_;
  for (int i = 0; i < kCartesianPositionAttributePrefixes.size(); ++i) {
    std::size_t dbl_length = 0;
    next_value_idx += kCartesianPositionAttributePrefixes[i].length() + 1;
    if (next_value_idx < len) {
      measured_cartesian_positions_[i] =
          std::stod(&incoming_xml[next_value_idx], &dbl_length);
      if (i > 2) {
        measured_cartesian_positions_[i] *= (M_PI / 180);
      }
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length;
  }

  next_value_idx += kAttributeSuffix.length();
  // this -1 is to account for that there is no " before the fist attribute
  next_value_idx += kJointPositionsPrefix.length() - 1;

  // Non-external axes
  for (int i = 0; i < kFixSixAxes; ++i) {
    std::size_t dbl_length = 0;
    next_value_idx += std::floor(std::log10(
        i + 1.0));       // length of extra digits, e.g. for more than 10 dofs
    next_value_idx += 6; // length of prefix + 1, e.g. " A1=\""

    if (next_value_idx < len) {
      // Only set values for configured axes
      if (i < num_of_non_ext_axes_){
        measured_positions_[i + (dof_ - num_of_non_ext_axes_)] =
            std::stod(&incoming_xml[next_value_idx], &dbl_length) * (M_PI / 180);
      } else {
        std::stod(&incoming_xml[next_value_idx], &dbl_length);
      }
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length; // length of the parsed double
  }
  next_value_idx += kAttributeSuffix.length();

  // Delay
  next_value_idx += kDelayNodePrefix.length();

  if (next_value_idx >= len) {
    throw std::invalid_argument("Received XML is not valid for the given "
                                "degree of freedom, Delay node is missing");
  }

  char *endptr = nullptr;
  delay_ = std::strtol(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == nullptr) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom, Delay "
        "value is not a valid number");
  }

  next_value_idx += endptr - &incoming_xml[next_value_idx];
  next_value_idx += kAttributeSuffix.length();

  // External axes
  // this -1 is to account for that there is no " before the fist attribute
  next_value_idx += kExtJointPositionsPrefix.length() - 1;

  for (int i = 0; i < kFixSixAxes; ++i) {
    std::size_t dbl_length = 0;
    next_value_idx += std::floor(std::log10(
        i + 1.0));       // length of extra digits, e.g. for more than 10 dofs
    next_value_idx += 6; // length of prefix + 1, e.g. " E1=\""

    if (next_value_idx < len) {
      if(i < (dof_-num_of_non_ext_axes_)) {
         measured_positions_[i] =
            std::stod(&incoming_xml[next_value_idx], &dbl_length) / 1000.0;
      } else {
         std::stod(&incoming_xml[next_value_idx], &dbl_length);
      }
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length; // length of the parsed double
  }
  next_value_idx += kAttributeSuffix.length();

  // GPIO
  if (!gpioAttributePrefix.empty()) {
    next_value_idx += kGpioPrefix.length() - 1;
  }

  for (int i = 0; i < gpioAttributePrefix.size(); ++i) {

    std::size_t dbl_length = 0;
    next_value_idx += gpioAttributePrefix[i].length() + 1;
    if (next_value_idx < len) {
      measured_gpio_values_[i]->SetValue(
          std::stod(&incoming_xml[next_value_idx], &dbl_length));
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given GPIO configuration");
    }
    next_value_idx += dbl_length; // length of the parsed double
  }
  if (!gpioAttributePrefix.empty()) {
    next_value_idx += kAttributeSuffix.length();
  }
  next_value_idx += kIpocNodePrefix.length();

  if (next_value_idx >= len) {
    throw std::invalid_argument("Received XML is not valid for the given "
                                "degree of freedom, IPOC node is missing");
  }

  ipoc_ = std::strtol(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == &incoming_xml[next_value_idx]) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom, IPOC value "
        "is not a valid number");
  }

  has_positions_ = true;
  has_cartesian_positions_ = true;
};

void ControlSignal::AppendToXMLString(std::string_view str) {
  strncat(xml_string_, str.data(),
          kBufferSize - strnlen(xml_string_, kBufferSize) - 1);
}

std::optional<std::string_view>
ControlSignal::CreateXMLString(int last_ipoc, bool stop_control) {
  std::memset(xml_string_, 0, sizeof(xml_string_));

  AppendToXMLString(kMessagePrefix);
  // Non-external axes
  AppendToXMLString(kJointPositionsPrefix);
  for (int i = 0; i < kFixSixAxes; ++i) {
    char double_buffer[kPrecision + 3 + 1 + 1 +
                       1]; // Precision + Digits + Comma + Null + Minus sign
    AppendToXMLString(joint_position_attribute_prefixes_[i]);
    // Index of Ax in all joint position values
    short a_index = (dof_ - num_of_non_ext_axes_) + i;
    // Only update values for configured axes
    double a_value = (i < num_of_non_ext_axes_) ? (joint_position_values_[a_index] - initial_positions_[a_index]) : initial_positions_[a_index];
    int ret = std::snprintf(
        double_buffer, sizeof(double_buffer), kDoubleAttributeFormat.data(),
        a_value * (180 / M_PI));
    if (ret <= 0) {
      return std::nullopt;
    }

    AppendToXMLString(double_buffer);
    AppendToXMLString("\"");
  }
  AppendToXMLString(kAttributeSuffix);

  // Stop
  AppendToXMLString(kStopNodePrefix);
  AppendToXMLString(stop_control ? "1" : "0");
  AppendToXMLString(kStopNodeSuffix);

  // External axes
  AppendToXMLString(kExtJointPositionsPrefix);
  for (int i = 0; i < kFixSixAxes; ++i) {
    char double_buffer[kPrecision + 3 + 1 + 1 +
                       1]; // Precision + Digits + Comma + Null + Minus sign
    AppendToXMLString(ext_joint_position_attribute_prefixes_[i]);
    // Only update values for configured axes
    double e_value = i < (dof_ - num_of_non_ext_axes_) ? (joint_position_values_[i] - initial_positions_[i]) : initial_positions_[i];
    int ret = std::snprintf(
        double_buffer, sizeof(double_buffer), kDoubleAttributeFormat.data(),
        e_value * 1000.0);
    if (ret <= 0) {
      return std::nullopt;
    }

    AppendToXMLString(double_buffer);
    AppendToXMLString("\"");
  }
  AppendToXMLString(kAttributeSuffix);

  // GPIO
  if (!gpioAttributePrefix.empty()) {
    AppendToXMLString(kGpioPrefix);
  }
  for (size_t i = 0; i < gpioAttributePrefix.size(); i++) {
    AppendToXMLString(gpioAttributePrefix[i]);
    switch (gpio_values_[i]->GetGPIOConfig()->GetValueType()) {
    case GPIOValueType::BOOL: {
      // Append bool value
      auto value = gpio_values_[i]->GetBoolValue();
      if (value.has_value()) {
        AppendToXMLString(value.value() ? "1" : "0");
      } else {
        return std::nullopt;
      }
      break;
    }
    case GPIOValueType::DOUBLE: {
      // Append double value
      char double_buffer[kPrecision + 19 + 1 + 1 +
                         1]; // Precision + Digits + Comma + Null + Minus sign
      auto value = gpio_values_[i]->GetDoubleValue();
      if (value.has_value()) {
        int ret = std::snprintf(double_buffer, sizeof(double_buffer),
                                kDoubleAttributeFormat.data(), value.value());
        if (ret <= 0) {
          return std::nullopt;
        }
        AppendToXMLString(double_buffer);
      } else {
        return std::nullopt;
      }
      break;
    }
    case GPIOValueType::LONG: {
      // Append double value
      char long_buffer[19 + 1 + 1]; // Digits + Null + Minus sign
      auto value = gpio_values_[i]->GetLongValue();
      if (value.has_value()) {
        int ret = std::snprintf(long_buffer, sizeof(long_buffer), "%ld",
                                value.value());
        if (ret <= 0) {
          return std::nullopt;
        }
        AppendToXMLString(long_buffer);
      } else {
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
  if (!gpioAttributePrefix.empty()) {
    AppendToXMLString(kAttributeSuffix);
  }
  AppendToXMLString(kIpocNodePrefix);
  AppendToXMLString(std::to_string(last_ipoc).data());
  AppendToXMLString(kIpocNodeSuffix);
  AppendToXMLString(kMessageSuffix);

  return xml_string_;
}

void ControlSignal::SetInitialPositions(const MotionState &initial_positions) {
  has_initial_positions_ = true;
  std::copy(initial_positions.GetMeasuredPositions().cbegin(),
            initial_positions.GetMeasuredPositions().cend(),
            initial_positions_.begin());
}

} // namespace kuka::external::control::kss
