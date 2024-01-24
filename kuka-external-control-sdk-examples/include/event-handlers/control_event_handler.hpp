#ifndef EXTERNAL_CONTROL_SDK_EXAMPLE__CONTROL_EVENT_HANDLER_H_
#define EXTERNAL_CONTROL_SDK_EXAMPLE__CONTROL_EVENT_HANDLER_H_

#include <iostream>

#include "kuka/external-control-sdk/common/irobot.h"

namespace external_control_sdk_example {

class ControlEventHandler : public kuka::external::control::EventHandler {
  virtual void OnSampling() override { std::cout << "Sampling started\n"; };
  virtual void OnControlModeSwitch(const std::string& reason) override {
    std::cout << "Control mode switch, reason: " << reason << std::endl;
  };
  virtual void OnStopped(const std::string& reason) override {
    std::cout << "Stopped, reason: " << reason << std::endl;
  };
  virtual void OnError(const std::string& reason) override {
    std::cout << "Error occured, reason: " << reason << std::endl;
  };
};

}  // namespace external_control_sdk_example

#endif  // EXTERNAL_CONTROL_SDK_EXAMPLE__CONTROL_EVENT_HANDLER_H_
