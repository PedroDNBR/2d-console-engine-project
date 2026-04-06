#pragma once
#include "../World/Entity.h"

class Player : public Entity
{
public:
    Player(float posX, float posY) : Entity(posX, posY) {}

private:
    bool jump = false;
    float movementX = 0;
    float jumpForce = 110.f;
    float playerSpeed = 30.f;
    float gravity = 120.f;
    const float terminalVelocity = 1000.f;

protected:
    bool isGrounded = false;
    float yVelocity = 0.0f;
    int currentFrameIndex = 0;
    float animationWalkCycleTimer;

    void onStart(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onDestroy() override;
};

