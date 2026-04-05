#pragma once
#include <vector>
#include <memory>
#include "TilemapManager.h"
#include "EntityManager.h"
#include "../World/Camera.h"
#include "../World/Entity.h"
#include "../Sprite/SpriteToRender.h"
#include "../Core/ViewportInfo.h"
#include "../Core/Context/EngineContext.h"
#include "Context/WorldContext.h"
#include "../Core/AssetManager.h"

class Scene
{
public:
	void start(ViewportInfo& info, EngineContext& engineContext);
	void update(EngineContext& engineContext);
	void fixedUpdate(EngineContext& engineContext);
	void destroy(EngineContext& engineContext);
	void handleResize(ViewportInfo& info);

	std::vector<SpriteToRender> getEntitiesToRender();

	std::vector<SpriteToRender> getTopTilesToRender();

	std::vector<SpriteToRender> getBackgroundTilesToRender();

	Camera& getCamera() { return camera; }

protected:
	Camera camera;

	virtual void onStart(ViewportInfo& viewportInfo, EngineContext& engineContext, WorldContext& worldContext) = 0;
	virtual void onUpdate(EngineContext& engineContext, WorldContext& worldContext) = 0;
	virtual void onFixedUpdate(EngineContext& engineContext, WorldContext& worldContext) = 0;
	virtual void onDestroy(EngineContext& engineContext, WorldContext& worldContext) = 0;
	virtual void onHandleResize(ViewportInfo& info) = 0;

private:
	std::unique_ptr<TilemapManager> tilemapManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<WorldContext> worldContext;
	std::unique_ptr<CollisionManager> collisionManager;
	std::vector<SpriteToRender> spritesToRender;
};

