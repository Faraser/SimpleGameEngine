#pragma once
#include "Opengl/gl3.h"

struct Position {
    float x;
    float y;
};

struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct Vertex {
 Position position;
 Color color;
};