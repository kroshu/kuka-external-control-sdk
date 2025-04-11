cmake_minimum_required(VERSION 3.13)

project(external-control-sdk)

set(common_directory ${CMAKE_SOURCE_DIR}/common)
set(utils_directory ${CMAKE_SOURCE_DIR}/utils)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE )
endif()
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(iiqka)
add_subdirectory(kss)

get_target_property(IIQKA_INCLUDE_DIRS kuka-iiqka-client-library INCLUDE_DIRECTORIES)
get_target_property(KSS_INCLUDE_DIRS kuka-kss-client-library INCLUDE_DIRECTORIES)

add_library(kuka-external-control-sdk STATIC "$<TARGET_OBJECTS:kuka-iiqka-client-library>" "$<TARGET_OBJECTS:kuka-kss-client-library>")
target_include_directories(kuka-external-control-sdk PUBLIC ${IIQKA_INCLUDE_DIRS} ${KSS_INCLUDE_DIRS})
target_link_Libraries(kuka-external-control-sdk PUBLIC kuka-iiqka-client-library kuka-kss-client-library)

install(TARGETS kuka-external-control-sdk EXPORT SdkExport
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT SdkExport NAMESPACE Kuka:: FILE kuka-external-control-sdkTargets.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/kuka-external-control-sdkConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuka-external-control-sdk
        )

install(DIRECTORY ${common_directory}/include/ ${utils_directory}/include/
      DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hh")
# Install package.xml file so this package can be processed by ROS toolings
# See REP 136 for details
# Installing this in non-ROS environments won't have any effect, but it won't harm, either.
install(FILES package.xml DESTINATION share/external_control_sdk)
