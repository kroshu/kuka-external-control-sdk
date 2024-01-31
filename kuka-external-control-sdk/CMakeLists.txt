cmake_minimum_required(VERSION 3.13)

project("external-control-sdk")

set(artifact_name ${PROJECT_NAME})

set(common_directory "common")
set(iiqka_directory "iiqka")

set(utils_directory "utils")
set(proto_api_directory "proto-api")
set(target_name "kuka-external-control-sdk")
set(CMAKE_INSTALL_INCLUDEDIR "/usr/include")

find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(gRPC REQUIRED grpc++)

set(motion_external_proto_api_path "${CMAKE_CURRENT_LIST_DIR}/iiqka/proto-api/motion-external")
set(motion_services_ecs_proto_api_path "${CMAKE_CURRENT_LIST_DIR}/iiqka/proto-api/motion-services-ecs")

add_library(kuka-external-control-sdk-protobuf SHARED
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

target_link_libraries(kuka-external-control-sdk-protobuf PUBLIC protobuf::libprotobuf grpc++)

target_include_directories(kuka-external-control-sdk-protobuf PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")

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
  ${common_directory}/src/operation_status.cc
  ${iiqka_directory}/src/${utils_directory}/os-core-udp-communication/subscriber.cc
  ${iiqka_directory}/src/${utils_directory}/os-core-udp-communication/replier.cc
  ${iiqka_directory}/src/${utils_directory}/os-core-udp-communication/secure_replier.cc
  ${iiqka_directory}/src/${utils_directory}/os-core-udp-communication/socket.cc
  ${iiqka_directory}/src/${utils_directory}/os-core-udp-communication/secure_socket.cc
  ${iiqka_directory}/src/robot.cc
)

# Build external-control-sdk library

add_library(${target_name} SHARED ${sources})

target_link_libraries(${target_name} PUBLIC
  OpenSSL::SSL
  ${PROTOBUF_LIBRARY}
  ${gRPC_LIBRARIES}
  kuka-external-control-sdk-protobuf
)

target_include_directories(${target_name} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${common_directory}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${iiqka_directory}/include>"
  "${CMAKE_CURRENT_BINARY_DIR}"
)
target_compile_options(${target_name} PRIVATE -g)
target_compile_features(${target_name} INTERFACE cxx_std_17 PRIVATE cxx_std_17)

# Install and export

install(TARGETS kuka-external-control-sdk-protobuf EXPORT kuka-external-control-sdk-protobuf/
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS ${target_name} EXPORT ${target_name}/
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${common_directory}/include/
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${iiqka_directory}/include/
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${iiqka_directory}
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")
