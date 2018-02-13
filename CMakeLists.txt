cmake_minimum_required(VERSION 3.8)

project(SimpleGameEngine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SimpleGameEngine_SOURCE_DIR}/cmake")

add_subdirectory(ZombieGame)
add_subdirectory(BallGame)
add_subdirectory(NinjaPlatformer)
add_subdirectory(Engine)
