cmake_minimum_required(VERSION 3.16.3)
project(epaper_tools)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(DEV_Config)
add_subdirectory(EPD_IT8951)
add_executable(epaper_tools main.cpp)