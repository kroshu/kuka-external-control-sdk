cmake_minimum_required(VERSION 3.13)

project("kuka-external-control-examples")

# Project dependencies
list(APPEND CMAKE_PREFIX_PATH "~/.local/lib/cmake")

find_package(kuka-external-control-sdk CONFIG REQUIRED)

# Monitoring example
set(monitoring-sources
  src/monitoring_example.cc
)

set(monitoring-artifact_name monitoring-example)
add_executable(${monitoring-artifact_name} ${monitoring-sources})
target_compile_features(${monitoring-artifact_name} INTERFACE cxx_std_20 PRIVATE cxx_std_20)

target_link_libraries(${monitoring-artifact_name} PUBLIC
  Kuka::kuka-external-control-sdk
)
target_include_directories(${monitoring-artifact_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

# Control example
set(control-sources
  src/control_example.cc
)

set(control-artifact_name control-example)
add_executable(${control-artifact_name} ${control-sources})
target_compile_features(${control-artifact_name} INTERFACE cxx_std_20 PRIVATE cxx_std_20)

target_link_libraries(${control-artifact_name} PUBLIC
Kuka::kuka-external-control-sdk
)

target_include_directories(${control-artifact_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

