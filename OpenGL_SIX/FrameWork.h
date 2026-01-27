#pragma once
#include "Scene.h"
#include "Time.h"
class CFrameWork
{
private:
	CScene*		scene = NULL;
	CTimer		timer;
	bool		isRunning = false;
public:
	CFrameWork();
	~CFrameWork();

	void Init(CScene* startScene);
	void Render(GLint shaderProgramID);
	void Update();

	void keyboardUpInput(unsigned char key, int x, int y);
	void keyboardInput(unsigned char key, int x, int y);
	void mouseInput(int button, int state, int x, int y);
};