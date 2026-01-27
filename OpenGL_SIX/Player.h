#pragma once
#include "stdafx.h"
#include "GameObject.h"
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
	void					Update(float deltaTime) override;
	void 					SetMoveStatus(unsigned char status);
	void 					UnsetMoveStatus(unsigned char status);
	void					UpdateDirection(float deltaX, float deltaY);

	void					MouseEvent(int button, int state, int x, int y);
	void					MouseMotionEvent(int x, int y);
	void 					KeyboardUpEvent(unsigned char key, int x, int y);
	void 					KeyboardEvent(unsigned char key, int x, int y);

	glm::vec3 				GetMoveDirection() { return moveDirection; }

private:
	unsigned char			moveStatus = None;
	float 					moveSpeed = 10.0f;
	glm::vec3				moveDirection = glm::vec3{ 1.0f , 0.0f , 0.0f };

	float					yaw = -90.0f; // Y축 회전 각도
	float					pitch = 0.0f; // X축 회전 각도
	float					sensitivity = 0.1f;

	float					lastMouseX = 400;
	float					lastMouseY = 300;
	bool					isMousePressed = false;
};