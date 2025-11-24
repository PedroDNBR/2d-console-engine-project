#include "Player.h"
#include "Scene.h"

void Player::update(float deltaTime)
{
    Entity::update(deltaTime);

    if (!isGrounded)
    {
        if (yVelocity < 10000)
            yVelocity += 200.f * deltaTime;
    }

    isGrounded = scene->isTileSolidAtPoint(worldX, worldY + sprite->height + 1) ||
        scene->isTileSolidAtPoint(worldX + sprite->width, worldY + sprite->height + 1);


    if ((GetKeyState('W') & 0x8000) && isGrounded) yVelocity = -100.f;

    move(0, yVelocity * deltaTime);

    if (GetKeyState('A') & 0x8000) move(-30.0f * deltaTime, 0);
    if (GetKeyState('D') & 0x8000) move(30.0f * deltaTime, 0);
    //if (GetKeyState('S') & 0x8000) move(0, 30.0f * deltaTime);
}