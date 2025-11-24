#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player(float posX, float posY) : Entity(posX, posY) {}

    void update(float deltaTime);

protected:
    bool isGrounded = false;
    float yVelocity = 0.0f;
};

