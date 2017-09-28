#include "InputManager.h"

namespace Engine {
InputManager::InputManager() {

}

InputManager::~InputManager() {

}

void InputManager::pressKey(unsigned int keyId) {
    _keyMap[keyId] = true;
}

void InputManager::releaseKey(unsigned int keyId) {
    _keyMap[keyId] = false;
}

bool InputManager::isKeyPressed(unsigned int keyId) {
    auto it = _keyMap.find(keyId);
    if (it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}
}
