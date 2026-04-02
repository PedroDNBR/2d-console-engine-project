#include "WorldContext.h"

void WorldContext::createTilemap(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths, std::vector<std::vector<int>> tileStructure)
{
	tilemapManager.loadTilesSprites(engineContext, spritesPaths);
	tilemapManager.tilesStructure = tileStructure;
}

void WorldContext::createTilemapCollision(std::vector<int> tilemapPhysics)
{
	collisionManager.setTilemapPhysics(tilemapPhysics);
}

bool WorldContext::isTileSolid(float worldX, float worldY, int width, int height) const
{
	return collisionManager.isTileSolid(worldX, worldY, width, height);
}

bool WorldContext::isTileSolidAtPoint(float worldX, float worldY) const
{
	return collisionManager.isTileSolidAtPoint(worldX, worldY);
}


