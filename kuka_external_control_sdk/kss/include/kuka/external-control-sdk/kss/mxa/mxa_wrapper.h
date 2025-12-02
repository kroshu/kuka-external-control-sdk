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

#ifndef KUKA_EXTERNAL_CONTROL__KSS_MXA_MXA_WRAPPER_H_
#define KUKA_EXTERNAL_CONTROL__KSS_MXA_MXA_WRAPPER_H_

#include "MxAutomationV3_3.h"
#include <array>

namespace kuka::external::control::kss::mxa {

enum class BLOCKSTATE { ACTIVE = -1, DONE = 0, ABORTED = 1, ERROR = 2 };

struct BLOCKRESULT {
  BLOCKRESULT() : block_state(BLOCKSTATE::ACTIVE){};
  BLOCKRESULT(BLOCKSTATE state) : block_state(state){};
  BLOCKRESULT(int err_code)
      : block_state(BLOCKSTATE::ERROR), error_code(err_code){};

  BLOCKSTATE block_state;
  int error_code = 0;
};

class mxAWrapper {
public:
  mxAWrapper() {
    krc_read_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    krc_write_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_init_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_read_status_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_aut_ext_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_auto_start_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_set_override_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_tech_function_m_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    mxa_tech_function_s_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;
    krc_error_.AXISGROUPIDX = DEFAULT_AXISGROUP_ID;

    mxa_tech_function_m_.BOOL_DATA = bool_array_.data();
    mxa_tech_function_m_.INT_DATA = int_array_.data();
    mxa_tech_function_m_.REAL_DATA = real_array_.data();

    mxa_tech_function_s_.BOOL_DATA = bool_array_.data();
    mxa_tech_function_s_.INT_DATA = int_array_.data();
    mxa_tech_function_s_.REAL_DATA = real_array_.data();

    // Set AutExt block values
    mxa_aut_ext_.CONF_MESS = false;
    mxa_aut_ext_.DRIVES_ON = false;
    mxa_aut_ext_.DRIVES_OFF = true;
    mxa_aut_ext_.MOVE_ENABLE = true;
    mxa_aut_ext_.EXT_START = false;
    mxa_aut_ext_.RESET = false;
    mxa_aut_ext_.ENABLE_T1 = false;
    mxa_aut_ext_.ENABLE_T2 = false;
    mxa_aut_ext_.ENABLE_AUT = false;
    mxa_aut_ext_.ENABLE_EXT = true;
  }

  void getmxAOutput(unsigned char *read_buffer) {
    krc_read_.KRC4_INPUT = read_buffer;
    krc_read_.OnCycle();
  }

  void setmxAInput(unsigned char *write_buffer) {
    krc_write_.KRC4_OUTPUT = write_buffer;
    krc_write_.OnCycle();
  }

  int mxACycle() {
    mxa_init_.OnCycle();

    mxa_aut_ext_.OnCycle();

    // Set constant override
    mxa_set_override_.OVERRIDE = 100;
    mxa_set_override_.OnCycle();

    krc_error_.OnCycle();
    return krc_error_.ERRORID;
  }

  // Start robot interpreter of mxA
  BLOCKRESULT startMxAServer() {
    mxa_auto_start_.EXECUTERESET = true;
    mxa_auto_start_.OnCycle();

    if (mxa_auto_start_.ERROR) {
      mxa_auto_start_.EXECUTERESET = false;
      mxa_auto_start_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(mxa_auto_start_.ERRORID));
    } else if (mxa_auto_start_.DISPACTIVE) {
      mxa_auto_start_.EXECUTERESET = false;
      mxa_auto_start_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::DONE));
    }
    return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::ACTIVE));
  }

  // Only works with Techfunction extension
  BLOCKRESULT cancelProgram() {
    mxa_tech_function_s_.TECHFUNCTIONID = 3;
    mxa_tech_function_s_.PARAMETERCOUNT = 1; // must be >= 1, though not used
    mxa_tech_function_s_.BUFFERMODE = 0;
    mxa_tech_function_s_.EXECUTECMD = true;
    mxa_tech_function_s_.OnCycle();

    if (mxa_tech_function_s_.ERROR) {
      mxa_tech_function_s_.EXECUTECMD = false;
      mxa_tech_function_s_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(mxa_tech_function_s_.ERRORID));
    } else if (mxa_tech_function_s_.DONE) {
      mxa_tech_function_s_.EXECUTECMD = false;
      mxa_tech_function_s_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::DONE));
    }
    return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::ACTIVE));
  }

  void resetErrors() {
    krc_error_.MESSAGERESET = true;
    krc_error_.OnCycle();
  }

  // Only works with Techfunction extension
  BLOCKRESULT processRSI(int control_mode, int cycle_time) {
    mxa_tech_function_m_.INT_DATA[1] = control_mode;
    mxa_tech_function_m_.INT_DATA[2] = cycle_time;
    mxa_tech_function_m_.EXECUTECMD = true;
    mxa_tech_function_m_.OnCycle();

    if (mxa_tech_function_m_.ERROR) {
      mxa_tech_function_m_.EXECUTECMD = false;
      mxa_tech_function_m_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(mxa_tech_function_m_.ERRORID));
    } else if (mxa_tech_function_m_.DONE) {
      mxa_tech_function_m_.EXECUTECMD = false;
      mxa_tech_function_m_.OnCycle();
      return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::DONE));
    }
    return BLOCKRESULT(BLOCKSTATE(BLOCKSTATE::ACTIVE));
  }

  bool isServerActive() { return mxa_aut_ext_.PRO_ACT; }

  bool drivesPowered() { return mxa_aut_ext_.PERI_RDY; }

  bool emergencyStop() { return !mxa_aut_ext_.ALARM_STOP; }

  bool guardStop() { return !mxa_aut_ext_.USER_SAFE; }

  bool inMotion() { return mxa_aut_ext_.PRO_MOVE; }

  bool motionPossible() { return mxa_aut_ext_.PRO_ACT; }

  bool robotStopped() { return mxa_aut_ext_.ROB_STOPPED; }

  int getOpMode() {
    if (mxa_aut_ext_.T1) {
      return 1;
    } else if (mxa_aut_ext_.T2) {
      return 2;
    } else if (mxa_aut_ext_.AUT) {
      return 3;
    } else if (mxa_aut_ext_.EXT) {
      return 4;
    } else {
      return 0;
    }
  }

  bool isInitialized() { return mxa_init_.DONE; }

private:
  KRC_READAXISGROUP krc_read_;
  KRC_WRITEAXISGROUP krc_write_;
  KRC_INITIALIZE mxa_init_;

  KRC_READMXASTATUS mxa_read_status_;
  KRC_AUTOMATICEXTERNAL mxa_aut_ext_;
  KRC_AUTOSTART mxa_auto_start_;
  KRC_ERROR krc_error_;
  KRC_SETOVERRIDE mxa_set_override_;
  KRC_TECHFUNCTION mxa_tech_function_m_;
  KRC_TECHFUNCTION mxa_tech_function_s_;

  static constexpr int TECH_FUNC_PARAM_COUNT = 40;
  std::array<int, TECH_FUNC_PARAM_COUNT + 1> int_array_;
  std::array<bool, TECH_FUNC_PARAM_COUNT + 1> bool_array_;
  std::array<float, TECH_FUNC_PARAM_COUNT + 1> real_array_;

  static constexpr int DEFAULT_AXISGROUP_ID = 1;
};
} // namespace kuka::external::control::kss::mxa
#endif // KUKA_EXTERNAL_CONTROL__KSS_MXA_MXA_WRAPPER_H_