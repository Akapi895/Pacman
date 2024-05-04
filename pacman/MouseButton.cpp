#include "MouseButton.h"

MouseButton::MouseButton()
{
	object_position_.x = 0;
	object_position_.y = 0;
}

MouseButton::~MouseButton()
{

}

void MouseButton::setPositionObject(int posx, int posy, int width, int height)
{
	object_position_.x = posx;
	object_position_.y = posy;
	object_position_.w = width;
	object_position_.h = height;
}

bool MouseButton::handleEvent(SDL_Event* event_, SDL_Renderer* renderer)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x < object_position_.x || x > object_position_.x + object_position_.w)
	{
		return false;
	}

	else if (y < object_position_.y || y > object_position_.y + object_position_.h)
	{
		return false;
	}

	return true;
}

SDL_Rect MouseButton::getRect() const
{
	return object_position_;
}
