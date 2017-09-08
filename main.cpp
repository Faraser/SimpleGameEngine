#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "iostream"
#include "MainGame.h"

int main(int argc, char ** argv) {
    MainGame mainGame;
    mainGame.run();

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

