#pragma once
#include "Window.h"
#include <vector>
#include <chrono>
#include "../Sprite/Sprite.h"
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

    void resizeWindow(int newWidth, int newHeight);

public:
    ConsoleRenderer(int w, int h);
    void drawPixel(int x, int y, wchar_t ch, WORD color);
    void drawSprite(const Camera& camera, const Sprite* sprite, float worldX, float worldY, bool flip = false);
    void present(const Camera& camera);
    void clear();
    void queueDraw(const Sprite* sprite, float worldX, float worldY, bool flip = false);
    bool hasWindowResized();

    int getLogicalWidth() { return logicalWidth; }
    int getLogicalHeight() { return logicalHeight; }

    int getRealWidth() { return realWidth; }
    int getRealHeight() { return realHeight; }
};

