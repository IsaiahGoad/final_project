cmake_minimum_required(VERSION 3.10)
project(final_project)

# You must define this when calling cmake: -DPLATFORM_NAME=cv1800b or cortexa53.
if(NOT PLATFORM_NAME)
  message(FATAL_ERROR "Please set PLATFORM_NAME, e.g. -DPLATFORM_NAME=cv1800b")
endif()

set(BASE_PATH "/app/install_${PLATFORM_NAME}")

message(STATUS "Using platform: ${PLATFORM_NAME}")
message(STATUS "Looking for libraries under: ${BASE_PATH}")

# Helper macro to find and validate libraries
macro(find_and_check_library var libname foldersuffix)
  find_library(${var}
    NAMES ${libname} lib${libname}
    PATHS "${BASE_PATH}_${foldersuffix}/lib"
    NO_DEFAULT_PATH
  )
  if(NOT ${var})
    message(FATAL_ERROR "${libname} library not found in ${BASE_PATH}_${foldersuffix}/lib")
  else()
    message(STATUS "Found ${libname} library: ${${var}}")
  endif()
endmacro()

set(INCLUDE_PATHS
  "${BASE_PATH}_mqtt/include"
  "${BASE_PATH}_cjson/include"
  "${BASE_PATH}_openssl/include"
)
include_directories(${INCLUDE_PATHS})

# Find libraries
find_and_check_library(CJSON_LIB cjson cjson)
find_and_check_library(MQTT_LIB mosquitto mqtt)
find_and_check_library(OPEN_SSL_LIB ssl openssl)
find_and_check_library(CRYPTO_LIB crypto openssl)

# If you already have the compiled shared objects
# for all your homeworks then you do NOT have to recompile them
# simple add it them add the end of target_link_libraries
# like we did with wiringx
# Copy the shared objects (.so) and headers to the project directory

# Add executables
add_executable(subscriber subscriber.c)
add_executable(publisher publisher.c)

# Link libraries
# The publisher doesn't need any additional library linking as it's running on the host
# or rasberry pi (unless doing the bonus for receiving messages from the duo)
target_link_libraries(publisher ${CJSON_LIB} ${MQTT_LIB} ${OPEN_SSL_LIB} ${CRYPTO_LIB})

# The subscriber is running on the duo and you'll need to link your libraries.
# Add your library names at the end
# Also make sure you copy the libraries to /usr/lib on the duo
target_link_libraries(subscriber ${CJSON_LIB} ${MQTT_LIB} ${OPEN_SSL_LIB} ${CRYPTO_LIB})
