#include "ScanWave.h"

CScanWave::CScanWave(glm::vec3 p)
{
	WaveVelocity = 30.0f;
	WaveRadian = 0.0f;
	WaveRange = 10.0f;
	MaxRange = 50.0f;
	position = p;
}


CScanWave::~CScanWave()
{
}


void CScanWave::SetWaveVelocity(float v) {
	WaveVelocity = v;
}


void CScanWave::SetWaveRadian(float r) {
	WaveRadian = r;
}


void CScanWave::SetWaveRange(float rg) {
	WaveRange = rg;
}


bool CScanWave::IsInWaveRange() {
	return (WaveRadian <= MaxRange);
}


void CScanWave::Update(float deltatime) {
	WaveRadian += WaveVelocity * deltatime;
}