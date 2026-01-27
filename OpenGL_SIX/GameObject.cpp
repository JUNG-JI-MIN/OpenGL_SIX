#include "GameObject.h"
vector<Vertex> create_cube(float x, float y, float z, glm::vec4 color) {
    vector<Vertex> cube_vertices = {
        // 앞면 | Normal: +Z | TexCoords: { {0, 0}, {1, 0}, {1, 1}, {0, 1} }
        { {-x, -y,  z}, color, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} }, // 0 (bottom-left)
        { { x, -y,  z}, color, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} }, // 1 (bottom-right)
        { { x,  y,  z}, color, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} }, // 2 (top-right)
        { {-x,  y,  z}, color, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} }, // 3 (top-left)

        // 뒷면 | Normal: -Z
        { {-x, -y, -z}, color, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} }, // 4 
        { { x, -y, -z}, color, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} }, // 5 
        { { x,  y, -z}, color, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} }, // 6 
        { {-x,  y, -z}, color, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} }, // 7 

        // 왼쪽면 | Normal: -X
        { {-x, -y, -z}, color, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 8
        { {-x, -y,  z}, color, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }, // 9
        { {-x,  y,  z}, color, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} }, // 10
        { {-x,  y, -z}, color, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} }, // 11

        // 오른쪽면 | Normal: +X
        { { x, -y, -z}, color, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }, // 12
        { { x, -y,  z}, color, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 13
        { { x,  y,  z}, color, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} }, // 14
        { { x,  y, -z}, color, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} }, // 15

        // 위면 | Normal: +Y
        { {-x,  y, -z}, color, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} }, // 16 
        { { x,  y, -z}, color, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} }, // 17
        { { x,  y,  z}, color, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} }, // 18
        { {-x,  y,  z}, color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} }, // 19

        // 아래면 | Normal: -Y
        { {-x, -y, -z}, color, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} }, // 20
        { {-x, -y,  z}, color, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} }, // 21
        { { x, -y,  z}, color, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} }, // 22
        { { x, -y, -z}, color, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} }  // 23
    };
    return cube_vertices;
}
vector<unsigned int> create_cube_index() {
    vector<unsigned int> cube_indices = {
        // 앞면
        0, 1, 2,
        0, 2, 3,
        // 뒷면
        4, 7, 6,
        4, 6, 5,

        // 왼쪽면
        8, 9, 10,
        8, 10, 11,
        // 오른쪽면
        12, 15, 14,
        12, 14, 13,
        // 위면
        16, 19, 18,
        16, 18, 17,
        // 아래면
        20, 23, 22,
        20, 22, 21
    };
    return cube_indices;
}
vector<Vertex> create_ground_plane(float width, float depth) {
    glm::vec4 color = { 0.5f, 0.5f, 0.5f, 1.0f };
    float halfWidth = width / 2.0f;
    float halfDepth = depth / 2.0f;

    vector<Vertex> ground_vertices = {
        // Y = -5 높이에 바닥 배치 (아래로 내려감)
        { {-halfWidth, -1.f,  halfDepth}, color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} }, // 0
        { { halfWidth, -1.f,  halfDepth}, color, {0.0f, 1.0f, 0.0f}, {10.0f, 0.0f} }, // 1
        { { halfWidth, -1.f, -halfDepth}, color, {0.0f, 1.0f, 0.0f}, {10.0f, 10.0f} }, // 2
        { {-halfWidth, -1.f, -halfDepth}, color, {0.0f, 1.0f, 0.0f}, {0.0f, 10.0f} }, // 3
    };
    return ground_vertices;
}

vector<unsigned int> create_ground_index() {
    vector<unsigned int> ground_indices = {
        0, 1, 2,
        0, 2, 3,
    };
    return ground_indices;
}
CGameObject::CGameObject(glm::vec3 p)
{
	SetPosition(p);
}


glm::vec3 CGameObject::GetPosition()
{
	return position;
}


void CGameObject::SetPosition(glm::vec3 pos) 
{
	position = pos;
}


void CGameObject::AddPosition(glm::vec3 deltaPos) 
{
    position += deltaPos;
}


glm::quat CGameObject::GetRotation() 
{
	return rotation;
}


void CGameObject::SetRotation(glm::quat rot) 
{
	rotation = rot;
}


glm::vec3 CGameObject::GetScale()
{
	return scale;
}


void CGameObject::SetScale(glm::vec3 scl) 
{
	scale = scl;
}


void CGameObject::SetObject(CMesh* m, CTexture* t)
{
    mesh = m;
	texture = t;
}


void CGameObject::Update(float deltaTime)
{
    // 기본 구현 (아무것도 안 함)
    // 파생 클래스에서 override해서 사용
}


void CGameObject::Render(GLuint shaderProgramID)
{
    glm::mat4 uModel = GetModelMatrix();
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(uModel)));

    GLuint uLoc_m = glGetUniformLocation(shaderProgramID, "m");
    GLuint uLoc_n = glGetUniformLocation(shaderProgramID, "n");
    GLuint uLoc_uTex = glGetUniformLocation(shaderProgramID, "useTexture");
    GLuint uLoc_Tex = glGetUniformLocation(shaderProgramID, "texture1");

    glUniformMatrix3fv(uLoc_n, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(uLoc_m, 1, GL_FALSE, glm::value_ptr(uModel));
	glUniform1i(uLoc_uTex, useTexture ? 1 : 0);
    glUniform1i(uLoc_Tex, 0);

    if (texture) {
        texture->Bind();
    }
	if (mesh) {
		mesh->Draw();
	}
}

glm::mat4 CGameObject::GetModelMatrix() 
{
    return glm::translate(glm::mat4(1.0f), position) *
           glm::mat4_cast(rotation) *
		glm::scale(glm::mat4(1.0f), scale);
}

CGameObject::~CGameObject() 
{

}


void TileRectangle::Update(float deltaTime)
{
    if (position.y <= 0.0f) return;
	glm::vec3 falling = glm::vec3(0.0f, fallingSpeed * deltaTime, 0.0f);
    AddPosition(falling);
}


TileRectangle::~TileRectangle()
{
}


