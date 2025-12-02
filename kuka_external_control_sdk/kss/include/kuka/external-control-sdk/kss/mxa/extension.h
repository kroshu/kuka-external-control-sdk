#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_EXTENSION_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_EXTENSION_H_

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss::mxa {

struct InitializationData {

  // TODO: fill init data from mxA telegram

  uint8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }

  std::string semantic_version;
  uint8_t num_axes;
  uint8_t num_external_axes;
  std::string model_name;
  std::string hw_version;
  std::string sw_version;
};

class IEventHandlerExtension {
public:
  virtual void OnConnected(const InitializationData &init_data) = 0;
};

class IStatusUpdateHandler {
public:
  virtual void OnStatusUpdateReceived(const StatusUpdate &response) = 0;
};

} // namespace kuka::external::control::kss::mxa
#endif // KUKA_EXTERNAL_CONTROL__KSS_EKI_EXTENSION_H_
