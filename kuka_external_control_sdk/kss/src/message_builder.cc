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

MotionState &MotionState::operator=(const MotionState &other) {
  if (dof_ != other.dof_) {
    throw std::invalid_argument(
        "Cannot assign MotionState with different degrees of freedom");
  }

  if (this != &other) {
    delay_ = other.delay_;
    ipoc_ = other.ipoc_;
    has_positions_ = other.has_positions_;
    has_torques_ = other.has_torques_;
    has_velocities_ = other.has_velocities_;
    has_cartesian_positions_ = other.has_cartesian_positions_;
    std::copy(other.measured_positions_.cbegin(),
              other.measured_positions_.cend(), measured_positions_.begin());
    std::copy(other.measured_torques_.cbegin(), other.measured_torques_.cend(),
              measured_torques_.begin());
    std::copy(other.measured_velocities_.cbegin(),
              other.measured_velocities_.cend(), measured_velocities_.begin());
    std::copy(other.measured_cartesian_positions_.cbegin(),
              other.measured_cartesian_positions_.cend(),
              measured_cartesian_positions_.begin());
    // TODO (Komaromi): Add gpio to copy
    // std::copy(other.measured_gpio_values_.cbegin(),
    // other.measured_gpio_values_.cend(), measured_gpio_values_.begin());
  }

  return *this;
}

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
  next_value_idx += kJointPositionsPrefix.length() - 1;

  for (int i = 0; i < dof_; ++i) {
    std::size_t dbl_length = 0;
    next_value_idx += std::floor(std::log10(
        i + 1.0));       // length of extra digits, e.g. for more than 10 dofs
    next_value_idx += 6; // length of prefix + 1, e.g. " A1=\""

    if (next_value_idx < len) {
      measured_positions_[i] =
          std::stod(&incoming_xml[next_value_idx], &dbl_length) * (M_PI / 180);
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length; // length of the parsed double
  }
  next_value_idx += kAttributeSuffix.length();
  next_value_idx += kDelayNodePrefix.length();

  if (next_value_idx >= len) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom");
  }

  char *endptr = nullptr;
  delay_ = std::strtol(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == nullptr) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom");
  }

  next_value_idx += endptr - &incoming_xml[next_value_idx];
  next_value_idx += kAttributeSuffix.length();
  next_value_idx += kGpioPrefix.length() - 1;

  for (int i = 0; i < gpioAttributePrefix.size(); ++i) {

    std::size_t dbl_length = 0;
    next_value_idx += gpioAttributePrefix[i].length() + 1;
    if (next_value_idx < len) {
      measured_gpio_values_[i]->SetValue(
          std::stod(&incoming_xml[next_value_idx], &dbl_length));
    } else {
      throw std::invalid_argument(
          "Received XML is not valid for the given degree of freedom");
    }
    next_value_idx += dbl_length; // length of the parsed double
  }

  next_value_idx += kAttributeSuffix.length();
  next_value_idx += kIpocNodePrefix.length();

  if (next_value_idx >= len) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom");
  }

  ipoc_ = std::strtol(&incoming_xml[next_value_idx], &endptr, 0);
  if (errno != 0 && endptr == &incoming_xml[next_value_idx]) {
    throw std::invalid_argument(
        "Received XML is not valid for the given degree of freedom");
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
  AppendToXMLString(kJointPositionsPrefix);
  for (int i = 0; i < dof_; ++i) {
    char double_buffer[kPrecision + 3 + 1 + 1 +
                       1]; // Precision + Digits + Comma + Null + Minus sign
    AppendToXMLString(joint_position_attribute_prefixes_[i]);
    int ret = std::snprintf(double_buffer, sizeof(double_buffer),
                            kJointPositionAttributeFormat.data(),
                            (joint_position_values_[i] -
                             initial_positions_.GetMeasuredPositions()[i]) *
                                (180 / M_PI));
    if (ret <= 0) {
      return std::nullopt;
    }

    AppendToXMLString(double_buffer);
    AppendToXMLString("\"");
  }

  AppendToXMLString(kAttributeSuffix);
  AppendToXMLString(kStopNodePrefix);
  AppendToXMLString(stop_control ? "1" : "0");
  AppendToXMLString(kStopNodeSuffix);
  AppendToXMLString(kGpioPrefix);
  for (size_t i = 0; i < gpioAttributePrefix.size(); i++) {
    AppendToXMLString(gpioAttributePrefix[i]);
    // TODO (Komaromi) Do other value types
    auto value = gpio_values_[i]->GetValue();
    if (value.has_value()) {
      AppendToXMLString(std::to_string(value.value()));
    }
    AppendToXMLString("\"");
  }
  AppendToXMLString(kAttributeSuffix);
  AppendToXMLString(kIpocNodePrefix);
  AppendToXMLString(std::to_string(last_ipoc).data());
  AppendToXMLString(kIpocNodeSuffix);
  AppendToXMLString(kMessageSuffix);

  return xml_string_;
}

void ControlSignal::SetInitialPositions(const MotionState &initial_positions) {
  initial_positions_set_ = true;
  initial_positions_ = initial_positions;
}

} // namespace kuka::external::control::kss
