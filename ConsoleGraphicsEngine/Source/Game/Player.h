#pragma once
#include "../World/Entity.h"

class Player : public Entity
{
public:
    Player(float posX, float posY) : Entity(posX, posY) {}

private:
    const float terminalVelocity = 1000.f;
    float yVelocity = 0.0f;
    float movementX = 0;
    float jumpForce = 90.f;
    float playerSpeed = 30.f;
    float gravity = 120.f;
    float animationWalkCycleTimer = 0;
    bool isGrounded = false;
    bool jump = false;
    int currentFrameIndex = 0;

protected:
    void onStart(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext) override;
    void onDestroy() override;
};

