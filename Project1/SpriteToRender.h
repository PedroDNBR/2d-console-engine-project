#pragma once
class Sprite;
struct SpriteToRender
{
	const Sprite* sprite;
	float worldX;
	float worldY;
	bool flip = false;
};