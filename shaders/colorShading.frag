#version 330

out vec4 color;

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

uniform sampler2D mySampler;

void main() {
    vec4 textureColor = texture(mySampler, fragmentUV);

    color = fragmentColor * textureColor;
}