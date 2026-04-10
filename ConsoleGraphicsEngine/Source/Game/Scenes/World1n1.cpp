#include "World1n1.h"

void World1n1::onStart(ViewportInfo& viewportInfo, EngineContext& engineContext, WorldContext& worldContext)
{
	worldContext.createBackgroundTilemaps(
		engineContext,
		{ 
			"./Assets/Sprites/SkyScenarioElements/sky"
		},
		{
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		}
	);
	worldContext.createTopTilemaps(
		engineContext,
		{ 
			"./Assets/Sprites/GroundScenarioElements/ground",
			"./Assets/Sprites/GroundScenarioElements/brick",
			"./Assets/Sprites/GroundScenarioElements/leftbush",
			"./Assets/Sprites/GroundScenarioElements/centerbush",
			"./Assets/Sprites/GroundScenarioElements/rightbush",
			"./Assets/Sprites/GroundScenarioElements/trianglebushside",
			"./Assets/Sprites/GroundScenarioElements/trianglebushcenter",
			"./Assets/Sprites/GroundScenarioElements/trianglebushtop",
			"./Assets/Sprites/GroundScenarioElements/topleftpipe",
			"./Assets/Sprites/GroundScenarioElements/toprightpipe",
			"./Assets/Sprites/GroundScenarioElements/bottomleftpipe",
			"./Assets/Sprites/GroundScenarioElements/bottomrightpipe",
			"./Assets/Sprites/SkyScenarioElements/topleftcloud",
			"./Assets/Sprites/SkyScenarioElements/toprightcloud",
			"./Assets/Sprites/SkyScenarioElements/bottomleftcloud",
			"./Assets/Sprites/SkyScenarioElements/bottomrightcloud", 
		},
		{
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,9,10,0,0,0,0,0,0,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 0,0,0,0,0,0,3,4,5,0,6,7,-6,0,0,0,3,5,0,0,11,12,0,0,0,0,0,0,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
		}
	);
	worldContext.createTopTilemapsCollision(
		{ 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }
	);
	player = worldContext.createEntity<Player>(10, 128);
	player->tag = 1;
	goombas.push_back(worldContext.createEntity<Goomba>(240, 128));

	for (size_t i = 0; i < goombas.size(); i++)
	{
		goombas[i]->tag = 2;
	}
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