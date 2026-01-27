#pragma once
#include "stdafx.h"
class CCamera {
public:
    glm::vec3           position    =   glm::vec3{ 0,0,0 };
    glm::vec3           target      =   glm::vec3{ 0,0,0 };
    glm::vec3           up          =   glm::vec3{ 0,1,0 };

    float               fovy = 45.0f; 
    float               aspect; 
    float               n = 0.1f;
    float               f = 2000.0f; 
    float               orthoScale = 10.0f;

    CCamera();
    ~CCamera();

    void SetCamera(glm::vec3 pos, glm::vec3 tar, glm::vec3 u);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};