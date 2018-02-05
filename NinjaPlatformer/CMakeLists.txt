cmake_minimum_required(VERSION 3.8)

project(NinjaPlatformer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp main.cpp App.cpp App.h GameplayScreen.cpp GameplayScreen.h)

add_executable(NinjaPlatformer ${SOURCE_FILES})

include_directories(../)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(NinjaPlatformer Engine)
