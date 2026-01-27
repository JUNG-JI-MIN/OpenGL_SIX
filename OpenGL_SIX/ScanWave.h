#pragma once
#include "stdafx.h"
class CScanWave
{
public:
private:
	glm::vec3					position		= glm::vec3{0.0f};

	float						WaveVelocity	= 0;
	float						WaveRadian		= 0;
	float						WaveRange		= 0;

	float						MaxRange		= 0;
public:
	CScanWave(glm::vec3 p);
	~CScanWave();

	void SetWaveVelocity(float v);
	void SetWaveRadian(float r);
	void SetWaveRange(float rg);

	bool IsInWaveRange();

	// 쉐이더 전달용 함수
	glm::vec3 GetCenter() { return position; }
	float GetRadius() { return WaveRadian; }
	float GetRange() { return WaveRange; }
	float GetMaxRange() { return MaxRange; }

	void Update(float deltatime);
};

