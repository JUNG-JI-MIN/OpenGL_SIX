#pragma once
#include "Scene.h"
#include "Time.h"
class CFrameWork
{
private:
	CScene*		scene = NULL;
	CCamera		camera;
	CTimer		timer;
	bool		isRunning = false;
public:
	CFrameWork();
	~CFrameWork();

	void Init(CScene* startScene);
	void Render(GLint shaderProgramID);
	void Update();

	void keyboardInput(unsigned char key, int x, int y);
	void mouseInput(int button, int state, int x, int y);
};