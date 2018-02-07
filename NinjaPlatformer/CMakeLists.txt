cmake_minimum_required(VERSION 3.8)

project(NinjaPlatformer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp main.cpp App.cpp App.h GameplayScreen.cpp GameplayScreen.h Box.cpp Box.h)

add_executable(NinjaPlatformer ${SOURCE_FILES})

include_directories(../)

target_link_libraries(NinjaPlatformer Engine -lBox2D)
