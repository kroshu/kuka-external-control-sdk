#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_INITIALIZATION_DATA_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_INITIALIZATION_DATA_H_

#include <string>

#include "kuka/external-control-sdk/common/irobot.h"
#include "kuka/external-control-sdk/kss/configuration.h"

namespace kuka::external::control::kss::mxa {

struct InitializationData {
  InitializationData(uint8_t num_ax, uint8_t num_ext_ax)
      : num_axes(num_ax), num_external_axes(num_ext_ax) {}

  uint8_t GetTotalAxisCount() const { return num_axes + num_external_axes; }

  uint8_t num_axes = 0;
  uint8_t num_external_axes = 0;
};

class IEventHandlerExtension {
public:
  virtual void OnConnected(const InitializationData &init_data) = 0;
};


} // namespace kuka::external::control::kss::mxa
#endif // KUKA_EXTERNAL_CONTROL__KSS_MXA_INITIALIZATION_DATA_H_
