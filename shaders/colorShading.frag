#version 330

out vec4 color;
in vec4 fragmentColor;

uniform float time;

void main() {
    color = fragmentColor * abs(sin(time));
}