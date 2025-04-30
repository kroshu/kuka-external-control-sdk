include(CMakeFindDependencyMacro)

find_dependency(Threads REQUIRED)
find_dependency(tinyxml2 QUIET)

if(NOT tinyxml2_FOUND)
  message(STATUS "tinyxml2 not found")
  find_dependency(tinyxml2_vendor REQUIRED)
endif()


include("${CMAKE_CURRENT_LIST_DIR}/kuka-kss-client-libraryTargets.cmake")
