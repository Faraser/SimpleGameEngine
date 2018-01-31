#include "BallRenderer.h"

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
