cmake_minimum_required(VERSION 3.13)

project("external-control-sdk")

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

set(common_directory ${PARENT_DIR}/common)
set(kss_directory ${PARENT_DIR}/kss)
set(utils_directory ${PARENT_DIR}/utils)
set(test_directory ${kss_directory}/test)

set(target_name "kuka-kss-client-library")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

find_package(Threads REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

set(sources
  ${common_directory}/src/status.cc
  ${utils_directory}/src/os-core-udp-communication/replier.cc
  ${utils_directory}/src/os-core-udp-communication/socket.cc
  ${utils_directory}/src/os-core-udp-communication/publisher.cc
  ${utils_directory}/src/os-core-udp-communication/subscriber.cc
  ${utils_directory}/src/os-core-udp-communication/dissector.cc
  ${utils_directory}/src/os-core-udp-communication/tcp_client.cc
  ${kss_directory}/src/mxa/client.cc
  ${kss_directory}/src/mxa/robot_interface.cc
  ${kss_directory}/src/eki/client.cc
  ${kss_directory}/src/eki/robot_interface.cc
  ${kss_directory}/src/eki/init_sequence.cc
  ${kss_directory}/src/rsi/endpoint.cc
  ${kss_directory}/src/rsi/robot_interface.cc
  ${kss_directory}/src/message_builder.cc
  ${kss_directory}/src/robot.cc
)

# Build KSS client library

add_library(${target_name} STATIC ${sources})

target_include_directories(${target_name} PUBLIC
  "$<BUILD_INTERFACE:${common_directory}/include>"
  "$<BUILD_INTERFACE:${kss_directory}/include>"
  "$<BUILD_INTERFACE:${utils_directory}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>"
)

target_link_libraries(${target_name} PUBLIC Threads::Threads PUBLIC tinyxml2::tinyxml2)

target_compile_features(${target_name} INTERFACE cxx_std_17 PRIVATE cxx_std_17)

# Build tests for KSS
if (CMAKE_TESTING_ENABLED)
  if (NOT TARGET gtest)
    add_subdirectory(/usr/src/googletest GTest)
  endif()
  enable_testing()

  add_executable(
    test_kss_message_builder
    test/test_message_builder.cc
  )
  add_executable(
    test_eki_communication
    test/test_eki_communication.cc
  )

  target_link_libraries(
    test_kss_message_builder
    GTest::gtest_main
    kuka-kss-client-library
    GTest::gtest
  )
  target_link_libraries(
    test_eki_communication
    GTest::gtest_main
    kuka-kss-client-library
    GTest::gtest
  )

  target_include_directories(test_kss_message_builder PUBLIC
    "$<BUILD_INTERFACE:${common_directory}/include>"
    "$<BUILD_INTERFACE:${kss_directory}/include>"
    "$<BUILD_INTERFACE:${kss_directory}/test>"
  )
  target_include_directories(test_eki_communication PUBLIC
    "$<BUILD_INTERFACE:${common_directory}/include>"
    "$<BUILD_INTERFACE:${kss_directory}/include>"
    "$<BUILD_INTERFACE:${kss_directory}/test>"
  )

  target_compile_features(test_kss_message_builder INTERFACE cxx_std_17 PRIVATE cxx_std_17)
  target_compile_features(test_eki_communication INTERFACE cxx_std_17 PRIVATE cxx_std_17)

  include(GoogleTest)

  gtest_discover_tests(test_kss_message_builder)
  gtest_discover_tests(test_eki_communication)
endif()

install(TARGETS ${target_name} EXPORT SdkExport
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT SdkExport NAMESPACE Kuka:: FILE kuka-kss-client-libraryTargets.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-kss-client-library)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/kuka-kss-client-libraryConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-kss-client-library
        )

install(DIRECTORY ${kss_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

if (NOT ${PARENT_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    install(DIRECTORY ${common_directory}/include/ ${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")
endif()
