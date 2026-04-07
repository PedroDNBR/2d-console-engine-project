#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"
#include "../Sprite/SpriteToRender.h"

class Camera;

class EntityManager
{
public:
	std::vector<std::unique_ptr<Entity>> entities;

	void start(const EngineContext& engineContext, const WorldContext& worldContext);
	void update(const EngineContext& engineContext, const WorldContext& worldContext);
	void fixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext);
	template<typename NewEntity>
	NewEntity* createEntity(float posX, float posY);
	std::vector<SpriteToRender>& getEntitiesSpritesVisibleOnCamera(const Camera& camera);

	Entity* getEntityByTag(uint16_t targetTag);
	std::vector<Entity*> getAllEntitiesByTag(uint16_t targetTag);
	float getDistanceBetweenEntities(const Entity& entityA, const Entity& entityB);


private:
	std::vector<SpriteToRender> entitiesSpritesVisibleOnCamera;
};

template<typename NewEntity>
inline NewEntity* EntityManager::createEntity(float posX, float posY)
{
	static_assert(std::is_base_of<Entity, NewEntity>::value, "NewEntity must be a subclass of Entity");

	auto entity = std::make_unique<NewEntity>(posX, posY);
	NewEntity* entityPtr = entity.get();
	entities.push_back(std::move(entity));
	return entityPtr;
}
