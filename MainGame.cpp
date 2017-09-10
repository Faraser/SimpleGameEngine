#include "MainGame.h"
#include "iostream"
#include "string"
#include "OpenGL/gl3.h"
#include "Errors.h"

MainGame::MainGame() {
    _window = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    _gameState = GameState::PLAY;
}

void MainGame::run() {
    initSystems();

    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

    gameLoop();
}

void MainGame::initSystems() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fatalError("SDL could not initialize!");
    };

    _window = SDL_CreateWindow(
            "Game engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _screenWidth,
            _screenHeight,
            SDL_WINDOW_OPENGL
    );

    if (_window == nullptr) {
        fatalError("Window could not be created!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GLcontext could not been create");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    initShaders();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
        drawGame();
    }
}

void MainGame::processInput() {
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                break;
        }
    };
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();
    _sprite.draw();

    _colorProgram.unuse();
    SDL_GL_SwapWindow(_window);
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("shaders/colorShading.vert",
                                 "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.linkShaders();
}
