#include "World1n1.h"

void World1n1::onStart(ViewportInfo& viewportInfo, EngineContext& engineContext, WorldContext& worldContext)
{
	worldContext.createBackgroundTilemaps(
		engineContext,
		{ "./Assets/Sprites/sky" },
		{
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
		}
	);
	worldContext.createTopTilemaps(
		engineContext,
		{ "./Assets/Sprites/ground" },
		{
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
		}
	);
	worldContext.createTopTilemapsCollision(
		{ 1 }
	);
	player = worldContext.createEntity<Player>(10, 30);
}

void World1n1::onUpdate(EngineContext& engineContext, WorldContext& worldContext)
{
}

void World1n1::onFixedUpdate(EngineContext& engineContext, WorldContext& worldContext)
{
	CameraFollowTarget(player, camera, engineContext.fixedDeltaTime);
}

void World1n1::onDestroy(EngineContext& engineContext, WorldContext& worldContext)
{
}

void World1n1::onHandleResize(ViewportInfo& info)
{
}

void World1n1::CameraFollowTarget(Entity* targetEntity, Camera& camera, float fixedDeltaTime)
{
	float playerScreenX = (targetEntity->worldX + (targetEntity->currentFrame->width / 2)) - camera.x;
	float playerScreenY = (targetEntity->worldY + (targetEntity->currentFrame->height / 2)) - camera.y;

	float leftMagin = camera.width * .4f;
	float rightMagin = camera.width * .6f;

	if (playerScreenX < leftMagin)
	{
		camera.x += (playerScreenX - leftMagin) * fixedDeltaTime * cameraFollowSpeed;
	}
	else if (playerScreenX > rightMagin)
	{
		camera.x += (playerScreenX - rightMagin) * fixedDeltaTime * cameraFollowSpeed;
	}

	float topMagin = camera.height * .3f;
	float bottomMagin = camera.height * .7f;

	if (playerScreenY < topMagin)
		camera.y += (playerScreenY - topMagin) * fixedDeltaTime * cameraFollowSpeed;

	if (playerScreenY > bottomMagin)
		camera.y += (playerScreenY - bottomMagin) * fixedDeltaTime * cameraFollowSpeed;
}