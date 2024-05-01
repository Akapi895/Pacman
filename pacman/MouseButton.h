#ifndef MOUSE_BUTTON_H_
#define MOUSE_BUTTON_H_

#include "CommonFunction.h"
#include "BaseObject.h"


class MouseButton
{
public:
	MouseButton();
	~MouseButton();

	void setPositionObject(int xPos, int yPos, int height, int weight);
	bool handleEvent(SDL_Event* event_, SDL_Renderer* renderer);
	SDL_Rect getRect() const;
private:

	SDL_Rect object_position_;
};

#endif // !MOUSE_BUTTON_H_
