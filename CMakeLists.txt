cmake_minimum_required(VERSION 3.16.3)
project(epaper_tools)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
add_library(
        gpio_driver STATIC
        libs/IT8951/Config/DEV_Config.h
        libs/IT8951/Config/DEV_Config.c
)
add_library(
        epaper_driver STATIC
        libs/IT8951/e-Paper/EPD_IT8951.h
        libs/IT8951/e-Paper/EPD_IT8951.c
)
target_include_directories(gpio_driver PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs>)

add_executable(epaper-tools main.cpp)
target_link_libraries(epaper-tools gpio_driver epaper_driver)