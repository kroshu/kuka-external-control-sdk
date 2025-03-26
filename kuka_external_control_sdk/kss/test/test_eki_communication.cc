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

#include <memory>

#include <gtest/gtest.h>

#include "kuka/external-control-sdk/kss/eki/init_sequence.h"

using namespace kuka::external::control;

TEST(EkiCommunication, ParseInitializationDataAndFail) {
  InitializationData init_data;
  const char* xml_data = "";
  ASSERT_FALSE(kss::eki::ParseInitMessage(xml_data, init_data));
}

TEST(EkiCommunication, ParseInitializationDataAndSucceed) {
  InitializationData init_data;
  const char* xml_data = "<Robot><Common><Event EventID=\"6\" Message=\"1\"></Event><Status Mode=\"1\" ControlMode=\"1\" EStop=\"1\" ErrorCode=\"1\"></Status></Common><Init VER=\"1.0.0\" IPOC=\"0\" NumAxes=\"6\" NumExternalAxes=\"6\" Model=\"#SOME ROBOT MODEL\" RobVer=\"V0.0.0/KUKAx.x\"><Axis><A1 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A1><A2 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A2><A3 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A3><A4 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A4><A5 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A5><A6 Type=\"ROTATIONAL\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></A6><E1 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E1><E2 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E2><E3 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E3><E4 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E4><E5 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E5><E6 Type=\"LINEAR\" RatioNum=\"1\" RatioDen=\"1\" MaxRPM=\"1\"></E6></Axis></Init></Robot>";
  ASSERT_TRUE(kss::eki::ParseInitMessage(xml_data, init_data));

  ASSERT_EQ(init_data.semantic_version, "1.0.0");
  ASSERT_EQ(init_data.ipoc, 0);
  ASSERT_EQ(init_data.num_axes, 6);
  ASSERT_EQ(init_data.num_external_axes, 6);
  ASSERT_EQ(init_data.model_name, "#SOME ROBOT MODEL");
  ASSERT_EQ(init_data.hw_version, "V0.0.0");
  ASSERT_EQ(init_data.sw_version, "KUKAx.x");

  for (std::size_t i = 0; i < init_data.num_axes; ++i)
    ASSERT_EQ(init_data.axis_type[i], AxisType::ROTATIONAL);

  for (std::size_t i = init_data.num_axes; i < init_data.GetTotalAxisCount(); ++i)
    ASSERT_EQ(init_data.axis_type[i], AxisType::LINEAR);

  for (int16_t num : init_data.ratio_numerator)
    ASSERT_EQ(num, 1);

  for (int16_t den : init_data.ratio_denominator)
    ASSERT_EQ(den, 1);

  for (int16_t rpm : init_data.max_rpm)
    ASSERT_EQ(rpm, 1);
}

TEST(EkiCommunication, CheckSemanticVersionCompatibilityAndFail) {
  const char* server = "2.0.0";
  const char* client = "1.0.0";
  ASSERT_FALSE(kss::eki::CheckSemVerCompatibility(server, client));
}

TEST(EkiCommunication, CheckSemanticVersionCompatibilityAndSucceed) {
  const char* server = "2.0.0";
  const char* client = "2.2.4";
  ASSERT_TRUE(kss::eki::CheckSemVerCompatibility(server, client));
}
