#pragma once
#include "stdafx.h"
struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 normal;
    glm::vec2 texcoord;
};
class CMesh
{
private:
    GLuint vao; // Vertex Array Object
    GLuint vbo; // Vertex Buffer Object
    GLuint ebo; // Element Buffer Object
    vector<Vertex> vertices; // 버텍스 배열
    vector <unsigned int> indices; // 인덱스
    vector <glm::vec3> normal_vertices;
public:
    CMesh();
    CMesh(const vector<Vertex>& verts, const vector<unsigned int>& inds);
    ~CMesh();
    void Init();
	void Update();
	void Draw();
	void Delete();
};

