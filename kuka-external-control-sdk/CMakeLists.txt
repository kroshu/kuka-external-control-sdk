cmake_minimum_required(VERSION 3.13)

project("external-control-sdk")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindProtobuf.cmake)

set(artifact_name ${PROJECT_NAME})

set(common_directory "common")
set(iiqka_directory "iiqka")
set(common_directory "common")
set(utils_directory "utils")
set(proto_api_directory "proto-api")

set(target_name "kuka-external-control-sdk")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE )
endif()

set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/kuka-external-control-sdk)


find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(gRPC REQUIRED grpc++)

set(motion_external_proto_api_path "${CMAKE_CURRENT_LIST_DIR}/iiqka/proto-api/motion-external")
set(motion_services_ecs_proto_api_path "${CMAKE_CURRENT_LIST_DIR}/iiqka/proto-api/motion-services-ecs")

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
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>"
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
  OpenSSL::SSL
  kuka-external-control-sdk-protobuf
)

target_include_directories(${target_name} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${common_directory}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${iiqka_directory}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${utils_directory}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>"
)

target_compile_features(${target_name} INTERFACE cxx_std_17 PRIVATE cxx_std_17)

# Install and export

install(TARGETS kuka-external-control-sdk-protobuf EXPORT kuka-external-control-sdk-protobuf/
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS ${target_name} kuka-external-control-sdk-protobuf EXPORT MyExport
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT MyExport NAMESPACE Kuka:: FILE kuka-external-control-sdkConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${common_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${iiqka_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${iiqka_directory}
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")
