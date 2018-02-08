#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <Engine/Vertex.h>
#include <Engine/GLTexture.h>
#include <Engine/SpriteBatch.h>

class Box {
public:
    Box();

    ~Box();

    void init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, Engine::GLTexture texture, Engine::ColorRGBA8 color, bool fixedRotation);

    void draw(Engine::SpriteBatch & spriteBatch);

    b2Body* getBody() const { return m_body; }

    b2Fixture* getFixture() const { return m_fixture; }

    const glm::vec2& getDimensions() const { return m_dimensions; }

    const Engine::ColorRGBA8& getColor() const { return m_color; }

private:
    b2Body* m_body = nullptr;
    b2Fixture* m_fixture = nullptr;
    glm::vec2 m_dimensions;
    Engine::ColorRGBA8 m_color;
    Engine::GLTexture m_texture;
};


