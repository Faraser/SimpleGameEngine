#include "GameplayScreen.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Engine/IMainGame.h>
#include <OpenGL/gl3.h>
#include <Engine/ResourceManager.h>
#include <random>

GameplayScreen::GameplayScreen(Engine::Window* window) : m_window(window) {

}

GameplayScreen::~GameplayScreen() {

}

void GameplayScreen::build() {

}

void GameplayScreen::destroy() {

}

void GameplayScreen::onEntry() {
    b2Vec2 gravity(0.0f, -25.0f);
    m_world = std::make_unique<b2World>(gravity);

    // Make the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // Make the ground m_fixture
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Load the texture
    m_texture = Engine::ResourceManager::getTexture("Assets/bricks_top.png");

    // Make a bunch of boxes
    std::mt19937 randGenerator;
    std::uniform_real_distribution<float> xPos(-10.0f, 10.0f);
    std::uniform_real_distribution<float> yPos(-10.0f, 10.0f);
    std::uniform_real_distribution<float> size(0.5f, 2.5f);
    std::uniform_int_distribution<int> color(0, 255);

    const int NUM_BOXES = 50;

    for (int i = 0; i < NUM_BOXES; i++) {
        Engine::ColorRGBA8 randColor(color(randGenerator), color(randGenerator), color(randGenerator), 255);
        float s = size(randGenerator);
        Box newBox;
        newBox.init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(s, s), m_texture,
                    randColor, false);
        m_boxes.push_back(newBox);
    }


    // Initialize spritebatch
    m_spriteBatch.init();

    // Shader initialize
    m_textureProgram.compileShaders("Shaders/colorShading.vert",
                                    "Shaders/colorShading.frag");
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.linkShaders();


    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(32.0f);

    // Init player
    m_player.init(m_world.get(), glm::vec2(0.0f, 15.0f), glm::vec2(1.0f, 2.0f), Engine::ColorRGBA8(255, 255, 255, 255));
}

void GameplayScreen::onExit() {

}

void GameplayScreen::update() {
    m_camera.update();
    checkInput();
    m_player.update(m_game->inputManager);

    // Update the physics simulation
    m_world->Step(1.0f / 60.0f, 6, 2);
}

void GameplayScreen::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_textureProgram.use();

    // Upload texture uniform
    GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);
    glActiveTexture(GL_TEXTURE0);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();

    // Draw all the boxes
    for (auto& b : m_boxes) {
        b.draw(m_spriteBatch);
    }

    m_player.draw(m_spriteBatch);

    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unuse();
}

int GameplayScreen::getNextScreenIndex() const {
    return -1;
}

int GameplayScreen::getPreviousScreenIndex() const {
    return -1;
}

void GameplayScreen::checkInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_game->onSDLEvent(event);
    }

}

