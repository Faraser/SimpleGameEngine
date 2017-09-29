#pragma once

namespace Engine {

class FpsLimiter {
public:
    FpsLimiter();

    void init(float maxFPS);

    void setMaxFPS(float maxFPS);

    void begin();

    float end();

private:
    void calculateFPS();

    unsigned int _startTicks;

    float _fps;
    float _maxFPS;
    float _frameTime;
};

}
