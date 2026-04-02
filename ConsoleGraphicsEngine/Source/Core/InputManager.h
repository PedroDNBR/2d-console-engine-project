#pragma once
#include <Windows.h>
#include "KeyCode.h"

class InputManager
{
public:
	bool getKey(KeyCode key);
	bool getAction();	
};

