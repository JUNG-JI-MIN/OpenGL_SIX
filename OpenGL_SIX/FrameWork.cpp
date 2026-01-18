#include "FrameWork.h"
CFrameWork::CFrameWork()
	:camera(
		glm::vec3(100.0f, 100.0f, 100.0f),    // 카메라 위치 (더 높고 멀리)
		glm::vec3(0.0f, 0.0f, 0.0f),     // 바라보는 점 (필드 중심)
		glm::vec3(0.0f, 1.0f, 0.0f)        // 위쪽 방향
	)
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