#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include <random>
#include <stdint.h>
static std::mt19937 rng{ std::random_device{}() };

// 랜덤으로 큐브를 생성하는 장면 클래스
enum class CubeType {
	Blue,
	Red,
	Green,
	White,
	Black,
	Cyan,
	Yellow,
	COUNT
};

class CScene
{
public:
	CScene();
	~CScene();

	void keyboard_UpInput(unsigned char key, int x, int y);
	void Keyboard_Input(unsigned char key, int x, int y);
	void Mouse_Input(int button, int state, int x, int y);

	void Add_Mesh_Texture(); // 메쉬 추가
	void BuildObjects(); // 매쉬 추가 및 필드생성 후 오브젝트 생성
	void RemoveObjects(); // 오브젝트 삭제

	void TraceCameraToPlayer(); // 카메라를 플레이어 위치로 이동
	void AnimateObjects(float deltaTime); // 오브젝트 애니메이션 처리
	void Render(GLuint shaderProgramID);
private:
	vector<CGameObject*>	gameObjects;
	PlayerCube*				player;
	CCamera					camera;
	CMesh					meshes[7];
	CTexture				textures;
	Light					light;

	int 					numGameObjects = 0;
};