#pragma once

#include "TextureCache.h"
#include "GLTexture.h"
#include "string"

namespace Engine {
    class ResourceManager {
    public:
        static GLTexture getTexture(std::string texturePath);

    private:
        static TextureCache _textureCache;
    };
}
