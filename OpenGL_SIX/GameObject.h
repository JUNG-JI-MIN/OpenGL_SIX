#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Texture.h"
vector<Vertex> create_cube(float x = 1, float y = 1, float z = 1, glm::vec4 color = { 0.5f, 0.5f, 0.5f, 1.0f });
vector<unsigned int> create_cube_index();

class CGameObject
{
private:
	glm::vec3           position = glm::vec3(0.0f);
	glm::quat           rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3           scale = glm::vec3(1.0f);

	CMesh*				mesh = nullptr;
	CTexture*			texture = nullptr;

public:
	CGameObject(glm::vec3 p);
	~CGameObject();

	glm::vec3			GetPosition();
	void				SetPosition(glm::vec3 pos);

	glm::quat			GetRotation();
	void				SetRotation(glm::quat rot);

	glm::vec3			GetScale();
	void				SetScale(glm::vec3 scl);

	void 				SetObject(CMesh* m, CTexture* t);
	glm::mat4			GetModelMatrix();

	void 				Update();
	void 				Render();
};

class RotateRectangle : public CGameObject
{
public:
	RotateRectangle(glm::vec3 p) : CGameObject(p) {}
	~RotateRectangle();

private:
	float angle = 0.0f;
	float d_angle = 1.0f;
};