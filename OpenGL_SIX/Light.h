#pragma once
#include "stdafx.h"
// 조명 클래스
typedef struct CLIGHT {
    glm::vec3 position;
    glm::vec3 dir;
    glm::vec3 color;
    int type;
}LIGHT;
class Light {
private:
	LIGHT light;
public:
    Light();
    void Set_light();
    void Init(GLint shaderProgramID, const glm::vec3& cameraPos);
    void position_update(GLint shaderProgramID);
};
