#include <iostream>
#include <utility>

#include "../lib/stb/stb_image.h"

#include "TextureManager.h"

TextureManager::TextureManager(std::string  _filePath) : filePath(std::move(_filePath)) {  }

TextureManager::~TextureManager() { clearTexture(); };

bool TextureManager::loadTexture() {
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, nullptr, 4);

    if ( imageData == nullptr ) {
        std::cerr << "Fail load image" << '\n';
        return false;
    }

    // Create a OpenGL texture identifer
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);

    return true;
}

void TextureManager::useTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint& TextureManager::getTexture() { return textureID; }

int TextureManager::getWidth() const { return width; }

int TextureManager::getHeight() const { return height; }

void TextureManager::clearTexture() { glDeleteTextures(1, &textureID); }