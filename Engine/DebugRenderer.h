#pragma once

#include <glm/glm.hpp>
#include "Vertex.h"
#include "GLSLprogram.h"
#include <vector>

namespace Engine {

class DebugRenderer {
public:

    DebugRenderer();

    ~DebugRenderer();

    void init();

    void end();

    void drawBox(const glm::vec4& destRect, const ColorRGBA8& color, float angle);

    void drawCircle(const glm::vec2& center, const ColorRGBA8 color, float radius);

    void render(const glm::mat4& projectionMatrix, float lineWidth);

    void dispose();

    struct DebugVertex {
        glm::vec2 position;
        ColorRGBA8 color;
    };

private:
    GLSLprogram m_program;
    std::vector<DebugVertex> m_verts;
    std::vector<GLuint> m_indices;
    GLuint m_vbo, m_vao, m_ibo;
    int m_numElements = 0;
};

}


