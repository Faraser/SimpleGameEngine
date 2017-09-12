cmake_minimum_required(VERSION 3.8)
project(SimpleGameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp MainGame.cpp MainGame.h engine/Sprite.cpp engine/Sprite.h engine/GLSLprogram.cpp engine/GLSLprogram.h engine/Errors.cpp engine/Errors.h engine/Vertex.h engine/IOManager.cpp engine/IOManager.h engine/picoPNG.h engine/picoPNG.cpp engine/GLTexture.h engine/ImageLoader.cpp engine/ImageLoader.h engine/ResourceManager.cpp engine/ResourceManager.h engine/TextureCache.cpp engine/TextureCache.h engine/Window.cpp engine/Window.h)
add_executable(SimpleGameEngine ${SOURCE_FILES})

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

target_link_libraries(SimpleGameEngine ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY})
