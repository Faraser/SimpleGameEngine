#include "Errors.h"
#include "string"
#include "SDL2/SDL.h"
#include "iostream"


void fatalError(std::string errorMsg) {
    std::cout << errorMsg << " SDL error: " << SDL_GetError() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    int c;
    std::cin >> c;
    SDL_Quit();
};

