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

    isGrounded = scene->isTileSolidAtPoint(worldX, worldY + currentFrame->height + 1) ||
        scene->isTileSolidAtPoint(worldX + currentFrame->width, worldY + currentFrame->height + 1);


    if ((GetKeyState('W') & 0x8000) && isGrounded) yVelocity = -100.f;

    move(0, yVelocity * deltaTime);

    bool isMoving = false;

    if (GetKeyState('A') & 0x8000)
    {
        move(-30.0f * deltaTime, 0);
        isMoving = true;
        flipSprite = true;
    }
    else if (GetKeyState('D') & 0x8000)
    {
        move(30.0f * deltaTime, 0);
        isMoving = true;
        flipSprite = false;
    }
    if (isMoving)
    {
		animationWalkCycleTimer += deltaTime;

        if(animationWalkCycleTimer >= 0.18f)
        {
            animationWalkCycleTimer = 0;
            currentFrameIndex++;
            if (currentFrameIndex > 3)
                currentFrameIndex = 1;
		}
    }
    else
    {
        currentFrameIndex = 0;
    }
    if(isGrounded)
        currentFrame = frames[currentFrameIndex];
    else
		currentFrame = frames[4];
}