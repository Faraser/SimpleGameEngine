cmake_minimum_required(VERSION 3.8)

project(Engine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Sprite.cpp
        Sprite.h
        GLSLprogram.cpp
        GLSLprogram.h
        EngineErrors.cpp
        EngineErrors.h
        Vertex.h
        IOManager.cpp
        IOManager.h
        picoPNG.h
        picoPNG.cpp
        GLTexture.h
        ImageLoader.cpp
        ImageLoader.h
        ResourceManager.cpp
        ResourceManager.h
        TextureCache.cpp
        TextureCache.h
        Window.cpp
        Window.h
        Engine.cpp
        Engine.h
        Camera2D.cpp
        Camera2D.h
        SpriteBatch.cpp
        SpriteBatch.h
        InputManager.cpp
        InputManager.h
        Timing.cpp
        Timing.h
        SpriteFont.cpp
        SpriteFont.h
        AudioEngine.cpp
        AudioEngine.h
        ParticleEngine2D.cpp
        ParticleEngine2D.h
        ParticleBatch2D.cpp
        ParticleBatch2D.h)

#add_executable(SimpleGameEngine ${SOURCE_FILES})

add_library(Engine STATIC ${SOURCE_FILES})

include_directories(/usr/local/include)
include_directories(.)

link_directories(/usr/local/lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(Engine ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} -L/usr/local/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf -L/usr/local/Cellar/sdl2_mixer/2.0.1_1/lib -lSDL2_mixer)
