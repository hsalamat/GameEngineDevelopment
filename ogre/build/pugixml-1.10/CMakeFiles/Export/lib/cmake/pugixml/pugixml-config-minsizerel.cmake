#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pugixml" for configuration "MinSizeRel"
set_property(TARGET pugixml APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(pugixml PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/pugixml.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS pugixml )
list(APPEND _IMPORT_CHECK_FILES_FOR_pugixml "${_IMPORT_PREFIX}/lib/pugixml.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
