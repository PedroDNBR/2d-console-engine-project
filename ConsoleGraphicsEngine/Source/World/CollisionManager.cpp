#include "CollisionManager.h"

bool CollisionManager::isTileSolidAtPoint(float worldX, float worldY)
{
	int tileX = worldX / tilemapManager.topTilemap[0]->width;
	int tileY = worldY / tilemapManager.topTilemap[0]->height;

	if (tileY < 0 || tileY >= tilemapManager.topTilesStructure.size()) return false;
	if (tileX < 0 || tileX >= tilemapManager.topTilesStructure[tileY].size()) return false;

	int tileIndex = tilemapManager.topTilesStructure[tileY][tileX];

	if (tileIndex < 1) return 0;

	return topTilemapPhysics[tileIndex - 1] == 1;
}

bool CollisionManager::isTileSolid(float worldX, float worldY, int width, int height)
{
	return
		isTileSolidAtPoint(worldX, worldY) ||
		isTileSolidAtPoint(worldX + width - 1, worldY) ||
		isTileSolidAtPoint(worldX, worldY + height - 1) ||
		isTileSolidAtPoint(worldX + width - 1, worldY + height - 1);
}

Entity* CollisionManager::collidedWithEntity(float worldX, float worldY, int width, int height)
{
	for (int i = 0; i < entityManager.entities.size(); i++)
	{
		Entity* entity = entityManager.entities[i].get();
		if (entity->worldX < worldX + width &&
			entity->worldX + entity->currentFrame->width > worldX &&
			entity->worldY < worldY + height &&
			entity->worldY + entity->currentFrame->height > worldY)
		{
			return entity;
		}
	}
	return nullptr;
}

Entity* CollisionManager::collidedWithEntityAtPoint(float worldXMin, float worldXMax, float worldYMin, float worldYMax)
{
	for (int i = 0; i < entityManager.entities.size(); i++)
	{
		Entity* entity = entityManager.entities[i].get();
		if( entity->worldX < worldXMax &&
			entity->worldX + entity->currentFrame->width > worldXMin &&
			entity->worldY < worldYMax &&
			entity->worldY + entity->currentFrame->height > worldYMin)
		{
			return entity;
		}
	}
	return nullptr;
}
