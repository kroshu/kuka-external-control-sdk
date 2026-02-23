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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__KSS__EKI__INITIALIZATION_DATA_H_
#define KUKA__EXTERNAL_CONTROL_SDK__KSS__EKI__INITIALIZATION_DATA_H_

#include <tinyxml2.h>

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"
#include "kuka/external-control-sdk/kss/initialization_data.h"

namespace kuka::external::control::kss::eki
{

struct EKIInitializationData : public kuka::external::control::kss::InitializationData
{
  bool Parse(const char * data_to_parse)
  {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse(data_to_parse);
    if (error != tinyxml2::XMLError::XML_SUCCESS)
    {
      return false;
    }

    tinyxml2::XMLElement * root = doc.RootElement();
    if (root == nullptr)
    {
      return false;
    }

    tinyxml2::XMLElement * init_elem = root->FirstChildElement("Init");
    if (init_elem == nullptr)
    {
      return false;
    }

    semantic_version = init_elem->Attribute("VER");
    num_axes = std::stoi(init_elem->Attribute("NumAxes"));
    num_external_axes = std::stoi(init_elem->Attribute("NumExternalAxes"));
    model_name = init_elem->Attribute("Model");

    const std::string rob_ver = init_elem->Attribute("RobVer");
    // The hardware and software versions are separated by a slash
    const size_t sep_idx = rob_ver.find('/');
    hw_version = rob_ver.substr(0, sep_idx);
    sw_version = rob_ver.substr(sep_idx + 1);

    return true;
  }

  std::string semantic_version;
  std::string model_name;
  std::string hw_version;
  std::string sw_version;
};

}  // namespace kuka::external::control::kss::eki
#endif  // KUKA__EXTERNAL_CONTROL_SDK__KSS__EKI__INITIALIZATION_DATA_H_
