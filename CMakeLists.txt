cmake_minimum_required(VERSION 3.16.3)
project(epaper_tools)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/IT8951/Config)
add_subdirectory(libs/IT8951/e-Paper)
add_executable(epaper_tools main.cpp)