cmake_minimum_required(VERSION 3.8)
project(openGLTuror)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp MainGame.cpp MainGame.h)
add_executable(openGLTuror ${SOURCE_FILES})

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test Main.cpp)
target_link_libraries(openGLTuror ${SDL2_LIBRARIES})