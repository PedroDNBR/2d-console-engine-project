#include "WorldContext.h"

void WorldContext::createBackgroundTilemaps(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths, std::vector<std::vector<int>> tileStructure)
{
	tilemapManager.loadBackgroundTilesSprites(engineContext, spritesPaths);
	tilemapManager.backgroundTilesStructure = tileStructure;
}

void WorldContext::createTopTilemaps(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths, std::vector<std::vector<int>> tileStructure)
{
	tilemapManager.loadTopTilesSprites(engineContext, spritesPaths);
	tilemapManager.topTilesStructure = tileStructure;
}

void WorldContext::createTopTilemapsCollision(std::vector<int> tilemapPhysics)
{
	collisionManager.setTopTilemapPhysics(tilemapPhysics);
}

bool WorldContext::isTileSolid(float worldX, float worldY, int width, int height) const
{
	return collisionManager.isTileSolid(worldX, worldY, width, height);
}

bool WorldContext::isTileSolidAtPoint(float worldX, float worldY) const
{
	return collisionManager.isTileSolidAtPoint(worldX, worldY);
}

Entity* WorldContext::collidedWithEntity(float worldX, float worldY, int width, int height) const
{
	return collisionManager.collidedWithEntity(worldX, worldY, width, height);
}

Entity* WorldContext::getEntityByTag(uint16_t targetTag) const
{
	return entityManager.getEntityByTag(targetTag);
}

Entity* WorldContext::collidedWithEntityAtPoint(float worldXMin, float worldXMax, float worldYMin, float worldYMax) const
{
	return collisionManager.collidedWithEntityAtPoint(worldXMin, worldXMax, worldYMin, worldYMax);
}

std::vector<Entity*> WorldContext::getAllEntitiesByTag(uint16_t targetTag) const
{
	return entityManager.getAllEntitiesByTag(targetTag);
}

float WorldContext::getDistanceBetweenEntities(const Entity& entityA, const Entity& entityB) const
{
	return entityManager.getDistanceBetweenEntities(entityA, entityB);
}

void WorldContext::DestroyEntity(Entity* entity) const
{
	entityManager.DestroyEntity(entity);
}
void WorldContext::FlushDestroyedEntities() const
{
	entityManager.FlushDestroyedEntities();
}
