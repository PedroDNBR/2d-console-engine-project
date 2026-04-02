#pragma once
#include "../../World/Scene.h"
#include "../Player.h"

class World1n1 : public Scene
{
protected:
	void onStart(ViewportInfo& viewportInfo, EngineContext& engineContext, WorldContext& worldContext) override;
	void onUpdate(EngineContext& engineContext, WorldContext& worldContext) override;
	void onFixedUpdate(EngineContext& engineContext, WorldContext& worldContext) override;
	void onDestroy(EngineContext& engineContext, WorldContext& worldContext) override;
	void onHandleResize(ViewportInfo& info) override;

private:
	const int positiveXcameraOffset = 60;
	const int negativeXcameraOffset = 60;
	const int positiveYcameraOffset = 10;
	const int negativeYcameraOffset = 34;

	Player* player;

	int cameraFollowSpeed = 30;

	void CameraFollowTarget(Entity* targetEntity, Camera&, float fixedDeltaTime);

};

