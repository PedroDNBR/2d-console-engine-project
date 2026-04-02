#include "Entity.h"
#include "Scene.h"

void Entity::start(const EngineContext& engineContext, const WorldContext& worldContext)
{ 
    onStart(engineContext, worldContext);
}

void Entity::update(const EngineContext& engineContext, const WorldContext& worldContext)
{
	onUpdate(engineContext, worldContext);
}

void Entity::fixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext)
{
	onFixedUpdate(engineContext, worldContext);
}

void Entity::destroy()
{
    onDestroy();
    currentFrame = nullptr;
	frames = std::vector<const Sprite*>();
}
