#include "MouseButton.h"

MouseButton::MouseButton()
{
	clickRect_.x = 0;
	clickRect_.y = 0;
}

void MouseButton::setPositionObject(int posx, int posy, int width, int height)
{
	clickRect_.x = posx;
	clickRect_.y = posy;
	clickRect_.w = width;
	clickRect_.h = height;
}

bool MouseButton::handleEvent(SDL_Event* event_, SDL_Renderer* renderer)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	isClicked_ = false;

	if (x < clickRect_.x || x > clickRect_.x + clickRect_.w) {
        return false;
    } else if (y < clickRect_.y || y > clickRect_.y + clickRect_.h) {
        return false;
    }

    // Handle left mouse button click (optional)
    if (event_->type == SDL_MOUSEBUTTONDOWN && event_->button.button == SDL_BUTTON_LEFT) {
        isClicked_ = true;
    }

    return true;
}

SDL_Rect MouseButton::getClickRect() const
{
	return clickRect_;
}
