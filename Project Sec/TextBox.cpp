#include "TextBox.h"

void TextBox::setPosition(Vector2 to)
{
	box.x = to.x;
	box.y = to.y;
}

void TextBox::draw()
{
	DrawRectangleRec(box, WHITE);
	DrawRectangleLinesEx(box, 3, BLACK);
	DrawText(text.c_str(), box.x + 5, box.y + 10, 20, BLACK);
}
