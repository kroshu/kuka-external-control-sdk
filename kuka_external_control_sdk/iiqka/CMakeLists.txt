cmake_minimum_required(VERSION 3.13)

project("external-control-sdk")

include(${CMAKE_CURRENT_LIST_DIR}/cmake/FindProtobuf.cmake)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

set(common_directory ${PARENT_DIR}/common)
set(iiqka_directory ${PARENT_DIR}/iiqka)
set(utils_directory ${PARENT_DIR}/utils)
set(proto_api_directory ${iiqka_directory}/proto-api)
set(test_directory ${iiqka_directory}/test)

set(target_name "kuka-external-control-sdk")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(gRPC REQUIRED grpc++)
set(motion_external_proto_api_path "${proto_api_directory}/motion-external")
set(motion_services_ecs_proto_api_path "${proto_api_directory}/motion-services-ecs")

add_library(kuka-external-control-sdk-protobuf STATIC
"${motion_external_proto_api_path}/control_attributes.proto"
"${motion_external_proto_api_path}/utils.proto"
"${motion_external_proto_api_path}/external_control_mode.proto"
"${motion_external_proto_api_path}/control_signal_proxy.proto"
"${motion_external_proto_api_path}/control_signal_internal.proto"
"${motion_external_proto_api_path}/motion_state_internal.proto"
"${motion_services_ecs_proto_api_path}/motion_services_ecs.proto"
"${motion_services_ecs_proto_api_path}/external_header.proto"
"${motion_services_ecs_proto_api_path}/qos_profile_settings.proto"
"${motion_services_ecs_proto_api_path}/control_signal_external.proto"
"${motion_services_ecs_proto_api_path}/motion_state_external.proto")

set(PROTO_BINARY_DIR ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(kuka-external-control-sdk-protobuf PUBLIC  ${gRPC_LIBRARIES}
${PROTOBUF_LIBRARY})

target_include_directories(kuka-external-control-sdk-protobuf PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

protobuf_generate(
    TARGET kuka-external-control-sdk-protobuf
    LANGUAGE cpp
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

protobuf_generate(
    TARGET kuka-external-control-sdk-protobuf
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.hh .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=/usr/bin/grpc_cpp_plugin"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(sources
  ${PROTO_SRCS}
  ${common_directory}/src/status.cc
  ${utils_directory}/src/os-core-udp-communication/subscriber.cc
  ${utils_directory}/src/os-core-udp-communication/requester.cc
  ${utils_directory}/src/os-core-udp-communication/publisher.cc
  ${utils_directory}/src/os-core-udp-communication/replier.cc
  ${utils_directory}/src/os-core-udp-communication/secure_replier.cc
  ${utils_directory}/src/os-core-udp-communication/socket.cc
  ${utils_directory}/src/os-core-udp-communication/secure_socket.cc
  ${iiqka_directory}/src/robot.cc
)

# Build external-control-sdk library

add_library(${target_name} STATIC ${sources})

target_link_libraries(${target_name} PUBLIC
  Threads::Threads
  OpenSSL::SSL
  kuka-external-control-sdk-protobuf
)

target_include_directories(${target_name} PUBLIC
  "$<BUILD_INTERFACE:${common_directory}/include>"
  "$<BUILD_INTERFACE:${iiqka_directory}/include>"
  "$<BUILD_INTERFACE:${proto_api_directory}>"
  "$<BUILD_INTERFACE:${utils_directory}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/kuka/external-control-sdk/iiqka>"
)

target_compile_features(${target_name} INTERFACE cxx_std_17 PRIVATE cxx_std_17)

# Build tests for iiQKA

if(CMAKE_TESTING_ENABLED)
  add_subdirectory(/usr/src/googletest GTest)
  find_package(GTest)
  enable_testing()
  add_executable(
    test_robot
    test/test_robot.cc
    test/test-assets/fake_command_handling_service.cc
  )

  add_executable(
    test_message_builder
    test/test_message_builder.cc
  )

  target_link_libraries(
    test_robot
    GTest::gtest_main
    kuka-external-control-sdk
    GTest::gtest
  )

  target_link_libraries(
    test_message_builder
    GTest::gtest_main
    kuka-external-control-sdk
    GTest::gtest
  )

  target_include_directories(test_robot PUBLIC
    "$<BUILD_INTERFACE:${common_directory}/include>"
    "$<BUILD_INTERFACE:${iiqka_directory}/include>"
    "$<BUILD_INTERFACE:${iiqka_directory}/test>"
  )

  target_include_directories(test_message_builder PUBLIC
  "$<BUILD_INTERFACE:${common_directory}/include>"
  "$<BUILD_INTERFACE:${iiqka_directory}/include>"
  "$<BUILD_INTERFACE:${iiqka_directory}/test>"
)

  target_compile_features(test_robot INTERFACE cxx_std_17 PRIVATE cxx_std_17)
  target_compile_features(test_message_builder INTERFACE cxx_std_17 PRIVATE cxx_std_17)


  include(GoogleTest)
  gtest_discover_tests(test_robot)
  gtest_discover_tests(test_message_builder)
endif()

# Install and export

install(TARGETS ${target_name} kuka-external-control-sdk-protobuf EXPORT SdkExport
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT SdkExport NAMESPACE Kuka:: FILE kuka-external-control-sdkTargets.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/kuka-external-control-sdkConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk
        ) 

install(DIRECTORY ${iiqka_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/proto-api
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kuka/external-control-sdk/iiqka
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

if (NOT ${PARENT_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    install(DIRECTORY ${common_directory}/include/ ${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")
endif()