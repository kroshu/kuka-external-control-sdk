cmake_minimum_required(VERSION 3.13)

project(${DEBIAN_PROJECT_NAME}
  VERSION ${DEBIAN_PROJECT_VERSION}
)

# Project dependencies
find_library(ROX_EXTERNAL_CONTROL_SDK kuka-external-control-sdk PATHS "~/.local/lib" REQUIRED)
find_library(ROX_EXTERNAL_CONTROL_SDK_PROTOBUF kuka-external-control-sdk-protobuf PATHS "~/.local/lib" REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(gRPC REQUIRED grpc++)

link_directories("~/.local/lib")

# Monitoring example
set(monitoring-sources
  src/monitoring_example.cc
)

set(monitoring-artifact_name monitoring-example)
add_executable(${monitoring-artifact_name} ${monitoring-sources})
target_compile_features(${monitoring-artifact_name} INTERFACE cxx_std_20 PRIVATE cxx_std_20)

target_link_libraries(${monitoring-artifact_name}
  "${ROX_EXTERNAL_CONTROL_SDK}"
  ${gRPC_LIBRARIES}
  "${ROX_EXTERNAL_CONTROL_SDK_PROTOBUF}"
)
target_include_directories(${monitoring-artifact_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
      "~/.local/include"
)

install(
    TARGETS ${monitoring-artifact_name}
    CONFIGURATIONS RELEASE DEBUG
    EXPORT ${monitoring-artifact_name}-target
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Control example
set(control-sources
  src/control_example.cc
)

set(control-artifact_name control-example)
add_executable(${control-artifact_name} ${control-sources})
target_compile_features(${control-artifact_name} INTERFACE cxx_std_20 PRIVATE cxx_std_20)

target_link_libraries(${control-artifact_name}
  "${ROX_EXTERNAL_CONTROL_SDK}"
  ${gRPC_LIBRARIES}
  "${ROX_EXTERNAL_CONTROL_SDK_PROTOBUF}"
)

target_include_directories(${control-artifact_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
      "~/.local/include"
)

install(
    TARGETS ${control-artifact_name}
    CONFIGURATIONS RELEASE DEBUG
    EXPORT ${control-artifact_name}-target
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
