cmake_minimum_required(VERSION 3.8)
project(SimpleGameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        ZombieGame/MainGame.cpp
        ZombieGame/MainGame.h
        ZombieGame/Agent.cpp
        ZombieGame/Agent.h
        ZombieGame/Zombie.cpp
        ZombieGame/Zombie.h
        ZombieGame/Player.cpp
        ZombieGame/Player.h
        ZombieGame/Level.cpp
        ZombieGame/Level.h
        ZombieGame/Human.cpp
        ZombieGame/Human.h
        ZombieGame/Gun.cpp
        ZombieGame/Gun.h
        ZombieGame/Bullet.cpp
        ZombieGame/Bullet.h
        )

add_executable(SimpleGameEngine ${SOURCE_FILES})
add_subdirectory(Engine)

include_directories(.)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(SimpleGameEngine Engine)
