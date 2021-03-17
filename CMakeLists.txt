cmake_minimum_required(VERSION 3.16.3)
project(epaper_tools)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        epaper_tools
        libs/IT8951/Config/Debug.h
        libs/IT8951/Config/DEV_Config.c
        libs/IT8951/Config/DEV_Config.h
        libs/IT8951/e-Paper/EPD_IT8951.c
        libs/IT8951/e-Paper/EPD_IT8951.h
)

