#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
void CTexture::Load(const char* filePath) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "ERROR: Failed to load texture: " << filePath << std::endl;
        return;
    }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // 채널 수에 따라 포맷 결정
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // 텍스처 파라미터 설정 (필수!)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 밉맵 생성
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0); // 언바인드
}

void CTexture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void CTexture::Delete() {
    glDeleteTextures(1, &id);
}