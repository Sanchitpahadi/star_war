#include "Texture.h"
#include "Glad/glad.h"
#include <GLFW/glfw3.h>
#include "std_img.h"
#include <iostream>

Texture::Texture(const char* path) {
    // Generate and bind the texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture image data
    stbi_set_flip_vertically_on_load(true);  // Flip image if necessary
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        // Determine the texture format based on the number of channels
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else
            format = GL_RGB;  // Default to RGB if format is unexpected

        // Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    // Free image data
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);  // Activate the specified texture unit
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture
}
