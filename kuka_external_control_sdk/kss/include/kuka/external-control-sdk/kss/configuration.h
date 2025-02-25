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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_

#include <chrono>
#include <string>

#include "kuka/external-control-sdk/common/irobot.h"

namespace kuka::external::control::kss {

struct Configuration {
  // IP address of the KONI interface on the KRC-5.
  std::string kli_ip_address;
  // IP address of the client machine.
  std::string client_ip_address;

  // Degree of freedom.
  std::size_t dof = 6;

  /** The control mode to begin external control in.
   *  At the present, the following modes are supported:
   *  1 - Joint position control
   *  5? - cart pos
   */
  ControlMode initial_control_mode = ControlMode::UNSPECIFIED;

  // Ports open on the KRC to enable external control. These values are fixed.
  const unsigned short eki_port = 54600;
  const unsigned short client_port = 59152;

  const char* control_signal_default_format_str_ =
      "<Sen Type=\"KROSHU\"><AK A1=\"%lf\" A2=\"%lf\" A3=\"%lf\" A4=\"%lf\" A5=\"%lf\" A6=\"%lf\"/><Stop>%d</Stop><IPOC>%d</IPOC></Sen>";

  const char* motion_state_default_format_str_ =
      "<Rob Type=\"KUKA\"><RIst X=\"%*f\" Y=\"%*f\" Z=\"%*f\" A=\"%*f\" B=\"%*f\" C=\"%*f\"/><RSol X=\"%*f\" Y=\"%*f\" Z=\"%*f\" A=\"%*f\" B=\"%*f\" C=\"%*f\"/><AIPos A1=\"%lf\" A2=\"%lf\" A3=\"%lf\" A4=\"%lf\" A5=\"%lf\" A6=\"%lf\"/><ASPos A1=\"%*f\" A2=\"%*f\" A3=\"%*f\" A4=\"%*f\" A5=\"%*f\" A6=\"%*f\"/><Delay D=\"%*d\"/><IPOC>%d</IPOC></Rob>";
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_CONFIGURATION_H_
