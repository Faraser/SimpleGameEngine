cmake_minimum_required(VERSION 3.8)

project(NinjaPlatformer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp main.cpp App.cpp App.h GameplayScreen.cpp GameplayScreen.h Box.cpp Box.h Player.cpp Player.h Capsule.cpp Capsule.h Light.h MainMenuScreen.cpp MainMenuScreen.h ScreenIndices.h)

add_executable(NinjaPlatformer ${SOURCE_FILES})

include_directories(../)

find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIRS})

find_package(CEGUI REQUIRED)
include_directories(${CEGUI_INCLUDE_DIRS})

target_link_libraries(NinjaPlatformer Engine ${BOX2D_LIBRARIES} ${CEGUI_LIBRARIES} ${CEGUI_OpenGLRenderer_LIBRARIES})
