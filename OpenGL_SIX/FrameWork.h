#pragma once
#include "Scene.h"
static GLuint width, height;
static GLuint shaderProgramID; //--- 세이더 프로그램 이름
static GLuint vertexShader; //--- 버텍스 세이더 객체
static GLuint fragmentShader; //--- 프래그먼트 세이더 객체
static void make_vertexShaders();
static void make_fragmentShaders();
static GLuint make_shaderProgram();
static GLvoid drawScene();
static GLvoid Reshape(int w, int h);
class CFrameWork
{
private:
	CScene*		scene = NULL;
	CCamera		camera;
	bool		isRunning = false;
public:
	CFrameWork();
	~CFrameWork();

	void Init(CScene* startScene);
	void Render();
	void Update();

	void keyboardInput(unsigned char key, int x, int y);
	void mouseInput(int button, int state, int x, int y);
};