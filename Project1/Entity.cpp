#include "Entity.h"
#include "Scene.h"

void Entity::start() { }

// sample code for testing
int direction = 10;

void Entity::update(float deltaTime) { }

void Entity::destroy()
{
    currentFrame = nullptr;
	frames = std::vector<const Sprite*>();
}

void Entity::move(float x, float y)
{
    float futureWorldXPosition = worldX + x;
    float futureWorldYPosition = worldY + y;

    if (!scene->isTileSolid(futureWorldXPosition, worldY, currentFrame->width, currentFrame->height))
    {
        worldX = futureWorldXPosition;
    }

    if (!scene->isTileSolid(worldX, futureWorldYPosition, currentFrame->width, currentFrame->height))
    {
        worldY = futureWorldYPosition;
    }
}
