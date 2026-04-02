#pragma once
#include "../Sprite/Sprite.h"

struct EngineContext;
class WorldContext;

class Entity
{
public:
    const Sprite* currentFrame = nullptr;
    std::vector<const Sprite*> frames;

    bool flipSprite = false;

    float worldX, worldY;

    Entity(float posX, float posY) : worldX(posX), worldY(posY) {}
    
    void start(const EngineContext& engineContext, const WorldContext& worldContext);
    void update(const EngineContext& engineContext, const WorldContext& worldContext);
    void fixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext);
    void destroy();

protected:
    virtual void onStart(const EngineContext& engineContext, const WorldContext& worldContext) = 0;
    virtual void onUpdate(const EngineContext& engineContext, const WorldContext& worldContext) = 0;
    virtual void onFixedUpdate(const EngineContext& engineContext, const WorldContext& worldContext) = 0;
    virtual void onDestroy() = 0;
};

