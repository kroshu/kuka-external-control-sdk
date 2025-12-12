#ifndef KUKA_EXTERNAL_CONTROL__KSS_EKI_INITIALIZATION_DATA_H_
#define KUKA_EXTERNAL_CONTROL__KSS_EKI_INITIALIZATION_DATA_H_

#include <string>

#include <tinyxml2.h>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/initialization_data.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss::eki {

struct EKIInitializationData: public kuka::external::control::kss::InitializationData
{
  bool Parse(const char* data_to_parse) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse(data_to_parse);
    if (error != tinyxml2::XMLError::XML_SUCCESS) {
      return false;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (root == nullptr) {
      return false;
    }

    tinyxml2::XMLElement* init_elem = root->FirstChildElement("Init");
    if (init_elem == nullptr) {
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
#endif  // KUKA_EXTERNAL_CONTROL__KSS_EKI_INITIALIZATION_DATA_H_
