#include "Scene.h"

CScene::CScene()
{
	camera.SetCamera(glm::vec3(0.0f, 20.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


void CScene::Keyboard_Input(unsigned char key, int x, int y)
{
    if (player) player->KeyboardEvent(key, x, y);
	if (key == 'p') SpawnWave();
}

void CScene::keyboard_UpInput(unsigned char key, int x, int y)
{
    if (player) player->KeyboardUpEvent(key, x, y);
}


void CScene::Mouse_Input(int button, int state, int x, int y)
{
	if (player) player->MouseEvent(button, state, x, y);
}


void CScene::Mouse_Motion(int x, int y)
{
    if (player) player->MouseMotionEvent(x, y);
}


void CScene::Add_Mesh_Texture()
{
	meshes[(int)CubeType::Blue] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)), create_cube_index());

	meshes[(int)CubeType::Red] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::Green] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::White] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::Black] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), create_cube_index());
	
	meshes[(int)CubeType::Cyan] = CMesh(create_cube(1.0f, 1.0f, 1.0f, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)), create_cube_index());

    meshes[(int)CubeType::Yellow] = CMesh(create_ground_plane(100.0f, 100.0f), create_ground_index());



	for (int i = 0; i < 7; i++) {
		meshes[i].Init();
	}

	textures.Load("Res/silver.png");
}


void CScene::BuildObjects()
{
	int cubeCount = 0;
    Add_Mesh_Texture(); // 메쉬 추가

	player = new PlayerCube(glm::vec3(0.0f, 0.0f, 0.0f));
	player->SetObject(&meshes[(int)CubeType::White], nullptr);

	TileRectangle* ground = new TileRectangle(glm::vec3(0.0f, 0.0f, 0.0f));
	ground->SetObject(&meshes[(int)CubeType::Yellow], &textures);
	gameObjects.push_back(ground);

	camera.position = glm::vec3(0.0f, 20.0f, 30.0f);
}


void CScene::RemoveObjects()
{
	for (int i = 0; i < 7; i++) {
		meshes[i].Delete();
	}

	for (auto& wave : scanwaves) {
		delete wave;
	}

	textures.Delete();

    for (auto& o : gameObjects) {
		delete o;
    }
	gameObjects.clear();

    if (player) {
        delete player;
        player = nullptr;
    }
}


void CScene::SpawnWave() {
	if (player) {
		CScanWave* scanwave = new CScanWave(player->GetPosition());
		scanwaves.push_back(scanwave);
	}
}


void CScene::TraceCameraToPlayer()
{
    if (!player) return;
    glm::vec3 playerD = player->GetMoveDirection();
    glm::vec3 playerPos = player->GetPosition();
    camera.position = playerPos + glm::vec3(-playerD.x * 20,
                                            -playerD.y * 20,
                                            -playerD.z * 20);
	camera.target = playerPos;
}


void CScene::AnimateObjects(float deltaTime)
{
	for (CGameObject* o : gameObjects) {
		o->Update(deltaTime);
	}
	if (player) player->Update(deltaTime);

	for (CScanWave* scanwave : scanwaves) {
		if (scanwave) {
			scanwave->Update(deltaTime);
			if (!scanwave->IsInWaveRange()) {
				delete scanwave;
				scanwave = nullptr;
			}
		}
	}

	TraceCameraToPlayer();
}


void CScene::Render(GLuint shaderProgramID)
{
	// 1-1. 파동 개수 전달
	int waveCount = static_cast<int>(scanwaves.size());
	glUniform1i(glGetUniformLocation(shaderProgramID, "waveCount"), waveCount);

	// 1-2. 각 파동 데이터를 배열로 전달
	for (int i = 0; i < waveCount && i < 10; ++i) {
		std::string base = "waves[" + std::to_string(i) + "].";

		glUniform3fv(glGetUniformLocation(shaderProgramID, (base + "center").c_str()),
			1, glm::value_ptr(scanwaves[i]->GetCenter()));
		glUniform1f(glGetUniformLocation(shaderProgramID, (base + "radius").c_str()),
			scanwaves[i]->GetRadius());
		glUniform1f(glGetUniformLocation(shaderProgramID, (base + "range").c_str()),
			scanwaves[i]->GetRange());
	}

	// 2. 뷰, 프로젝션 행렬 셰이더에 전달
    glm::mat4 uProj = camera.getProjectionMatrix();
    glm::mat4 uView = camera.getViewMatrix();
    
    GLuint uLoc_v = glGetUniformLocation(shaderProgramID, "v");
    GLuint uLoc_p = glGetUniformLocation(shaderProgramID, "p");
	
    glUniformMatrix4fv(uLoc_v, 1, GL_FALSE, glm::value_ptr(uView));
    glUniformMatrix4fv(uLoc_p, 1, GL_FALSE, glm::value_ptr(uProj));

	// 3. 오브젝트 렌더링
    for (CGameObject* o : gameObjects) {
        o->Render(shaderProgramID);
    }

	// 4. 플레이어 렌더링
    if (player) {
        player->Render(shaderProgramID);
    }
}


CScene::~CScene()
{
	RemoveObjects();
}