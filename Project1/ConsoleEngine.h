#include <windows.h>
#include <vector>
#include <chrono>
#include "Sprite.h"
#include "Scene.h"
#include "Camera.h"

class ConsoleEngine {
private:
    HANDLE handle;
    int logicalWidth, logicalHeight;
    int realWidth, realHeight;
    std::vector<CHAR_INFO> buffer;
    SMALL_RECT rect;
    bool running = true;
    std::chrono::steady_clock::time_point lastFrame;
    float deltaTime = 0.0f;

public:
    Camera camera;
    Scene* currentScene;

    ConsoleEngine(int w, int h);

    bool isRunning() const { return running; }

    void clear();

    void drawPixel(int x, int y, wchar_t ch, WORD color);

    void drawSprite(const Sprite* sprite, float worldX, float worldY, bool flip = false);

    bool isOnCamera(float worldX, float worldY, int w, int h);

    void present();

    void handleInput();

    void run();

    int getLogicalWidth() { return logicalWidth; }
    int getLogicalHeight() { return logicalHeight; }

    int getRealWidth() { return realWidth; }
    int getRealHeight() { return realHeight; }
};