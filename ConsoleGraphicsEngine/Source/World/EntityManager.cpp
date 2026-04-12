#include <algorithm>
#include <iterator>
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

void EntityManager::DestroyEntity(Entity* entity)
{
	entitiesToDestroy.push_back(entity);
}

void EntityManager::FlushDestroyedEntities()
{
	for (Entity* entityToDestroy : entitiesToDestroy)
	{
		entityToDestroy->destroy();
		entities.erase(
			std::remove_if(
				entities.begin(),
				entities.end(),
				[entityToDestroy](const std::unique_ptr<Entity>& entity) {
					return entity.get() == entityToDestroy;
				}),
			entities.end()
		);
	}
	entitiesToDestroy.clear();
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

Entity* EntityManager::getEntityByTag(uint16_t targetTag)
{
	auto iterator = std::find_if(
		entities.begin(),
		entities.end(),
		[targetTag](const std::unique_ptr<Entity>& entity) {
			return entity->tag == targetTag;
		}
	);

	if(iterator != entities.end())
		return iterator->get();

	return nullptr;
}

std::vector<Entity*> EntityManager::getAllEntitiesByTag(uint16_t targetTag)
{
	std::vector<Entity*> result;
	for (const auto& entity : entities)
	{
		if (entity->tag == targetTag)
			result.push_back(entity.get()); // extrai o raw pointer aqui
	}
	return result;
}

float EntityManager::getDistanceBetweenEntities(const Entity& entityA, const Entity& entityB)
{
	float deltaX = entityA.worldX - entityB.worldX;
	float deltaY = entityA.worldY - entityB.worldY;
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}
