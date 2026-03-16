#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <locale>

class Window
{
public:
	static void CreateGameWindow(HANDLE* handle, int x, int y);
	static void GetWindowSize(HANDLE* handle, int& width, int& height);
};

