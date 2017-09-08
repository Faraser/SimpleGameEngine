#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "iostream"

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
    };

    SDL_Window *window = SDL_CreateWindow("Game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768,
                                          SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
    }

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    return 0;
}

