#pragma once

#include "Glad/glad.h"  // First, include Glad
#include <GLFW/glfw3.h>  // Then include GLFW (if you're using it)
#define STBI_MALLOC(sz) malloc(sz)
#define STBI_FREE(p) free(p)
#define STBI_REALLOC(p, sz) realloc(p, sz)
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_SIMD 
#define STB_IMAGE_IMPLEMENTATION
#include "std_img.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "VertexBuffer.h"
#include "Texture.h"
#include "Bullet.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "TextRenderer.h"
#include "shader.h"



const float collisionThreshold = 0.1f; // Adjust the value based on your game's requirements


class Enemy {
public:
    glm::vec3 position;
    float fireCooldown;
    bool markForDeletion = false;

    // Add const qualifier to getPosition
    glm::vec3 getPosition() const { return position; }

    void update() {
        position.y -= 0.0088f;
    }
};

bool enemyCollisionLogic(Enemy& enemy, std::vector<Bullet>& bullets) {
    for (auto& bullet : bullets) {
        float distance = glm::length(enemy.getPosition() - bullet.getPosition());
        if (distance < collisionThreshold) {
            bullet.markForDeletion = true;  // Mark the bullet for deletion
            enemy.markForDeletion = true;  // Mark the enemy for deletion
            return true; // Stop checking other bullets for this enemy
        }
    }
    return false;
}

std::string readShaderFromFile(const std::string& shaderPath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    shaderFile.open(shaderPath);
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}