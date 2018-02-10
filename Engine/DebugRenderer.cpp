#include <OpenGL/gl3.h>
#include "DebugRenderer.h"


const float PI = 3.14159265358979f;
namespace {
const char* VERT_SRC = R"(
#version 330

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec4 vertexColor;

 out vec2 fragmentPosition;
 out vec4 fragmentColor;

 uniform mat4 P;

 void main() {
     gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
     gl_Position.z = 0.0;
     gl_Position.w = 1.0;
     fragmentPosition = vertexPosition;
     fragmentColor = vertexColor;
 }
)";

const char* FRAG_SRC = R"(
#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

void main() {

    color = fragmentColor;
}
)";
}

namespace Engine {

DebugRenderer::DebugRenderer() {}

DebugRenderer::~DebugRenderer() {
    dispose();
}

void DebugRenderer::init() {
    // Shader init
    m_program.compileShadersFromSource(VERT_SRC, FRAG_SRC);
    m_program.addAttribute("vertexPosition");
    m_program.addAttribute("vertexColor");
    m_program.linkShaders();

    // Set up buffers
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*) offsetof(DebugVertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*) offsetof(DebugVertex, color));

    glBindVertexArray(0);
}

void DebugRenderer::end() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // Orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    // Orphan the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_numElements = m_indices.size();
    m_indices.clear();
    m_verts.clear();
}

void DebugRenderer::drawBox(const glm::vec4& destRect, const ColorRGBA8& color, float angle) {
    auto rotatePoint = [](glm::vec2 pos, float angle) -> glm::vec2 {
        return glm::vec2(pos.x * cos(angle) - pos.y * sin(angle), pos.x * sin(angle) + pos.y * cos(angle));
    };

    size_t i = m_verts.size();
    m_verts.resize(m_verts.size() + 4);

    glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    glm::vec2 positionOffset(destRect.x, destRect.y);

    // rotate the points
    m_verts[i].position = rotatePoint(tl, angle) + halfDims + positionOffset;
    m_verts[i + 1].position = rotatePoint(bl, angle) + halfDims + positionOffset;
    m_verts[i + 2].position = rotatePoint(br, angle) + halfDims + positionOffset;
    m_verts[i + 3].position = rotatePoint(tr, angle) + halfDims + positionOffset;

    for (size_t j = i; j < i + 4; j++) {
        m_verts[j].color = color;
    }

    m_indices.reserve(m_indices.size() + 8);
    m_indices.push_back(i);
    m_indices.push_back(i + 1);

    m_indices.push_back(i + 1);
    m_indices.push_back(i + 2);

    m_indices.push_back(i + 2);
    m_indices.push_back(i + 3);

    m_indices.push_back(i + 3);
    m_indices.push_back(i);
}

void DebugRenderer::drawCircle(const glm::vec2& center, const ColorRGBA8 color, float radius) {
    static const int NUM_VERTS = 100;
    int start = m_verts.size();
    m_verts.resize(m_verts.size() + NUM_VERTS);

    for (int i = 0; i < NUM_VERTS; i++) {
        float angle = static_cast<float>(i) / NUM_VERTS * PI * 2.0f;
        m_verts[start + i].position.x = cos(angle) * radius + center.x;
        m_verts[start + i].position.y = sin(angle) * radius + center.y;
        m_verts[start + i].color = color;
    }

    // Set up indices for indexed drawing
    m_indices.reserve(m_indices.size() + NUM_VERTS * 2);
    for (int i = 0; i < NUM_VERTS - 1; i++) {
        m_indices.push_back(start + i);
        m_indices.push_back(start + i + 1);
    }

    m_indices.push_back(start + NUM_VERTS - 1);
    m_indices.push_back(start);
}

void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth) {
    m_program.use();

    GLint pUniform = m_program.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    glLineWidth(lineWidth);

    glBindVertexArray(m_vao);
    glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_program.unuse();
}

void DebugRenderer::dispose() {
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }

    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
    }

    if (m_ibo) {
        glDeleteBuffers(1, &m_ibo);
    }

    m_program.dispose();
}

}
