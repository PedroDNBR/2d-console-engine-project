#pragma once
#include "Sprite.h"
class Scene;

class Entity
{
public:
    Scene* scene;

    const Sprite* currentFrame = nullptr;
    std::vector<const Sprite*> frames;

    bool flipSprite = false;

    float worldX, worldY;

    Entity(float posX, float posY) : worldX(posX), worldY(posY) {}
    
    virtual void start();
    virtual void update(float deltaTime);
    virtual void destroy();

    virtual void move(float x, float y);
};

