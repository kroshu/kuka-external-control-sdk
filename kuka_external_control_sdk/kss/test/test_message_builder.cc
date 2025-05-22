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

#include <cmath>


#include "kuka/external-control-sdk/kss/message_builder.h"

using ::testing::Test;

class KSSControlSignal : public ::testing::Test {
 protected:
  virtual ~KSSControlSignal() = default;

  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

class KSSMotionState : public ::testing::Test {
 protected:
  virtual ~KSSMotionState() = default;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(KSSMotionState, TestZeroInit4Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[0], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[1], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[2], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.00);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[0], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[1], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[2], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[3], 0.00);

    EXPECT_EQ(initial_motion_state.GetDelay(), 15);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestZeroInit9Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(9);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\" A7=\"0.00000\" A8=\"0.00000\" A9=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[0], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[1], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[2], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.00);

    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[0], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[1], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[2], 0.00);
    EXPECT_EQ(initial_motion_state.GetMeasuredPositions()[3], 0.00);

    EXPECT_EQ(initial_motion_state.GetDelay(), 15);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
} 

TEST_F(KSSMotionState, TestZeroInit10Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(10);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\" A7=\"0.00000\" A8=\"0.00000\" A9=\"0.00000\" A10=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    for (auto k : initial_motion_state.GetMeasuredPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    EXPECT_EQ(initial_motion_state.GetDelay(), 15);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestZeroInit11Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(11);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\" A7=\"0.00000\" A8=\"0.00000\" A9=\"0.00000\" A10=\"0.00000\" A11=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    for (auto k : initial_motion_state.GetMeasuredPositions()) {
      EXPECT_EQ(k, 0.0);
    }
    
    EXPECT_EQ(initial_motion_state.GetDelay(), 15);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestZeroInit0Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(0);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos \"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";

    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);

    for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    for (auto k : initial_motion_state.GetMeasuredPositions()) {
      EXPECT_TRUE(std::isnan(k));
    }
}

TEST_F(KSSMotionState, TestInit1Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(1);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"2.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 0.034906, 0.02);
}


TEST_F(KSSMotionState, TestInitJointPositions6Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"5.32000\" A2=\"6.4\" A3=\"111.30000\" A4=\"12.20000\" A5=\"0.00000\" A6=\"12.50000\"/><Delay D=\"0\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 0.092851, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[1], 0.1117010, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[2], 1.9425514, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[3], 0.21331763, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[4], 0, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[5], 0.218166156, 0.002);

    EXPECT_EQ(initial_motion_state.GetDelay(), 0);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInitCartesianPositions6Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" C=\"12.50000\"/><AIPos A1=\"0.000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><Delay D=\"8\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    for (auto k : initial_motion_state.GetMeasuredPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[0], 5.32, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[1], 6.4, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[2], 111.3, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.21293, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[4], 0.0, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[5], 0.218166, 0.002);

    EXPECT_EQ(initial_motion_state.GetDelay(), 8);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestFillEverything6Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"5.32000\" Y=\"6.4\" Z=\"111.30000\" A=\"12.20000\" B=\"0.00000\" C=\"12.50000\"/><AIPos A1=\"8.2\" A2=\"3.3\" A3=\"111.67\" A4=\"12.22220\" A5=\"-35.20000\" A6=\"-12.50000\"/><Delay D=\"11\"/><IPOC>357</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);

    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[0], 5.32, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[1], 6.4, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[2], 111.3, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[3], 0.21293, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[4], 0.0, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredCartesianPositions()[5], 0.218166, 0.002);

    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[0], 0.14311699, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[1], 0.0575958, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[2], 1.9490091, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[3], 0.213317, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[4], -0.614355, 0.002);
    EXPECT_NEAR(initial_motion_state.GetMeasuredPositions()[5], -0.218166, 0.002);

    EXPECT_EQ(initial_motion_state.GetDelay(), 11);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 357);
}

TEST_F(KSSMotionState, TestInvalidIpoc) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>TTTT</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);

    for (auto k : initial_motion_state.GetMeasuredCartesianPositions()) {
      EXPECT_EQ(k, 0.0);
    }

    for (auto k : initial_motion_state.GetMeasuredPositions()) {
      EXPECT_EQ(k, 0.0);
    }
    EXPECT_EQ(initial_motion_state.GetDelay(), 15);
    EXPECT_EQ(initial_motion_state.GetIpoc(), 0);
}

TEST_F(KSSMotionState, TestInvalidDelay) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"HHH\"/><IPOC>0</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestLastPositionInvalid) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"asdfggdfs\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestFirstPositionInvalid) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"bbbba\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestXInvalid) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"Gggggg\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestCInvalid) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"TTTTTTTTT\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>TTTT</IPOC></Rob>";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestEntireXMLInvalid) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "I'm not a valid XML";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestEmptyString) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "";
    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}

TEST_F(KSSMotionState, TestNullptr) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    EXPECT_THROW(initial_motion_state.CreateFromXML(nullptr), std::invalid_argument);
}

TEST_F(KSSMotionState, TestWholeStringIsNumbers) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";

    EXPECT_THROW(initial_motion_state.CreateFromXML(rsi_xml), std::invalid_argument);
}


