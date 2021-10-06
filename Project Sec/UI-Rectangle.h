#pragma once

#include <raylib.h>

class UIRect
{
private:
	Rectangle box;
	Color backgroundColor = WHITE;
	Color outlineColor = BLACK;
public:
	UIRect(Vector2 position, Vector2 size);

	void draw();
	void setBackgroundColor(Color to) { backgroundColor = to; }
	void setOutlineColor(Color to) { outlineColor = to; }
	bool isPointIn(Vector2 point);
};

