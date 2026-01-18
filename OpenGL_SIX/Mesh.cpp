#include "Mesh.h"
CMesh::CMesh(const vector<Vertex>& verts, const vector<unsigned int>& inds)
	:vao(0), vbo(0), ebo(0)
{
	vertices = verts;
	indices = inds;
}
CMesh::CMesh()
{
}
void CMesh::Init()
{
    std::cout << "Init() called: vertices=" << vertices.size()
        << ", indices=" << indices.size() << std::endl;

    if (vertices.empty() || indices.empty()) {
        std::cerr << "ERROR: Empty vertex or index data!" << std::endl;
        return;
    }
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 정점 속성 설정 (position, color 등)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
}


void CMesh::Update() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
}


void CMesh::Draw()
{
    glBindVertexArray(vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


void CMesh::Delete()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

CMesh::~CMesh()
{
    Delete();
}