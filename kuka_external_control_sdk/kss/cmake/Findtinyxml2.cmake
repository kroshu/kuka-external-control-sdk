find_path(tinyxml2_INCLUDE_DIR NAMES tinyxml2.h)
find_library(tinyxml2_LIBRARY NAMES tinyxml2)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tinyxml2 DEFAULT_MSG tinyxml2_LIBRARY tinyxml2_INCLUDE_DIR)

if(tinyxml2_FOUND)
  set(tinyxml2_LIBRARIES ${tinyxml2_LIBRARY})
  set(tinyxml2_INCLUDE_DIRS ${tinyxml2_INCLUDE_DIR})
endif()
