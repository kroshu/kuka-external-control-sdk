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

#include <limits>
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

    const char * semantic_version_attr = init_elem->Attribute("VER");
    const char * model_attr = init_elem->Attribute("Model");
    const char * rob_ver_attr = init_elem->Attribute("RobVer");
    if (semantic_version_attr == nullptr || model_attr == nullptr || rob_ver_attr == nullptr)
    {
      return false;
    }

    unsigned num_axes_attr = 0;
    unsigned num_external_axes_attr = 0;
    error = init_elem->QueryUnsignedAttribute("NumAxes", &num_axes_attr);
    if (error != tinyxml2::XML_SUCCESS || num_axes_attr > std::numeric_limits<uint8_t>::max())
    {
      return false;
    }
    error = init_elem->QueryUnsignedAttribute("NumExternalAxes", &num_external_axes_attr);
    if (
      error != tinyxml2::XML_SUCCESS ||
      num_external_axes_attr > std::numeric_limits<uint8_t>::max())
    {
      return false;
    }

    semantic_version = semantic_version_attr;
    num_axes = static_cast<uint8_t>(num_axes_attr);
    num_external_axes = static_cast<uint8_t>(num_external_axes_attr);
    model_name = model_attr;

    const std::string rob_ver = rob_ver_attr;
    // The hardware and software versions are separated by a slash
    const size_t sep_idx = rob_ver.find('/');
    if (sep_idx == std::string::npos)
    {
      return false;
    }
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
