#include "MouseButton.h"

MouseButton::MouseButton()
{
	object_position_.x = 0;
	object_position_.y = 0;
}

MouseButton::~MouseButton()
{

}

void MouseButton::setPositionObject(int xPos, int yPos, int width, int height)
{
	object_position_.x = xPos;
	object_position_.y = yPos;
	object_position_.h = height;
	object_position_.w = width;
}

bool MouseButton::handleEvent(SDL_Event* event_, SDL_Renderer* renderer)
{

	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse, &yMouse);
	if (xMouse < object_position_.x)
	{
		return false;
	}
	else if (xMouse > object_position_.x + object_position_.w)
	{
		return false;
	}
	else if (yMouse < object_position_.y)
	{
		return false;
	}
	else if (yMouse > object_position_.y + object_position_.h)
	{
		return false;
	}
	return true;
}

SDL_Rect MouseButton::getRect() const
{
	return object_position_;
}
