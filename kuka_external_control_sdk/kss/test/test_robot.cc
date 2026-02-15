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

#include <gtest/gtest.h>

#include "kuka/external-control-sdk/kss/robot.h"

using ::testing::Test;

class KSSRobot : public ::testing::Test {
 protected:
  kuka::external::control::kss::Configuration kss_config_;
  std::unique_ptr<kuka::external::control::kss::Robot> robot_;

  KSSRobot(){};

  virtual ~KSSRobot() = default;

  virtual void SetUp() {
    robot_ = std::make_unique<kuka::external::control::kss::Robot>(kss_config_);
  }

  virtual void TearDown() {
    robot_.reset();
  }
};
