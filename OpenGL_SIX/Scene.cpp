#include "Scene.h"

CScene::CScene()
{
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			field[x][z] = CubeType::None;
		}
	}
}


void CScene::Keyboard_Input(unsigned char key, int x, int y)
{
	// 키보드 입력 처리 코드 작성
}


void CScene::Mouse_Input(int button, int state, int x, int y)
{
	// 마우스 입력 처리 코드 작성
}


void CScene::GenerateField(int x, int z, CubeType ownerType)
{
	if (x < 0 || x >= 20 || z < 0 || z >= 20) return;
	if (field[x][z] != CubeType::None) return;

	auto it = validNeighbors.find(ownerType);
	if (it == validNeighbors.end()) return;
	
	const vector<CubeType>& candidates = it->second;

	if (candidates.empty()) return;

	std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
	CubeType selectedType = candidates[dist(rng)];
	field[x][z] = selectedType;


	// 재귀적으로 인접한 필드 생성
	GenerateField(x + 1, z, selectedType);
	GenerateField(x - 1, z, selectedType);
	GenerateField(x, z + 1, selectedType);
	GenerateField(x, z - 1, selectedType);
}


void CScene::AddMesh()
{
	meshes[(int)CubeType::BlueCube] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)), create_cube_index());

	meshes[(int)CubeType::RedCube] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::GreenCube] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::WhiteCube] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::BlackCube] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), create_cube_index());
	
	for (int i = 0; i < 5; i++) {
		meshes[i].Init();
	}
}


void CScene::BuildObjects()
{
	int cubeCount = 0;
	AddMesh(); // 메쉬 추가
	GenerateField(10, 10, CubeType::GreenCube); // 필드 생성 시작
	
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			if (field[x][z] != CubeType::None) {
				TileRectangle* obj = new TileRectangle(glm::vec3((x - 10) * 2.0f, 30.0f, (z - 10) * 2.0f));
				obj->SetObject(&meshes[(int)field[x][z]], nullptr);
				gameObjects.push_back(obj);
				cubeCount++;
			}
		}
	}
	// Scene.cpp의 BuildObjects() 끝에 추가
	std::cout << "Meshes created: " << cubeCount << std::endl;
	std::cout << "GameObjects: " << gameObjects.size() << std::endl;
}


void CScene::RemoveObjects()
{
	for (int i = 0; i < 5; i++) {
		meshes[i].Delete();
	}
	gameObjects.clear();
}


void CScene::AnimateObjects(float deltaTime)
{
	for (CGameObject* o : gameObjects) {
		o->Update(deltaTime);
	}
}
void PrintMatrix(const std::string& name, const glm::mat4& mat)
{
	std::cout << "\n=== " << name << " ===" << std::endl;
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++) {
			std::cout << std::setw(8) << mat[j][i] << " ";
		}
		std::cout << "]\n";
	}
}

void CScene::Render(GLuint shaderProgramID, CCamera& camera)
{
    glm::mat4 uProj = camera.getProjectionMatrix();
    glm::mat4 uView = camera.getViewMatrix();

    GLuint uLoc_m = glGetUniformLocation(shaderProgramID, "m");
    GLuint uLoc_v = glGetUniformLocation(shaderProgramID, "v");
    GLuint uLoc_p = glGetUniformLocation(shaderProgramID, "p");
	
    glUniformMatrix4fv(uLoc_v, 1, GL_FALSE, glm::value_ptr(uView));
    glUniformMatrix4fv(uLoc_p, 1, GL_FALSE, glm::value_ptr(uProj));

    for (CGameObject* o : gameObjects) {
        glm::mat4 uModel = o->GetModelMatrix();
        glUniformMatrix4fv(uLoc_m, 1, GL_FALSE, glm::value_ptr(uModel));
        
        o->Render();
    }
}


CScene::~CScene()
{
	RemoveObjects();
}