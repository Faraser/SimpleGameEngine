#pragma once

#include "SDL2/SDL.h"
#include "string"

enum WindowFlags {
    INVISIBLE = 0x1,
    FULLSCREEN = 0x2,
    BORDERLESS = 0x4
};

class Window {
public:
    Window();

    ~Window();

    int create(const std::string &windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

    int getScreenWidth() const { return _screenWidth; };

    int getScreenHeight() const { return _screenHeight; };

    void swapBuffer();

private:
    SDL_Window *_sdlWindow;
    int _screenWidth, _screenHeight;
};
