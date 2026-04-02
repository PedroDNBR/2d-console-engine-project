#include "EntityManager.h"
#include "../Sprite/SpriteImporter.h"
#include "Camera.h"

void EntityManager::start(const EngineContext& engineContext, const WorldContext& worldContext)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->start(engineContext, worldContext);
	}
}

void EntityManager::update(const EngineContext& engineContext, const WorldContext& worldContext)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->update(engineContext, worldContext);
	}
}

void EntityManager::fixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->fixedUpdate(engineContext, worldContext);
	}
}

std::vector<SpriteToRender>& EntityManager::getEntitiesSpritesVisibleOnCamera(const Camera& camera)
{
	entitiesSpritesVisibleOnCamera.clear();
	for (size_t i = 0; i < entities.size(); i++)
	{
		Entity* entity = entities[i].get();
		if (camera.isOnCamera(entity->worldX, entity->worldY, entity->currentFrame->width, entity->currentFrame->height))
		{
			SpriteToRender spriteToRender;
			spriteToRender.sprite = entity->currentFrame;
			spriteToRender.worldX = entity->worldX;
			spriteToRender.worldY = entity->worldY;
			spriteToRender.flip = entity->flipSprite;
			entitiesSpritesVisibleOnCamera.push_back(spriteToRender);
		}
	}

	return entitiesSpritesVisibleOnCamera;
}
