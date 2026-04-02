#include "CollisionManager.h"

bool CollisionManager::isTileSolidAtPoint(float worldX, float worldY)
{
	int tileX = worldX / tilemapManager.tilemap[0]->width;
	int tileY = worldY / tilemapManager.tilemap[0]->height;

	if (tileY < 0 || tileY >= tilemapManager.tilesStructure.size()) return false;
	if (tileX < 0 || tileX >= tilemapManager.tilesStructure[tileY].size()) return false;

	int tileIndex = tilemapManager.tilesStructure[tileY][tileX];

	return tilemapPhysics[tileIndex] == 1;
}

bool CollisionManager::isTileSolid(float worldX, float worldY, int width, int height)
{
	return
		isTileSolidAtPoint(worldX, worldY) ||
		isTileSolidAtPoint(worldX + width - 1, worldY) ||
		isTileSolidAtPoint(worldX, worldY + height - 1) ||
		isTileSolidAtPoint(worldX + width - 1, worldY + height - 1);
}