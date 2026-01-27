#include "Scene.h"

CScene::CScene()
{
	camera.SetCamera(glm::vec3(0.0f, 20.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    light.Set_light();
}


void CScene::Keyboard_Input(unsigned char key, int x, int y)
{
    if (player) player->KeyboardEvent(key, x, y);
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

	TraceCameraToPlayer();
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