#include "MainGame.h"
#include "iostream"
#include "string"
#include "GL/glew.h"

void fatalError(std::string errorMsg) {
    std::cout << errorMsg << " SDL error: " << SDL_GetError() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    int c;
    std::cin >> c;
    SDL_Quit();
};

MainGame::MainGame() {
    _window = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    _gameState = GameState::PLAY;
}

void MainGame::run() {
    initSystems();
    gameLoop();
}

void MainGame::initSystems() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fatalError("SDL could not initialize!");
    };

    SDL_Window *_window = SDL_CreateWindow(
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

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GLcontext could not been create");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew");
    }

//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
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
//                std::cout << evnt.motion.x << std::endl;
                break;
        }
    };
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_COLOR_ARRAY);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0, 0);
    glVertex2f(0, 500);
    glVertex2f(500, 500);

    glEnd();

    SDL_GL_SwapWindow(_window);
}
