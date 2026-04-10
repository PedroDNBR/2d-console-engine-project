#pragma once
#include <vector>
struct DebugPixel 
{
	int x;
	int y;
	wchar_t ch;
	int color;
};
class DebugDraw
{
public:
	std::vector<DebugPixel> debugPixels;

	void drawPixel(int x, int y, wchar_t ch, int color)
	{
		debugPixels.push_back({ x, y, ch, color });
	}
};