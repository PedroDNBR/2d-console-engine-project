#include "Goomba.h"
#include "../../../World/Scene.h"
#ifdef _DEBUG
#include "../../../Core/DebugDraw.h"
#endif

void Goomba::Die()
{
    if (!isAlive) return;
    isAlive = false;
    currentFrame = frames[1];
    worldY += currentFrame->height;
}

void Goomba::onStart(const EngineContext& engineContext, const WorldContext& worldContext)
{
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Entties/Enemies/goomba"));
    frames.push_back(&engineContext.assetManager->loadSprite("./Assets/Sprites/Entties/Enemies/goombaflat"));
	currentFrame = frames[0];

    targetPlayer = worldContext.getEntityByTag(1);
}

void Goomba::onUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    if (!isAlive) return;

    if (targetPlayer == nullptr)
    {
        targetPlayer = worldContext.getEntityByTag(1);
        return;
    }
	if (worldContext.getDistanceBetweenEntities(*this, *targetPlayer) < 60)
        amIInSight = true;

	if(!amIInSight)
		return;

    animationWalkCycleTimer += engineContext.deltaTime;

    if (animationWalkCycleTimer >= 0.18f)
    {
        flipSprite = !flipSprite;
        animationWalkCycleTimer = 0;
    }
}

void Goomba::onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
    if (!isAlive) return;

    if (targetPlayer == nullptr)
        return;

    if (!amIInSight)
        return;

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

    float newWorldX = worldX + movementX * goompaSpeed * engineContext.fixedDeltaTime;
    if (!worldContext.isTileSolid(newWorldX, worldY, currentFrame->width, currentFrame->height))
    {
        worldX = newWorldX;
    }

    if (!isGrounded)
    {
        yVelocity += gravity * engineContext.fixedDeltaTime;
        if (yVelocity > terminalVelocity)
            yVelocity = terminalVelocity;
    }
}

void Goomba::onDestroy()
{
}
