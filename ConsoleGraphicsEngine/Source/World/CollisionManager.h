#pragma once
#include "TilemapManager.h"

class CollisionManager
{
public:
	CollisionManager(TilemapManager& tilemapManager) : tilemapManager(tilemapManager) {}

	bool isTileSolid(float worldX, float worldY, int width, int height);
	bool isTileSolidAtPoint(float worldX, float worldY);

	void setTilemapPhysics(const std::vector<int>& physics) { tilemapPhysics = physics; }

private:
	TilemapManager& tilemapManager;

	std::vector<int> tilemapPhysics;
};

