cmake_minimum_required(VERSION 3.13)

project("external-control-sdk")

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

set(common_directory ${PARENT_DIR}/common)
set(kss_directory ${PARENT_DIR}/kss)
set(utils_directory ${PARENT_DIR}/utils)

set(target_name "kuka-kss-client-library")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

find_package(Threads REQUIRED)

set(sources
  ${PROTO_SRCS}
  ${common_directory}/src/status.cc
  ${utils_directory}/src/os-core-udp-communication/replier.cc
  ${utils_directory}/src/os-core-udp-communication/socket.cc
  ${utils_directory}/src/os-core-udp-communication/dissector.cc
  ${utils_directory}/src/os-core-udp-communication/tcp_client.cc
  ${kss_directory}/src/eki-rsi/eki_comm_client.cc
  ${kss_directory}/src/eki-rsi/rsi_comm_endpoint.cc
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

target_link_libraries(${target_name} PUBLIC
    Threads::Threads
)

target_compile_features(${target_name} INTERFACE cxx_std_17 PRIVATE cxx_std_17)

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
