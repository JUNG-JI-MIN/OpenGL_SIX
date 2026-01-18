#pragma once
#include "stdafx.h"
class CCamera {
public:
    glm::vec3           position;
    glm::vec3           target;
    glm::vec3           up;

    float               fovy = 45.0f; 
    float               aspect; 
    float               n = 0.1f;
    float               f = 150.0f; 
    float               orthoScale = 10.0f;

    CCamera(glm::vec3 pos, glm::vec3 tar, glm::vec3 u);
    ~CCamera();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};
