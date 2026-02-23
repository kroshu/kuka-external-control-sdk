cmake_minimum_required(VERSION 3.13)

project(external-control-sdk)

set(common_directory ${CMAKE_SOURCE_DIR}/common)
set(utils_directory ${CMAKE_SOURCE_DIR}/utils)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE)
endif()
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(iiqka)
add_subdirectory(kss)

get_target_property(IIQKA_INCLUDE_DIRS kuka-iiqka-client-library INCLUDE_DIRECTORIES)
get_target_property(KSS_INCLUDE_DIRS kuka-kss-client-library INCLUDE_DIRECTORIES)

add_library(kuka-external-control-sdk STATIC "$<TARGET_OBJECTS:kuka-iiqka-client-library>" "$<TARGET_OBJECTS:kuka-kss-client-library>")
target_include_directories(kuka-external-control-sdk PUBLIC ${IIQKA_INCLUDE_DIRS} ${KSS_INCLUDE_DIRS})
target_link_libraries(kuka-external-control-sdk PUBLIC
  kuka-iiqka-client-library
  kuka-kss-client-library
)

install(TARGETS kuka-external-control-sdk EXPORT SdkExport
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT SdkExport NAMESPACE Kuka::
    FILE kuka-external-control-sdkTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk
)

install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/kuka-external-control-sdkConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk
)

install(DIRECTORY ${common_directory}/include/ ${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

# Install package.xml file so this package can be processed by ROS toolings
# See REP 136 for details
# Installing this in non-ROS environments won't have any effect, but it won't harm, either.
install(FILES package.xml DESTINATION share/kuka_external_control_sdk)

#### Begin import ####
# Imported from ros-industrial/ros_industrial_cmake_boilerplate
# Copyright (C) 2018 by George Cave - gcave@stablecoder.ca
# Copyright (c) 2020, Southwest Research Institute
# Licensed under Apache-2.0 license

# Allows Colcon to find non-Ament packages when using workspace underlays
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/share/ament_index/resource_index/packages/kuka_external_control_sdk "")
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/share/ament_index/resource_index/packages/kuka_external_control_sdk
    DESTINATION share/ament_index/resource_index/packages
)
file(WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/share/kuka_external_control_sdk/hook/ament_prefix_path.dsv
    "prepend-non-duplicate;AMENT_PREFIX_PATH;"
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/share/kuka_external_control_sdk/hook/ament_prefix_path.dsv
    DESTINATION share/kuka_external_control_sdk/hook
)
file(WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/share/kuka_external_control_sdk/hook/ros_package_path.dsv
    "prepend-non-duplicate;ROS_PACKAGE_PATH;"
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/share/kuka_external_control_sdk/hook/ros_package_path.dsv
    DESTINATION share/kuka_external_control_sdk/hook
)
#### End import ####
