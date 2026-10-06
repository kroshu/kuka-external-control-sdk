include(CMakeFindDependencyMacro)

find_dependency(kuka_external_control_sdk_common REQUIRED)
find_dependency(kuka-iiqka-client-library REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/kuka-external-control-sdkTargets.cmake")
