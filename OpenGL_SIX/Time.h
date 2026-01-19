#pragma once
#include <chrono>

class CTimer
{
private:
    std::chrono::high_resolution_clock::time_point lastTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    float deltaTime;
    float totalTime;

public:
    CTimer();
    ~CTimer();

    void Update();
    float GetDeltaTime() const;     // 프레임 간 경과 시간 (초 단위)
    float GetTotalTime() const;     // 프로그램 시작 후 총 경과 시간
    int GetFPS() const;             // 현재 FPS
};