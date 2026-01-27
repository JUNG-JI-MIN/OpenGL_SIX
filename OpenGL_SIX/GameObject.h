#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Texture.h"
vector<Vertex> create_cube(float x = 1, float y = 1, float z = 1, glm::vec4 color = { 0.5f, 0.5f, 0.5f, 1.0f });
vector<unsigned int> create_cube_index();

class CGameObject
{
protected:
	glm::vec3           position = glm::vec3(0.0f);
	glm::quat           rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3           scale = glm::vec3(1.0f);

	CMesh*				mesh = nullptr;
	CTexture*			texture = nullptr;

	bool 				useTexture = true;

public:
	CGameObject(glm::vec3 p);
	~CGameObject();

	glm::vec3			GetPosition();
	void				SetPosition(glm::vec3 pos);
	void 				AddPosition(glm::vec3 deltaPos);

	glm::quat			GetRotation();
	void				SetRotation(glm::quat rot);

	glm::vec3			GetScale();
	void				SetScale(glm::vec3 scl);

	void 				SetObject(CMesh* m, CTexture* t);
	glm::mat4			GetModelMatrix();

	virtual void		Update(float deltaTime);
	void 				Render(GLuint shaderProgramID);
};

class TileRectangle : public CGameObject
{
public:
	TileRectangle(glm::vec3 p) : CGameObject(p) {}
	~TileRectangle();
	void				Update(float deltaTime) override;

private:
	float				fallingSpeed = -30.0f;
};

enum Direction : unsigned char {
	None = 0,      // 0000
	Up = 1 << 0, // 0001 (1)
	Down = 1 << 1, // 0010 (2)
	Left = 1 << 2, // 0100 (4)
	Right = 1 << 3  // 1000 (8)
};

class PlayerCube : public CGameObject
{
public:

	PlayerCube(glm::vec3 p) : CGameObject(p) {}
	~PlayerCube() {}
	void				Update(float deltaTime) override;
	void 				SetMoveStatus(unsigned char status);
	void 				UnsetMoveStatus(unsigned char status);

	glm::vec3 			GetMoveDirection() { return moveDirection; }
private:
	unsigned char		moveStatus = None;
	float 				moveSpeed = 10.0f;
	glm::vec3			moveDirection = glm::vec3{ 1.0f , 0.0f , 0.0f };

};