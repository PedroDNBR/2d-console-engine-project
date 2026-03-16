#pragma once
#include <vector>
#include "../Sprite/Sprite.h"
#include "../World/Entity.h"
#include "../Game/Player.h"
#include <memory>
class ConsoleRenderer;

class Scene
{
public:
	Scene(std::vector<std::vector<int>> tilemap) : tilesStructure(tilemap) {}
	void start(ConsoleRenderer* engine);
	void update(ConsoleRenderer* engine, float deltaTime);
	void destroy();

	bool isTileSolid(float worldX, float worldY, int width, int height);
	bool isTileSolidAtPoint(float worldX, float worldY);

protected:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<Sprite>> spritesUsedInScene;

	std::vector<std::unique_ptr<Sprite>> tilemap;
	std::vector<int> tilemapPhysics;
	std::vector<std::vector<int>> tilesStructure;

	const int positiveXcameraOffset = 60;
	const int negativeXcameraOffset = 60;
	const int positiveYcameraOffset = 10;
	const int negativeYcameraOffset = 34;

	void loadTilemap();

	void setTilemapsOnPosition(ConsoleRenderer* engine);

	void CameraFollowTarget(ConsoleRenderer* engine, float deltaTime);

};

