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

#include <tinyxml2.h>

#include "kuka/external-control-sdk/kss/eki/init_sequence.h"

namespace kuka::external::control::kss::eki {

bool ParseInitMessage(const char* data_to_parse, InitializationData& init_data) {
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLError error = doc.Parse(data_to_parse);
  if (error != tinyxml2::XMLError::XML_SUCCESS)
    return false;

  tinyxml2::XMLElement* root = doc.RootElement();
  if (root == nullptr)
    return false;

  tinyxml2::XMLElement* init_elem = root->FirstChildElement("Init");
  if (init_elem == nullptr)
    return false;

  init_data.semantic_version = init_elem->Attribute("VER");
  init_data.ipoc = std::stol(init_elem->Attribute("IPOC"));
  init_data.num_axes = std::stoi(init_elem->Attribute("NumAxes"));
  init_data.num_external_axes = std::stoi(init_elem->Attribute("NumExternalAxes"));
  init_data.model_name = init_elem->Attribute("Model");

  const int8_t size = init_data.num_axes + init_data.num_external_axes;
  init_data.axis_type.resize(size);
  init_data.ratio_numerator.resize(size);
  init_data.ratio_denominator.resize(size);
  init_data.max_rpm.resize(size);

  tinyxml2::XMLElement *axis = init_elem->FirstChildElement("Axis");

  // A1, A2 ... A6, E1, E2 ... E6 + '\0'
  char ax_i[3];

  // Parse robot axes parameters
  for (size_t i = 0; i < init_data.num_axes; ++i) {
    sprintf(ax_i, "A%ld", i + 1);
    tinyxml2::XMLElement* ax_elem = axis->FirstChildElement(ax_i);
    init_data.axis_type[i] = ax_elem->Attribute("Type");
    init_data.ratio_numerator[i] = std::stoi(ax_elem->Attribute("RatioNum"));
    init_data.ratio_denominator[i] = std::stoi(ax_elem->Attribute("RatioDen"));
    init_data.max_rpm[i] = std::stoi(ax_elem->Attribute("MaxRPM"));
  }

  // Parse extarnal axes parameters
  for (size_t i = 0; i < init_data.num_external_axes; ++i) {
    const size_t actual_idx = i + init_data.num_axes;
    sprintf(ax_i, "E%ld", i + 1);
    tinyxml2::XMLElement* ax_elem = axis->FirstChildElement(ax_i);
    init_data.axis_type[actual_idx] = ax_elem->Attribute("Type");
    init_data.ratio_numerator[actual_idx] = std::stoi(ax_elem->Attribute("RatioNum"));
    init_data.ratio_denominator[actual_idx] = std::stoi(ax_elem->Attribute("RatioDen"));
    init_data.max_rpm[actual_idx] = std::stoi(ax_elem->Attribute("MaxRPM"));
  }

  return true;
}

std::array<uint8_t, 3> ExtractNumbers(const char* version) {
  std::array<uint8_t, 3> numbers;
  char* copy = new char[strlen(version) + 1];
  strcpy(copy, version);

  char* token = strtok(copy, ".");
  for (size_t i = 0; token != nullptr; ++i) {
    numbers[i] = std::stoi(token);
    token = std::strtok(nullptr, ".");
  }

  delete[] copy;
  return numbers;
}

bool CheckSemVerCompatibility(const char* server, const char* client) {
  std::array<uint8_t, 3> server_ver = ExtractNumbers(server);
  std::array<uint8_t, 3> client_ver = ExtractNumbers(client);
  return server_ver[0] == client_ver[0];
}

}  // namespace kuka::external::control::kss::eki
