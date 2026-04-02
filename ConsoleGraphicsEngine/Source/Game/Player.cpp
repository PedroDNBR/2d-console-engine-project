#include "Player.h"
#include "../World/Scene.h"
#include "../Core/InputManager.h"


void Player::onStart(const EngineContext& engineContext, const WorldContext& worldContext)
{
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/mauro"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/maurowalk1"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/maurowalk2"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/maurowalk3"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/maurojump"));
	currentFrame = frames[0];
}

void Player::onUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    


    //    //if ((GetKeyState('W') & 0x8000) && isGrounded) yVelocity = -100.f;

    //move(0, yVelocity * engineContext.deltaTime);

    //bool isMoving = false;

    movementX = 0;

    if (engineContext.inputManager->getKey(KeyCode::KEY_W) && isGrounded)
    {
		jump = true;
    }

    if (engineContext.inputManager->getKey(KeyCode::KEY_A))
    {
        movementX = -1.f;
        // isMoving = true;
        //flipSprite = true;
    }
    if (engineContext.inputManager->getKey(KeyCode::KEY_D))
    {
        movementX = 1.f;
        //isMoving = true;
        //flipSprite = false;
    }

    //if (isMoving)
    //{
    //    animationWalkCycleTimer += engineContext.deltaTime;

    //    if (animationWalkCycleTimer >= 0.18f)
    //    {
    //        animationWalkCycleTimer = 0;
    //        currentFrameIndex++;
    //        if (currentFrameIndex > 3)
    //            currentFrameIndex = 1;
    //    }
    //}
    //else
    //{
    //    currentFrameIndex = 0;
    //}
    //if (isGrounded)
    //    currentFrame = frames[currentFrameIndex];
    //else
    //    currentFrame = frames[4];
}

void Player::onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    if (!isGrounded)
        yVelocity += gravity * engineContext.fixedDeltaTime;

    float newWorldX = worldX + movementX * playerSpeed * engineContext.fixedDeltaTime;
    if (!worldContext.isTileSolid(newWorldX, worldY, currentFrame->width, currentFrame->height))
    {
        worldX = newWorldX;
	}


    float newWorldY = worldY + yVelocity * engineContext.fixedDeltaTime;
    if (worldContext.isTileSolid(worldX, newWorldY, currentFrame->width, currentFrame->height))
    {
        if (yVelocity > 0)
        {
			worldY = std::floor((newWorldY + currentFrame->height) / 16) * 16 - currentFrame->height;
        }
        yVelocity = 0;
    }
    else
    {
        worldY = newWorldY;
    }

    isGrounded = worldContext.isTileSolidAtPoint(worldX, worldY + currentFrame->height) ||
        worldContext.isTileSolidAtPoint(worldX + currentFrame->width - 1, worldY + currentFrame->height);

    if (isGrounded && jump)
    {
        yVelocity = -jumpForce;
    }

    jump = false;
}

void Player::onDestroy()
{
}
