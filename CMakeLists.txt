# cd to project root
# gcc -Wall -c libs/IT8951/Config/DEV_Config.c
# gcc -Wall -c libs/IT8951/e-Paper/EPD_IT8951.c
# g++ -Wall -c main.cpp

# g++ DEV_Config.o EPD_IT8951.o main.o /usr/local/lib/libbcm2835.a -o epaper-tools

# sudo ./epaper-tools

cmake_minimum_required(VERSION 3.16.3)
project(epaper-tools)

set(CMAKE_CXX_STANDARD 17)

add_library(bcm2835 STATIC IMPORTED)
set_property(TARGET bcm2835 PROPERTY
        IMPORTED_LOCATION "/usr/local/lib/libbcm2835.a")

add_library(EPD_IT895 STATIC libs/IT8951/e-Paper/EPD_IT8951.c)
add_library(DEV_Config STATIC libs/IT8951/Config/DEV_Config.c)
target_link_libraries(DEV_Config PRIVATE bcm2835)

add_executable(epaper-tools main.cpp)
target_link_libraries(epaper-tools DEV_Config EPD_IT895)

#target_include_directories(epaper-tools PUBLIC libs/IT8951/Config)
#target_include_directories(epaper-tools PUBLIC libs/IT8951/e-Paper)

