#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cjson" for configuration ""
set_property(TARGET cjson APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(cjson PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/app/build/install_cv1800b_cjson/lib/libcjson.so.1.7.17"
  IMPORTED_SONAME_NOCONFIG "libcjson.so.1"
  )

list(APPEND _cmake_import_check_targets cjson )
list(APPEND _cmake_import_check_files_for_cjson "/app/build/install_cv1800b_cjson/lib/libcjson.so.1.7.17" )

# Import target "cjson-static" for configuration ""
set_property(TARGET cjson-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(cjson-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "/app/build/install_cv1800b_cjson/lib/libcjson.a"
  )

list(APPEND _cmake_import_check_targets cjson-static )
list(APPEND _cmake_import_check_files_for_cjson-static "/app/build/install_cv1800b_cjson/lib/libcjson.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
