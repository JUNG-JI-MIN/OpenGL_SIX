#include "Player.h"
void PlayerCube::Update(float deltaTime)
{
    glm::vec3 direction = glm::vec3(0.0f);

    // 전방 벡터
    glm::vec3 forward = glm::normalize(moveDirection);

    // 오른쪽 벡터 = forward와 월드 up(0,1,0)의 외적
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (moveStatus & Up) {
        direction += forward;
    }
    if (moveStatus & Down) {
        direction -= forward;
    }
    if (moveStatus & Left) {
        direction -= right;
    }
    if (moveStatus & Right) {
        direction += right;
    }

    if (glm::length(direction) > 0.0f) {
        direction = glm::normalize(direction);
        glm::vec3 movement = direction * moveSpeed * deltaTime;
        movement.y = 0.0f; // 수평 이동만
        AddPosition(movement);
    }
}


void PlayerCube::UpdateDirection(float deltaX, float deltaY)
{
    // 마우스 이동량으로 yaw, pitch 업데이트
    yaw += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;  // Y축은 반대로 (화면 좌표계)

    // pitch 제한 (위아래로 너무 많이 안 보게)
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // yaw, pitch로부터 방향 벡터 계산
    glm::vec3 newDirection;
    newDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newDirection.y = sin(glm::radians(pitch));
    newDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	SetRotation(glm::quat(glm::vec3(0.0f, glm::radians(-yaw), 0.0f)));

    moveDirection = glm::normalize(newDirection);
}


void PlayerCube::KeyboardEvent(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': case 'W':
        SetMoveStatus(Up);
        break;
    case 's': case 'S':
        SetMoveStatus(Down);
        break;
    case 'a': case 'A':
        SetMoveStatus(Left);
        break;
    case 'd': case 'D':
        SetMoveStatus(Right);
        break;
    }
}


void PlayerCube::KeyboardUpEvent(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': case 'W':
        UnsetMoveStatus(Up);
        break;
    case 's': case 'S':
        UnsetMoveStatus(Down);
        break;
    case 'a': case 'A':
        UnsetMoveStatus(Left);
        break;
    case 'd': case 'D':
        UnsetMoveStatus(Right);
        break;
    }
}


void PlayerCube::MouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMousePressed = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isMousePressed = false;
        }
    }
}


void PlayerCube::MouseMotionEvent(int x, int y)
{
    if (lastMouseX == -1) {
        lastMouseX = x;
        lastMouseY = y;
        return;
    }

    // 마우스 이동량 계산
    float deltaX = static_cast<float>(x - lastMouseX);
    float deltaY = static_cast<float>(y - lastMouseY);

    // 플레이어 방향 업데이트
    UpdateDirection(deltaX, deltaY);

    // 현재 위치 저장
    lastMouseX = x;
    lastMouseY = y;
}


void PlayerCube::SetMoveStatus(unsigned char status)
{
    moveStatus |= status;
}


void PlayerCube::UnsetMoveStatus(unsigned char status)
{
    moveStatus &= ~status;
}