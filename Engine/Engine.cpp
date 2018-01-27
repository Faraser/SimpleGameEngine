#include <SDL2/SDL.h>

#include "Engine.h"
#include "EngineErrors.h"

namespace Engine {
int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fatalError("SDL could not initialize!");
    };

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return 0;
}
}
