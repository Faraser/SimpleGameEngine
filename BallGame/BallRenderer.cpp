#include "BallRenderer.h"

// TODO: refactor this
void BallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch,
                               const std::vector<Ball>& balls,
                               const glm::mat4& projectionMatrix) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Lazy initialize the program
    if (m_program == nullptr) {
        m_program = std::make_unique<Engine::GLSLprogram>();
        m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
        m_program->addAttribute("vertexPosition");
        m_program->addAttribute("vertexColor");
        m_program->addAttribute("vertexUV");
        m_program->linkShaders();
    }

    m_program->use();

    spriteBatch.begin();

    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureUniform = m_program->getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    GLint pUniform = m_program->getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Render all the balls
    for (auto& ball : balls) {
        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
                                 ball.radius * 2.0f, ball.radius * 2.0f);
        spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, ball.color);
    }

    spriteBatch.end();
    spriteBatch.renderBatch();

    m_program->unuse();
}

void MomentumBallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch,
                                       const std::vector<Ball>& balls,
                                       const glm::mat4& projectionMatrix) {
    glClearColor(0.0f, 0.1f, 0.5f, 1.0f);

    // Lazy initialize the program
    if (m_program == nullptr) {
        m_program = std::make_unique<Engine::GLSLprogram>();
        m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
        m_program->addAttribute("vertexPosition");
        m_program->addAttribute("vertexColor");
        m_program->addAttribute("vertexUV");
        m_program->linkShaders();
    }

    m_program->use();

    spriteBatch.begin();

    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureUniform = m_program->getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    GLint pUniform = m_program->getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Render all the balls
    for (auto& ball : balls) {
        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
                                 ball.radius * 2.0f, ball.radius * 2.0f);

        Engine::ColorRGBA8 color;
        GLubyte colorVal = static_cast<GLubyte>(glm::clamp(glm::length(ball.velocity) * ball.mass * 12.0f, 0.0f,
                                                           255.0f));
        color.r = colorVal;
        color.g = colorVal;
        color.b = colorVal;
        color.a = colorVal;

        spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, color);
    }

    spriteBatch.end();
    spriteBatch.renderBatch();

    m_program->unuse();
}

VelocityBallRenderer::VelocityBallRenderer(int screenWidth, int screenHeight) :
        m_screenWidth(screenWidth),
        m_screenHeight(screenHeight) {}

void VelocityBallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch,
                                       const std::vector<Ball>& balls,
                                       const glm::mat4& projectionMatrix) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Lazy initialize the program
    if (m_program == nullptr) {
        m_program = std::make_unique<Engine::GLSLprogram>();
        m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
        m_program->addAttribute("vertexPosition");
        m_program->addAttribute("vertexColor");
        m_program->addAttribute("vertexUV");
        m_program->linkShaders();
    }

    m_program->use();

    spriteBatch.begin();

    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureUniform = m_program->getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    GLint pUniform = m_program->getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Render all the balls
    for (auto& ball : balls) {
        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
                                 ball.radius * 2.0f, ball.radius * 2.0f);

        float mult = 100.0f;
        Engine::ColorRGBA8 color;
        GLubyte colorVal = static_cast<GLubyte>(glm::clamp(ball.velocity.x * ball.mass * mult, 0.0f, 255.0f));
        color.r = 128;
        color.g = static_cast<GLubyte>((ball.position.x / m_screenWidth) * 255.0f);
        color.b = static_cast<GLubyte>((ball.position.y / m_screenHeight) * 255.0f);
        color.a = colorVal;

        spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, color);
    }

    spriteBatch.end();
    spriteBatch.renderBatch();

    m_program->unuse();
}

TrippyBallRenderer::TrippyBallRenderer(int screenWidth, int screenHeight) :
        m_screenWidth(screenWidth),
        m_screenHeight(screenHeight) {}

void TrippyBallRenderer::renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls,
                                     const glm::mat4& projectionMatrix) {
    glClearColor(0.1f, 0.0f, 0.0f, 1.0f);

    // Lazy initialize the program
    if (m_program == nullptr) {
        m_program = std::make_unique<Engine::GLSLprogram>();
        m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
        m_program->addAttribute("vertexPosition");
        m_program->addAttribute("vertexColor");
        m_program->addAttribute("vertexUV");
        m_program->linkShaders();
    }

    m_program->use();

    spriteBatch.begin();

    // Make sure the shader uses texture 0
    glActiveTexture(GL_TEXTURE0);
    GLint textureUniform = m_program->getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    GLint pUniform = m_program->getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    float TIME_SPEED = 0.01f;
    float DIVISOR = 4.0f;
    float SPIRAL_INTESITY = 10.0f;

    m_time += TIME_SPEED;

    // Render all the balls
    for (auto& ball : balls) {
        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius,
                                 ball.radius * 2.0f, ball.radius * 2.0f);


        // Get vector from center point
        glm::vec2 centerVec = ball.position - glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
        float centerDist = glm::length(centerVec);

        // Get angle from the horizontal
        float angle = atan2(centerVec.x, centerVec.y) / (3.1415926f / DIVISOR);
        // Move with time
        angle -= m_time;
        // Add the spiral
        angle += (centerDist / m_screenWidth) * SPIRAL_INTESITY;

        Engine::ColorRGBA8 color;
        color.r = static_cast<GLubyte>(angle * 255.0f);
        color.g = static_cast<GLubyte>(angle * 255.0f * cos(m_time));
        color.b = static_cast<GLubyte>(angle * 255.0f * sin(m_time));
        color.a = static_cast<GLubyte>(glm::clamp(1.0f - (centerDist / (m_screenWidth / 2.0f)), 0.0f, 1.0f) * 255.0f);

        spriteBatch.draw(destRect, uvRect, ball.textureId, 0.0f, color);
    }

    spriteBatch.end();
    spriteBatch.renderBatch();

    m_program->unuse();

}
