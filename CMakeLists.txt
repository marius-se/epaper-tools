cmake_minimum_required(VERSION 3.16.3)
project(epaper-tools)

set(CMAKE_CXX_STANDARD 17)

add_library(DEV_Config STATIC libs/IT8951/Config/DEV_Config.c)
add_library(EPD_IT895 STATIC libs/IT8951/e-Paper/EPD_IT8951.c)

add_executable(epaper-tools main.cpp)

target_link_libraries(epaper-tools DEV_Config)
target_link_libraries(epaper-tools EPD_IT895)
target_link_libraries(epaper-tools /usr/local/lib/libbcm2835.a)

target_include_directories(epaper-tools PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libs/IT8951/Config")
target_include_directories(epaper-tools PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libs/IT8951/e-Paper")

