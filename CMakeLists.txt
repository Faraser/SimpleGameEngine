cmake_minimum_required(VERSION 3.8)
project(openGLTuror)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp MainGame.cpp MainGame.h Sprite.cpp Sprite.h GLSLprogram.cpp GLSLprogram.h Errors.cpp Errors.h)
add_executable(openGLTuror ${SOURCE_FILES})

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(openGLTuror ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY})
