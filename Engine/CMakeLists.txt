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
        ParticleBatch2D.h
        IGameScreen.h
        IMainGame.cpp
        IMainGame.h
        ScreenList.cpp
        ScreenList.h
        DebugRenderer.cpp
        DebugRenderer.h
        TileSheet.h
        )

add_library(Engine STATIC ${SOURCE_FILES})

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_mixer)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(Engine
        ${OPENGL_gl_LIBRARY}
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
