cmake_minimum_required(VERSION 3.8)

project(ZombieGame)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        MainGame.cpp
        MainGame.h
        Agent.cpp
        Agent.h
        Zombie.cpp
        Zombie.h
        Player.cpp
        Player.h
        Level.cpp
        Level.h
        Human.cpp
        Human.h
        Gun.cpp
        Gun.h
        Bullet.cpp
        Bullet.h
        )

add_executable(ZombieGame ${SOURCE_FILES})

include_directories(../)

target_link_libraries(ZombieGame Engine)
