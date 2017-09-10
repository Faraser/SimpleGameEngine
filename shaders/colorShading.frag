#version 330

out vec4 color;
in vec4 fragmentColor;

void main() {
    color = fragmentColor;
}