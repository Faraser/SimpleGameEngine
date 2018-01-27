#pragma once

#include "GLTexture.h"
#include <string>

namespace Engine {
class ImageLoader {
public:
    static GLTexture loadPNG(const std::string& filePath);

};
}