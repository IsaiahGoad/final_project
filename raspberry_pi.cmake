set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(SYSROOT $ENV{SYSROOT_AARCH64})

set(CMAKE_SYSROOT ${SYSROOT})
set(CMAKE_C_COMPILER "aarch64-unknown-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "aarch64-unknown-linux-gnu-g++")

set(CMAKE_FIND_ROOT_PATH "/app/install_cortexa53_openssl" "/app/install_cortexa53_cjson" "/app/install_cortexa53_mqtt")

link_directories(".")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)