#pragma once
#include "Window.h"
#include <vector>
#include <chrono>
#include "../Sprite/Sprite.h"
#include "../World/Scene.h"
#include "../World/Camera.h"
#include "../Sprite/SpriteToRender.h"

class ConsoleRenderer
{
private:
    HANDLE handle;
    int logicalWidth, logicalHeight;
    int realWidth, realHeight;
    std::vector<CHAR_INFO> buffer;
    SMALL_RECT rect;

    std::vector<SpriteToRender> spritesToRender;

public:
    Camera camera;

    ConsoleRenderer(int w, int h);
    void drawPixel(int x, int y, wchar_t ch, WORD color);
    void drawSprite(const Sprite* sprite, float worldX, float worldY, bool flip = false);
    bool isOnCamera(float worldX, float worldY, int w, int h);
    void present();
    void clear();
    void queueDraw(const Sprite* sprite, float worldX, float worldY, bool flip = false);
    void handleResize();

    int getLogicalWidth() { return logicalWidth; }
    int getLogicalHeight() { return logicalHeight; }

    int getRealWidth() { return realWidth; }
    int getRealHeight() { return realHeight; }
};

