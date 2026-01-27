#include "Camera.h"

CCamera::CCamera()
{
}
void CCamera::SetCamera(glm::vec3 pos, glm::vec3 tar, glm::vec3 u) {
    position = pos;
    target = tar;
    up = u;
}
glm::mat4 CCamera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}
glm::mat4 CCamera::getProjectionMatrix() {
    aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    return glm::perspective(glm::radians(fovy), aspect, n, f);
}
CCamera::~CCamera() {
}