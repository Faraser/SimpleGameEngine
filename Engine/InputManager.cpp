#include "InputManager.h"

namespace Engine {
InputManager::InputManager() : _mouseCoords(0.0f, 0.0f) {

}

InputManager::~InputManager() {

}

void InputManager::update() {
    for (const auto& it : _keyMap) {
        _previousKeyMap[it.first] = it.second;
    }
}

void InputManager::pressKey(unsigned int keyId) {
    _keyMap[keyId] = true;
}

void InputManager::releaseKey(unsigned int keyId) {
    _keyMap[keyId] = false;
}

bool InputManager::isKeyDown(unsigned int keyId) {
    auto it = _keyMap.find(keyId);
    if (it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

bool InputManager::isKeyPressed(unsigned int keyId) {
    if (isKeyDown(keyId) && !wasKeyDown(keyId)) return true;

    return false;
}

void InputManager::setMouseCoords(float x, float y) {
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool InputManager::wasKeyDown(unsigned int keyId) {
    auto it = _previousKeyMap.find(keyId);
    if (it != _previousKeyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

}

