#include "TextureCache.h"
#include "ImageLoader.h"

namespace Engine {
TextureCache::TextureCache() {

};

TextureCache::~TextureCache() {

}

GLTexture TextureCache::getTexture(std::string texturePath) {
    auto mit = _textureMap.find(texturePath);
    if (mit == _textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        _textureMap.insert({texturePath, newTexture});
        return newTexture;
    }

    return mit->second;
}
}
