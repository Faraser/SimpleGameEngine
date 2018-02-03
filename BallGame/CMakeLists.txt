cmake_minimum_required(VERSION 3.8)

project(BallGame)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        MainGame.cpp
        MainGame.h
        Ball.cpp
        Ball.h
        BallRenderer.cpp BallRenderer.h BallController.cpp BallController.h Grid.cpp Grid.h)

add_executable(BallGame ${SOURCE_FILES})

include_directories(../)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(BallGame Engine)
