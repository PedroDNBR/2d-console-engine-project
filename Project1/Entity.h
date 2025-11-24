#pragma once
#include "Sprite.h"
class Scene;

class Entity
{
public:
    Scene* scene;

    Sprite* sprite;
    float worldX, worldY;

    Entity(float posX, float posY) : worldX(posX), worldY(posY) {}
    
    virtual void start();
    virtual void update(float deltaTime);
    virtual void destroy();

    virtual void move(float x, float y);
};

