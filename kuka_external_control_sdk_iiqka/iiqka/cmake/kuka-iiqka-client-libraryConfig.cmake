include(CMakeFindDependencyMacro)

find_dependency(kuka_external_control_sdk_common REQUIRED)
find_dependency(OpenSSL REQUIRED)
find_dependency(Threads REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/kuka-iiqka-client-libraryTargets.cmake")
