#ifndef KUKA_EXTERNAL_CONTROL__KSS_EXTENSION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_EXTENSION_H_

#include <tinyxml2.h>

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss {

struct InitializationData {
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

  uint8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }

  std::string semantic_version;
  uint8_t num_axes;
  uint8_t num_external_axes;
  std::string model_name;
  std::string hw_version;
  std::string sw_version;
};

struct StatusUpdate {
  StatusUpdate() { Reset(); }

  void Reset() {
    control_mode_ = ControlMode::UNSPECIFIED;
    cycle_time_ = CycleTime::UNSPECIFIED;
    drives_powered_ = false;
    emergency_stop_ = false;
    guard_stop_ = false;
    in_motion_ = false;
    motion_possible_ = false;
    operation_mode_ = OperationMode::UNSPECIFIED;
    robot_stopped_ = false;
  }

  ControlMode control_mode_;
  CycleTime cycle_time_;
  bool drives_powered_;
  bool emergency_stop_;
  bool guard_stop_;
  bool in_motion_;
  bool motion_possible_;
  OperationMode operation_mode_;
  bool robot_stopped_;
};

class IEventHandlerExtension {
 public:
  virtual void OnConnected(const InitializationData& init_data) = 0;
};

class IStatusUpdateHandler {
 public:
  virtual void OnStatusUpdateReceived(const StatusUpdate& response) = 0;
};

}  // namespace kuka::external::control::kss

#endif  // KUKA_EXTERNAL_CONTROL__KSS_EXTENSION_H_
