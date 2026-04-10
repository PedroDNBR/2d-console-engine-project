#pragma once
#include "../TilemapManager.h"
#include "../EntityManager.h"
#include "../CollisionManager.h"

class WorldContext
{
private:
	TilemapManager& tilemapManager;
	EntityManager& entityManager;
	CollisionManager& collisionManager;

public:
	WorldContext(TilemapManager& tilemapManager, EntityManager& entityManager, CollisionManager& collisionManager) : tilemapManager(tilemapManager), entityManager(entityManager), collisionManager(collisionManager) {}
	
	template<typename NewEntity>
	NewEntity* createEntity(float posX, float posY);
	void createBackgroundTilemaps(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths, std::vector<std::vector<int>> tileStructure);
	void createTopTilemaps(const EngineContext& engineContext, const std::vector<std::string>& spritesPaths, std::vector<std::vector<int>> tileStructure);
	void createTopTilemapsCollision(std::vector<int> tilemapPhysics);

	bool isTileSolid(float worldX, float worldY, int width, int height) const;
	bool isTileSolidAtPoint(float worldX, float worldY) const;

	Entity* getEntityByTag(uint16_t targetTag) const;
	Entity* collidedWithEntity(float worldX, float worldY, int width, int height) const;
	Entity* collidedWithEntityAtPoint(float worldXMin, float worldXMax, float worldYMin, float worldYMax) const;
	std::vector<Entity*> getAllEntitiesByTag(uint16_t targetTag) const;
	float getDistanceBetweenEntities(const Entity& entityA, const Entity& entityB) const;
};

template<typename NewEntity>
inline NewEntity* WorldContext::createEntity(float posX, float posY)
{
	return entityManager.createEntity<NewEntity>(posX, posY);
}