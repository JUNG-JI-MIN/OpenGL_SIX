#include "FrameWork.h"
CFrameWork::CFrameWork()
	:camera(glm::vec3(0.0f, 30.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
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
void CFrameWork::Render()
{
	if (scene != nullptr) {
		scene->Render(shaderProgramID, camera);
	}
}
void CFrameWork::Update()
{
	if (scene != nullptr) {
		scene->AnimateObjects();
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