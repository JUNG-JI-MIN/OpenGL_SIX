#include "Time.h"
CTimer::CTimer()
    : deltaTime(0.0f), totalTime(0.0f)
{
    lastTime = std::chrono::high_resolution_clock::now();
    currentTime = lastTime;
}


CTimer::~CTimer()
{
}


void CTimer::Update()
{
    currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();

    totalTime += deltaTime;

    lastTime = currentTime;
}


float CTimer::GetDeltaTime() const
{
    return deltaTime;
}


float CTimer::GetTotalTime() const
{
    return totalTime;
}


int CTimer::GetFPS() const
{
    if (deltaTime > 0.0f) {
        return static_cast<int>(1.0f / deltaTime);
    }
    return 0;
}
