#pragma once
#include "stdafx.h"
#include <stb_image.h>
class CTexture {
private:
    GLuint id;
    int width, height;
    int channels;
public:
    void Load(const char* filePath);
    void Bind();
	void Unbind();
    void Delete();
    GLuint GetID() const { return id; }
};