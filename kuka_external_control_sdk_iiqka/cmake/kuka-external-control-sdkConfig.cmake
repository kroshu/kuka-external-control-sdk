include(CMakeFindDependencyMacro)

find_dependency(kuka-iiqka-client-library REQUIRED)
find_dependency(kuka-kss-client-library REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/kuka-external-control-sdkTargets.cmake")
