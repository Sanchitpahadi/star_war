#ifndef BULLET_H
#define BULLET_H

#include <glm/glm.hpp>

class Bullet {
    glm::vec3 position;
    float speed = 0.1f;
public:
    bool markForDeletion = false;

    Bullet(float startX, float startY) : position(startX, startY, 0.0f) {}

    void PlayerBulletUpdate() {
        position.y += speed;
    }

  

    glm::vec3 getPosition() const { return position; }
};

#endif
