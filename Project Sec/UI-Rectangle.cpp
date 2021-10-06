#include "UI-Rectangle.h"

UIRect::UIRect(Vector2 position, Vector2 size):
	box({ position.x, position.y, size.x, size.y })
{
}

void UIRect::draw()
{
	DrawRectangleRec(box, backgroundColor);
	DrawRectangleLinesEx(box, 2, outlineColor);
}

bool UIRect::isPointIn(Vector2 mouse)
{
	if (mouse.x >= box.x && mouse.x <= box.x + box.width) // muis x in button x
		return mouse.y >= box.y && mouse.y <= box.y + box.height; // muis y in button y
	return false;
}
