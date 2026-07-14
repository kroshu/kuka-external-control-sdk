// Copyright 2023 KUKA Hungaria Kft.
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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__KSS__CONFIGURATION_H_
#define KUKA__EXTERNAL_CONTROL_SDK__KSS__CONFIGURATION_H_

#include <array>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include "kuka/external-control-sdk/common/irobot.h"

namespace kuka::external::control::kss
{

// RSI cycle time
enum class CycleTime : uint8_t
{
  UNSPECIFIED = 0,
  RSI_4MS = 1,
  RSI_12MS = 2
};

// Convert CycleTime enum to human-readable string
inline const char * CycleTimeToString(CycleTime cycle_time)
{
  switch (cycle_time)
  {
    case CycleTime::RSI_4MS:
      return "4ms";
    case CycleTime::RSI_12MS:
      return "12ms";
    default:
      return "unspecified";
  }
}

struct GPIOConfiguration
{
  // Name of the GPIO
  std::string name;
  //  Type of the GPIO value (BOOL, DOUBLE, LONG)
  GPIOValueType value_type = GPIOValueType::UNSPECIFIED;
  // (Optional) Initial value for the GPIO
  // TODO(Komaromi): Make it type specific
  double initial_value = 0;
  // (Optional) Enable limits for the GPIO value
  // If true, min_value and max_value must be set
  // If false, min_value and max_value are ignored
  bool enable_limits = false;
  // (Optional) Minimum value for the GPIO
  double min_value = 0;
  // (Optional) Maximum value for the GPIO
  double max_value = 0;
};

struct JointConfiguration
{
  enum class Type : uint8_t
  {
    UNKNOWN = 0,
    REVOLUTE = 1,
    PRISMATIC = 2
  };

  JointConfiguration(const std::string & n, Type t, bool e) : name(n), type(t), is_external(e) {}

  std::string name;
  Type type = Type::REVOLUTE;
  bool is_external = false;

  static constexpr Type ToType(std::string_view s)
  {
    if (s == "revolute")
    {
      return Type::REVOLUTE;
    }
    if (s == "prismatic")
    {
      return Type::PRISMATIC;
    }
    return Type::UNKNOWN;
  }

  static constexpr std::string_view TypeToString(Type t)
  {
    switch (t)
    {
      case Type::REVOLUTE:
        return "revolute";
      case Type::PRISMATIC:
        return "prismatic";
      default:
        return "unknown";
    }
  }
};

enum class MotionStateSignalType : uint8_t
{
  POSITION = 0,
  VELOCITY = 1,
  TORQUE = 2
};

constexpr const char * MotionStateSignalTypeToString(MotionStateSignalType signal_type)
{
  switch (signal_type)
  {
    case MotionStateSignalType::POSITION:
      return "position";
    case MotionStateSignalType::VELOCITY:
      return "velocity";
    case MotionStateSignalType::TORQUE:
      return "torque";
    default:
      return "unknown";
  }
}

struct MotionStateJointFieldConfiguration
{
  std::string joint_identifier;
  MotionStateSignalType signal_type = MotionStateSignalType::POSITION;
  std::string xml_element;
  std::string xml_attribute;
};

struct MotionStateCartesianFieldConfiguration
{
  bool enabled = true;
  std::string xml_element = "RIst";
  std::array<std::string, 6> xml_attributes = {"X", "Y", "Z", "A", "B", "C"};
};

enum class MotionStateXmlFieldType : uint8_t
{
  CARTESIAN = 0,
  JOINT = 1,
  DELAY = 2,
  GPIO = 3,
  IPOC = 4
};

struct MotionStateXmlOrderEntry
{
  MotionStateXmlFieldType field_type = MotionStateXmlFieldType::JOINT;
  std::size_t index = 0;
};

struct MotionStateXmlConfiguration
{
  std::vector<MotionStateJointFieldConfiguration> joint_fields;
  MotionStateCartesianFieldConfiguration cartesian;
  std::string gpio_xml_element = "GPIO";
  std::vector<std::string> gpio_xml_attributes;
  std::vector<MotionStateXmlOrderEntry> field_order;
};

// Field types for outgoing RSI control signal messages
enum class ControlSignalXmlFieldType : uint8_t
{
  JOINT = 0,      // internal joint positions element
  EXT_JOINT = 1,  // external joint positions element
  GPIO = 2,       // GPIO command element
  IPOC = 3        // IPOC element
};

struct ControlSignalXmlOrderEntry
{
  ControlSignalXmlFieldType field_type = ControlSignalXmlFieldType::JOINT;
  std::size_t index = 0;
};

struct ControlSignalXmlConfiguration
{
  // XML element name for internal joint positions (legacy default: "AK")
  std::string joint_xml_element = "AK";

  // Attribute names for internal joint positions.
  // If empty, auto-generated as "A1", "A2", ... up to the number of internal axes.
  std::vector<std::string> joint_xml_attributes;

  // XML element name for external joint positions (legacy default: "EK")
  std::string ext_joint_xml_element = "EK";

  // Attribute names for external joint positions.
  // If empty, auto-generated as "E1", "E2", ... up to the number of external axes.
  std::vector<std::string> ext_joint_xml_attributes;

  // XML element name for GPIO command values (legacy default: "GPIO")
  std::string gpio_xml_element = "GPIO";

  // Explicit field ordering for the transmitted message.
  // If empty, the default legacy order is used:
  //   JOINT, EXT_JOINT (if external axes exist), GPIO (if GPIO commands exist), IPOC
  std::vector<ControlSignalXmlOrderEntry> field_order;
};

struct Configuration
{
  // IP address of the KONI interface on the KRC-5.
  std::string kli_ip_address;

  // IP address of the client application for real-time communication.
  std::string client_ip = "0.0.0.0";

  // Port number of the client application for real-time communication via UDP.
  uint16_t client_port = 59152;

  // Port number of the client application for receiving mxAutomation messages via UDP.
  uint16_t mxa_client_port = 1337;

  // Port number of the client application for receiving and sending EKI messages via TCP.
  uint16_t eki_client_port = 54601;

  // Degree of freedom.
  std::size_t dof = 6;

  // Joint configuration
  std::vector<JointConfiguration> joint_configs;

  // GPIO states
  std::vector<GPIOConfiguration> gpio_state_configs;

  // GPIO commands
  std::vector<GPIOConfiguration> gpio_command_configs;

  // Optional XML layout used for parsing RSI state messages. If not set, the legacy
  // RSI layout (<RIst><AIPos><EIPos><Delay><GPIO><IPOC>) is used.
  std::optional<MotionStateXmlConfiguration> motion_state_xml_config;

  // Optional XML layout for transmitted RSI control signal messages. If not set, the legacy
  // RSI layout (<Stop><AK ...><EK ...><GPIO ...><IPOC>) is used.
  std::optional<ControlSignalXmlConfiguration> control_signal_xml_config;

  // The control mode to begin external control in.
  // At the present, the following modes are supported:
  // 1 - Joint position control
  ControlMode initial_control_mode = ControlMode::UNSPECIFIED;

  // This value is ignored if plain RSI is used
  CycleTime cycle_time = CycleTime::RSI_12MS;

  enum class InstalledInterface
  {
    UNSPECIFIED = 0,
    MXA_RSI = 1,
    EKI_RSI = 2,
    RSI_ONLY = 3
  };

  // The interface installed on the KSS robot
  InstalledInterface installed_interface = InstalledInterface::RSI_ONLY;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA__EXTERNAL_CONTROL_SDK__KSS__CONFIGURATION_H_
