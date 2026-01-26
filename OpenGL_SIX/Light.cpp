#include "Light.h"

Light::Light() {
}


void Light::Set_light() {
    light.position = glm::vec3(0.0f, 10.0f, 0.0f);
    light.dir = glm::vec3(0.0f, -1.0f, 0.0f);
    light.color = glm::vec3(1.0f, 1.0f, 1.0f);
    light.type = 0; // ¿¹: 0 = ¹æÇâ±¤, 1 = Á¡±¤¿ø µî
}


void Light::Init(GLint shaderProgramID, const glm::vec3& cameraPos) {
    GLuint u = glGetUniformLocation(shaderProgramID, "light.position");
    glUniform3fv(u, 1, glm::value_ptr(light.position));
    u = glGetUniformLocation(shaderProgramID, "light.dir");
    glUniform3fv(u, 1, glm::value_ptr(light.dir));
    u = glGetUniformLocation(shaderProgramID, "light.color");
    glUniform3fv(u, 1, glm::value_ptr(light.color));
    u = glGetUniformLocation(shaderProgramID, "light.type");
    glUniform1i(u, light.type);

    // viewPos À¯´ÏÆû ¼³Á¤ Ãß°¡
    GLuint viewPosLoc = glGetUniformLocation(shaderProgramID, "viewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));
}


void Light::position_update(GLint shaderProgramID) {
	GLuint u = glGetUniformLocation(shaderProgramID, "light.position");
	glUniform3fv(u, 1, glm::value_ptr(light.position));
}