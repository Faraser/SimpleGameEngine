#version 330

out vec4 color;

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;


void main() {
    float distance = length(fragmentUV);
    color = vec4(fragmentColor.rgb, fragmentColor.a * (pow(0.01, distance) - 0.01));
}