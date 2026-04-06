#include "Player.h"
#include "../World/Scene.h"
#include "../Core/InputManager.h"


void Player::onStart(const EngineContext& engineContext, const WorldContext& worldContext)
{
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Player/mauro"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Player/maurowalk1"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Player/maurowalk2"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Player/maurowalk3"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Player/maurojump"));
	currentFrame = frames[0];
}

void Player::onUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    bool isMoving = false;

    movementX = 0;

    if (engineContext.inputManager->getKey(KeyCode::KEY_W) && isGrounded)
    {
		jump = true;
    }

    if (engineContext.inputManager->getKey(KeyCode::KEY_A))
    {
        movementX = -1.f;
        isMoving = true;
        flipSprite = true;
    }
    if (engineContext.inputManager->getKey(KeyCode::KEY_D))
    {
        movementX = 1.f;
        isMoving = true;
        flipSprite = false;
    }

    if (isMoving)
    {
        animationWalkCycleTimer += engineContext.deltaTime;

        if (animationWalkCycleTimer >= 0.18f)
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
    if (isGrounded)
        currentFrame = frames[currentFrameIndex];
    else
        currentFrame = frames[4];
}

void Player::onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    isGrounded = worldContext.isTileSolidAtPoint(worldX, worldY + currentFrame->height + 1) ||
        worldContext.isTileSolidAtPoint(worldX + currentFrame->width - 1, worldY + currentFrame->height + 1);

    float newWorldY = worldY + yVelocity * engineContext.fixedDeltaTime;
    if (worldContext.isTileSolid(worldX, newWorldY + 1, currentFrame->width, currentFrame->height))
    {
        yVelocity = 0;
		newWorldY = (int)((worldY + currentFrame->height) / currentFrame->height) * currentFrame->height - currentFrame->height - 1;
    }
    else
    {
        worldY = newWorldY;
    }

    float newWorldX = worldX + movementX * playerSpeed * engineContext.fixedDeltaTime;
    if (!worldContext.isTileSolid(newWorldX, worldY, currentFrame->width, currentFrame->height))
    {
        worldX = newWorldX;
    }

    if (isGrounded && jump)
    {
        yVelocity = -jumpForce;
    }
    if(!isGrounded)
    {
        yVelocity += gravity * engineContext.fixedDeltaTime;
        if (yVelocity > terminalVelocity)
            yVelocity = terminalVelocity;
	}

    jump = false;
}

void Player::onDestroy()
{
}
