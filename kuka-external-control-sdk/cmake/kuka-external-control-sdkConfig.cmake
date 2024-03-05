include(CMakeFindDependencyMacro)


find_dependency(OpenSSL REQUIRED)
find_dependency(Threads REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/kuka-external-control-sdkTargets.cmake")