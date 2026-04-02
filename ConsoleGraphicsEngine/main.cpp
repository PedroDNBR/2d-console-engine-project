#include <iostream>
#include "Source/Core/ConsoleEngine.h"
#include "Source/Game/Scenes/World1n1.h"

int main() {
    ConsoleEngine engine;

    engine.run(std::make_unique<World1n1>());

    std::cout << "Game Finished\n";
}