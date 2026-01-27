#include "Scene.h"

CScene::CScene()
	:camera(
		glm::vec3(0.0f, 0.0f, 0.0f),    // 카메라 위치 (더 높고 멀리)
		glm::vec3(0.0f, 0.0f, 0.0f),     // 바라보는 점 (필드 중심)
		glm::vec3(0.0f, 1.0f, 0.0f)        // 위쪽 방향
	)

{
    light.Set_light();
}


void CScene::Keyboard_Input(unsigned char key, int x, int y)
{
    if (!player) return;

    switch (key)
    {
    case 'w': case 'W':
        player->SetMoveStatus(Up);
        break;
    case 's': case 'S':
        player->SetMoveStatus(Down);
        break;
    case 'a': case 'A':
        player->SetMoveStatus(Left);
        break;
    case 'd': case 'D':
        player->SetMoveStatus(Right);
        break;
    }
}

void CScene::keyboard_UpInput(unsigned char key, int x, int y)
{
    if (!player) return;

    switch (key)
    {
    case 'w': case 'W':
        player->UnsetMoveStatus(Up);
        break;
    case 's': case 'S':
        player->UnsetMoveStatus(Down);
        break;
    case 'a': case 'A':
        player->UnsetMoveStatus(Left);
        break;
    case 'd': case 'D':
        player->UnsetMoveStatus(Right);
        break;
    }
}


void CScene::Mouse_Input(int button, int state, int x, int y)
{
	if (!player) return;
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
	player->SetObject(&meshes[(int)CubeType::White], &textures);

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


void CScene::TraceCameraToPlayer()
{
    if (!player) return;
    glm::vec3 playerD = player->GetMoveDirection();
    glm::vec3 playerPos = player->GetPosition();
    camera.position = playerPos + glm::vec3(-playerD.x * 10,
                                            -playerD.y * 10,
                                            -playerD.z * 10);
	camera.target = playerPos;
}


void CScene::AnimateObjects(float deltaTime)
{
	for (CGameObject* o : gameObjects) {
		o->Update(deltaTime);
	}
	if (player) player->Update(deltaTime);
}

void CScene::Render(GLuint shaderProgramID)
{
    glm::mat4 uProj = camera.getProjectionMatrix();
    glm::mat4 uView = camera.getViewMatrix();
    
	light.Init(shaderProgramID, camera.position);
    GLuint uLoc_v = glGetUniformLocation(shaderProgramID, "v");
    GLuint uLoc_p = glGetUniformLocation(shaderProgramID, "p");
	
    glUniformMatrix4fv(uLoc_v, 1, GL_FALSE, glm::value_ptr(uView));
    glUniformMatrix4fv(uLoc_p, 1, GL_FALSE, glm::value_ptr(uProj));

    for (CGameObject* o : gameObjects) {
        o->Render(shaderProgramID);
    }

    if (player) {
        player->Render(shaderProgramID);
    }
}


CScene::~CScene()
{
	RemoveObjects();
}