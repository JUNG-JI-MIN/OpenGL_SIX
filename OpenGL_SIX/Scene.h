#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <map>
#include <random>
static std::mt19937 rng{ std::random_device{}() };

// 랜덤으로 큐브를 생성하는 장면 클래스
enum class CubeType {
	BlueCube,
	RedCube,
	GreenCube,
	WhiteCube,
	BlackCube,
	None
};
// 각 큐브 타입별로 인접할 수 있는 큐브 타입 정의
static const std::map<CubeType, vector<CubeType>> validNeighbors = {
	{ CubeType::GreenCube, { CubeType::GreenCube, CubeType::BlueCube, CubeType::WhiteCube } },
	{ CubeType::BlueCube, { CubeType::BlueCube, CubeType::GreenCube } },
	{ CubeType::WhiteCube, { CubeType::WhiteCube, CubeType::GreenCube, CubeType::RedCube } },
	{ CubeType::RedCube, { CubeType::BlackCube } },
	{ CubeType::BlackCube, { CubeType::GreenCube, CubeType::BlueCube, CubeType::WhiteCube, CubeType::BlackCube } }
};

class CScene
{
public:
	CScene();
	~CScene();

	void Keyboard_Input(unsigned char key, int x, int y);
	void Mouse_Input(int button, int state, int x, int y);

	void GenerateField(int x, int z, CubeType ownerType); // 필드 생성
	void AddMesh(); // 메쉬 추가
	void BuildObjects(); // 매쉬 추가 및 필드생성 후 오브젝트 생성
	void RemoveObjects(); // 오브젝트 삭제
	void AnimateObjects(float deltaTime); // 오브젝트 애니메이션 처리
	void Render(GLuint shaderProgramID, CCamera& Camera);
private:
	vector<CGameObject*>	gameObjects;
	CMesh					meshes[6];
	CubeType				field[20][20] = { CubeType ::None};
	int 					numGameObjects = 0;
};