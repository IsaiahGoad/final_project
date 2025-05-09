cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(bmp280 VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

add_library(bmp280_shared SHARED bmp280_i2c.c)
add_executable(bmp280_bin main.c)
target_link_libraries(bmp280_bin bmp280_shared wiringx)