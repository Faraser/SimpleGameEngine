#pragma once

#include <vector>
#include <string>

namespace Engine {
class IOManager {
public:
    static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
};
}