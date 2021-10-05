#pragma once

#include <raylib.h>
#include <string>

class TextBox
{
private:
	Rectangle box;
	std::string text;
public:
	// constructors
	TextBox(Rectangle rec) : box(rec) {}
	TextBox(Rectangle rec, std::string text) : box(rec), text(text) {}

	// methods
	void setString(std::string to) { this->text = to; }
	void setPosition(Vector2 to);
	void draw();
};

