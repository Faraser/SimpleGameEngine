#include "Window.h"

#include <OpenGL/gl3.h>

#include "EngineErrors.h"

namespace Engine {
Window::Window() {

}

Window::~Window() {

}

int Window::create(const std::string& windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
    Uint32 flags = SDL_WINDOW_OPENGL;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }

    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }


    _sdlWindow = SDL_CreateWindow(
            windowName.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            screenWidth,
            screenHeight,
            flags
    );

    if (_sdlWindow == nullptr) {
        fatalError("Window could not be created!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
    if (glContext == nullptr) {
        fatalError("SDL_GLcontext could not been create");
    }


    // Enable alpha-blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void Window::swapBuffer() {
    SDL_GL_SwapWindow(_sdlWindow);
}
}
