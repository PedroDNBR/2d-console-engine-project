#include "Entity.h"
#include "Scene.h"

void Entity::start() { }

// sample code for testing
int direction = 10;

void Entity::update(float deltaTime) { }

void Entity::destroy()
{
    if (sprite == nullptr) return;
	delete sprite;
	sprite = nullptr;
}

void Entity::move(float x, float y)
{
    float futureWorldXPosition = worldX + x;
    float futureWorldYPosition = worldY + y;

    if (!scene->isTileSolid(futureWorldXPosition, worldY, sprite->width, sprite->height))
    {
        worldX = futureWorldXPosition;
    }

    if (!scene->isTileSolid(worldX, futureWorldYPosition, sprite->width, sprite->height))
    {
        worldY = futureWorldYPosition;
    }
}
