#pragma once
class SceneManager;
class InputManager;
class AssetManager;
#ifdef _DEBUG
class DebugDraw;
#endif
struct EngineContext
{
	float deltaTime;
	float fixedDeltaTime;
	SceneManager* sceneManager;
	InputManager* inputManager;
	AssetManager* assetManager;
#ifdef _DEBUG
	DebugDraw* debugDraw;
#endif
};