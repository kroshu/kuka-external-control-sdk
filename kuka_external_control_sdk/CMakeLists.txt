cmake_minimum_required(VERSION 3.13)

project(external-control-sdk)


set(common_directory ${CMAKE_SOURCE_DIR}/common)
set(utils_directory ${CMAKE_SOURCE_DIR}/utils)

add_subdirectory(iiqka)
#add_subdirectory(kss)

install(DIRECTORY ${common_directory}/include/ ${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")

# Install package.xml file so this package can be processed by ROS toolings
# See REP 136 for details
# Installing this in non-ROS environments won't have any effect, but it won't harm, either.
install(FILES package.xml DESTINATION share/external_control_sdk)