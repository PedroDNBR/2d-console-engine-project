#pragma once
class InputManager;
class AssetManager;
struct EngineContext
{
	float deltaTime;
	float fixedDeltaTime;
	InputManager* inputManager;
	AssetManager* assetManager;
};