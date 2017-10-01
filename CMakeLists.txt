cmake_minimum_required(VERSION 3.8)
project(SimpleGameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp MainGame.cpp MainGame.h Engine/Sprite.cpp Engine/Sprite.h Engine/GLSLprogram.cpp Engine/GLSLprogram.h Engine/Errors.cpp Engine/Errors.h Engine/Vertex.h Engine/IOManager.cpp Engine/IOManager.h Engine/picoPNG.h Engine/picoPNG.cpp Engine/GLTexture.h Engine/ImageLoader.cpp Engine/ImageLoader.h Engine/ResourceManager.cpp Engine/ResourceManager.h Engine/TextureCache.cpp Engine/TextureCache.h Engine/Window.cpp Engine/Window.h Engine/Engine.cpp Engine/Engine.h Engine/Camera2D.cpp Engine/Camera2D.h Engine/SpriteBatch.cpp Engine/SpriteBatch.h Engine/InputManager.cpp Engine/InputManager.h Engine/Timing.cpp Engine/Timing.h Bullet.cpp Bullet.h)
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
