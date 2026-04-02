#include "InputManager.h"

bool InputManager::getKey(KeyCode key)
{
	return (GetKeyState(key) & 0x8000);
}
