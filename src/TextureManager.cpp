#include <iostream>

#include "../lib/stb/stb_image.h"

#include "TextureManager.h"

TextureManager::TextureManager(const std::string& _filePath) { loadTexture(_filePath); }

TextureManager::~TextureManager() = default;

void TextureManager::loadTexture(const std::string &_filePath) {
    imageData = stbi_load(_filePath.c_str(), &imageWidth, &imageHeight, nullptr, 4);

    if ( imageData == nullptr ) {
        std::cerr << "Fail load image" << std::endl;
    }

    // Create a OpenGL texture identifer
    glGenTextures(1, &imageTexture);
    glBindTexture(GL_TEXTURE_2D, imageTexture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
}

GLuint TextureManager::getTexture() const { return imageTexture; }

int TextureManager::getWidth() const { return imageWidth; }

int TextureManager::getHeight() const { return imageHeight; }