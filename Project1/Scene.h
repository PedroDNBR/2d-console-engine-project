#pragma once
#include <vector>
#include "Sprite.h"
#include "Entity.h"
#include "Player.h"
class ConsoleEngine;

class Scene
{
public:
	Scene(std::vector<std::vector<int>> tilemap) : tilesStructure(tilemap) {}
	void start(ConsoleEngine* engine);
	void update(ConsoleEngine* engine, float deltaTime);
	void destroy();

	bool isTileSolid(float worldX, float worldY, int width, int height);
	bool isTileSolidAtPoint(float worldX, float worldY);

protected:
	std::vector<Entity*> entities;

	std::vector<Sprite*> tilemap;
	std::vector<int> tilemapPhysics;

	std::vector<std::vector<int>> tilesStructure;

	const int positiveXcameraOffset = 60;
	const int negativeXcameraOffset = 60;
	const int positiveYcameraOffset = 10;
	const int negativeYcameraOffset = 34;

	void loadTilemap();

	void setTilemapsOnPosition(ConsoleEngine* engine);

	void CameraFollowTarget(ConsoleEngine* engine, float deltaTime);

};

