#pragma once
#include "TilemapManager.h"
#include "EntityManager.h"

class CollisionManager
{
public:
	CollisionManager(TilemapManager& tilemapManager, EntityManager& entityManager) : tilemapManager(tilemapManager), entityManager(entityManager) {}

	bool isTileSolid(float worldX, float worldY, int width, int height);
	bool isTileSolidAtPoint(float worldX, float worldY);

	void setTopTilemapPhysics(const std::vector<int>& physics) { topTilemapPhysics = physics; }

	Entity* collidedWithEntity(float worldX, float worldY, int width, int height);
	Entity* collidedWithEntityAtPoint(float worldXMin, float worldXMax, float worldYMin, float worldYMax);

private:
	TilemapManager& tilemapManager;
	EntityManager& entityManager;

	std::vector<int> topTilemapPhysics;
};