TEST_F(KSSControlSignal, TestZeroInit6Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(6, initial_motion_state);

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\" A5=\"0.000000\" A6=\"0.000000\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestZeroInit4Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(4, initial_motion_state);

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"0.000000\" A2=\"0.000000\" A3=\"0.000000\" A4=\"0.000000\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestZeroInit0Dof) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);    
    
    kuka::external::control::kss::ControlSignal control_signal(0, initial_motion_state);

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestInitialMotionStateHasSmallerDof) {
    kuka::external::control::kss::MotionState initial_motion_state(3);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(4, initial_motion_state);

    std::vector<double> values = {3.4, 3.4, 3.4, 3.4};
    control_signal.AddJointPositionValues(values.begin(), values.end());
    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"194.805650\" A2=\"194.805650\" A3=\"194.805650\" A4=\"194.805650\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}


TEST_F(KSSControlSignal, TestFillEverything) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"1.00000\" A2=\"2.00000\" A3=\"3.00000\" A4=\"4.00000\" A5=\"5.00000\" A6=\"6.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(6, initial_motion_state);

    std::vector<double> values = {3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
    control_signal.AddJointPositionValues(values.begin(), values.end());
    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"193.805650\" A2=\"192.805650\" A3=\"191.805650\" A4=\"190.805650\" A5=\"189.805650\" A6=\"188.805650\"/><Stop>1</Stop><IPOC>543265442</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(543265442, true).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestInitWithDifferentValues) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"194.80565\" A2=\"200.535228\" A3=\"206.264806\" A4=\"211.994384\" A5=\"217.723962\" A6=\"223.45354\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(6, initial_motion_state);

    std::vector<double> values = {3.4, 3.4, 3.4, 3.4, 3.4, 3.4};
    control_signal.AddJointPositionValues(values.begin(), values.end());
    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"0.000000\" A2=\"-5.729578\" A3=\"-11.459156\" A4=\"-17.188734\" A5=\"-22.918312\" A6=\"-28.647890\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0, false).value().data(), expected_xml);
}
/* TODO: Rethink these test cases
TEST_F(KSSControlSignal, TestInitWithHighPrecision) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(6, initial_motion_state);
    control_signal.AddJointPositionValues({183.412344666443214313, 183.512344666443214313, 183.612344666443214313, 183.712344666443214313, 183.912344666443214313, 183.112344966443214313});

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"183.412345\" A2=\"183.512345\" A3=\"183.612345\" A4=\"183.712345\" A5=\"183.912345\" A6=\"183.112345\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0, false).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestInitWithHugeDoubles) {
    kuka::external::control::kss::MotionState initial_motion_state(6);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\" A5=\"0.00000\" A6=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(6, initial_motion_state);
    control_signal.AddJointPositionValues({std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max()});

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"17976931348\" A2=\"17976931348\" A3=\"17976931348\" A4=\"17976931348\" A5=\"17976931348\" A6=\"17976931348\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0, false).value().data(), expected_xml);
}
*/

/* Later, when we can generate format strings
TEST_F(KSSControlSignal, TestControlSignalAttemptOverflow1500Dof) {
}
*/

TEST_F(KSSControlSignal, AddPositionsMultipleTimes) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"15\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    kuka::external::control::kss::ControlSignal control_signal(4, initial_motion_state);
    
    std::vector<double> values1 = {2.0, 3.2, 4.0, 5.00000};
    control_signal.AddJointPositionValues(values1.begin(), values1.end());
    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"114.591559\" A2=\"183.346494\" A3=\"229.183118\" A4=\"286.478898\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);

    std::vector<double> values2 = {1.9, 3.1, 4.006, 5.0};
    control_signal.AddJointPositionValues(values2.begin(), values2.end());

    expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"108.861981\" A2=\"177.616916\" A3=\"229.526893\" A4=\"286.478898\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";

    // Return relative positions after the first Get
    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
      
      
    std::vector<double> values3 = {1.0, 3.4, 4.0, -5.00000};
    control_signal.AddJointPositionValues(values3.begin(), values3.end());
    expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"57.295780\" A2=\"194.805650\" A3=\"229.183118\" A4=\"-286.478898\"/><Stop>0</Stop><IPOC>1</IPOC></Sen>";

    EXPECT_STREQ(control_signal.CreateXMLString(1).value().data(), expected_xml);
}

TEST_F(KSSControlSignal, TestAddPositionsTwice) {
    kuka::external::control::kss::MotionState initial_motion_state(4);
    const char* rsi_xml = "<Rob Type=\"KUKA\"><RIst X=\"0.00000\" Y=\"0.00000\" Z=\"0.00000\" A=\"0.00000\" B=\"0.00000\" C=\"0.00000\"/><AIPos A1=\"0.00000\" A2=\"0.00000\" A3=\"0.00000\" A4=\"0.00000\"/><Delay D=\"0\"/><IPOC>0</IPOC></Rob>";
    initial_motion_state.CreateFromXML(rsi_xml);
    
    kuka::external::control::kss::ControlSignal control_signal(4, initial_motion_state);
    
    std::vector<double> values1 = {2.0, 3.2, 4.000, 5.00000};
    std::vector<double> values2 = {2.8, 3.6, 4.120, 5.3};

    control_signal.AddJointPositionValues(values1.begin(), values1.end());
    control_signal.AddJointPositionValues(values2.begin(), values2.end());

    const char* expected_xml =
      "<Sen Type=\"KROSHU\"><AK A1=\"160.428183\" A2=\"206.264806\" A3=\"236.058612\" A4=\"303.667631\"/><Stop>0</Stop><IPOC>0</IPOC></Sen>";
    EXPECT_STREQ(control_signal.CreateXMLString(0).value().data(), expected_xml);
}