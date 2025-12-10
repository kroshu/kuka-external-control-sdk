cmake_minimum_required(VERSION 3.13)

project("kuka-external-control-examples")

# Project dependencies
list(APPEND CMAKE_PREFIX_PATH "~/.local/lib/cmake")

find_package(kuka-external-control-sdk CONFIG REQUIRED)

# EKI + RSI example
add_executable(eki_rsi_example src/eki_rsi_example.cc)
target_compile_features(eki_rsi_example INTERFACE cxx_std_20 PRIVATE cxx_std_20)
target_link_libraries(eki_rsi_example PRIVATE Kuka::kuka-external-control-sdk)
target_include_directories(eki_rsi_example PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

# Multi RSI example
add_executable(multi_rsi_robot_example src/multi_rsi_robot_example.cc)
target_compile_features(multi_rsi_robot_example INTERFACE cxx_std_20 PRIVATE cxx_std_20)
target_link_libraries(multi_rsi_robot_example PRIVATE Kuka::kuka-external-control-sdk)
target_include_directories(multi_rsi_robot_example PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

# Install package.xml file so this package can be processed by ROS toolings
# See REP 136 for details
# Installing this in non-ROS environments won't have any effect, but it won't harm, either.
install(FILES package.xml DESTINATION share/external_control_sdk)
