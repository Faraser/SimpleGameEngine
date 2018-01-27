#include "EngineErrors.h"

#include <SDL2/SDL.h>
#include <iostream>

namespace Engine {
void fatalError(std::string errorMsg) {
    std::cout << errorMsg << " SDL error: " << SDL_GetError() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    int c;
    std::cin >> c;
    SDL_Quit();
    exit(69);
};
}
