#pragma once
#include "../../../World/Entity.h"

class Goomba : public Entity
{
public:
    Goomba(float posX, float posY) : Entity(posX, posY) {}

private:
    const float terminalVelocity = 1000.f;
    float yVelocity = 0.0f;
    float movementX = -1;
    float gravity = 120.f;
    float animationWalkCycleTimer = 0;
    float goompaSpeed = 15;
    bool amIInSight = false;
    bool isGrounded = false;

	Entity* targetPlayer;

protected:
    void onStart(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onDestroy() override;
};

