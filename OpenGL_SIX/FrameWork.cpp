#include "FrameWork.h"
CFrameWork::CFrameWork()
{
}
CFrameWork::~CFrameWork()
{
	if (scene != nullptr) {
		delete scene;
		scene = nullptr;
	}
}
void CFrameWork::Init(CScene* startScene)
{
	scene = startScene;
	if (scene != nullptr) {
		scene->BuildObjects();
	}
}
void CFrameWork::Render(GLint shaderProgramID)
{
	if (scene != nullptr) {
		scene->Render(shaderProgramID);
	}
}
void CFrameWork::Update()
{
	timer.Update();

	if (scene != nullptr) {
		scene->AnimateObjects(timer.GetDeltaTime());
	}
}
void CFrameWork::keyboardUpInput(unsigned char key, int x, int y) {
	if (scene != nullptr) {
		scene->keyboard_UpInput(key, x, y);
	}
}
void CFrameWork::keyboardInput(unsigned char key, int x, int y) {
	if (scene != nullptr) {
		scene->Keyboard_Input(key, x, y);
	}
}
void CFrameWork::mouseInput(int button, int state, int x, int y) {
	if (scene != nullptr) {
		scene->Mouse_Input(button, state, x, y);
	}
}
void CFrameWork::mousemove(int x, int y) {
	if (scene != nullptr) {
		scene->Mouse_Motion(x, y);
	}
}