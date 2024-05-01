#ifndef PACMAN_DIE_H_
#define PACMAN_DIE_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"

class PacmanDie : public BaseObject
{
public:
	PacmanDie();
	~PacmanDie();

	bool loadImage(string path, SDL_Renderer* renderer, bool isVertical = false, SDL_Color* colorKey = NULL);
	void setClips(bool isVertical = false);
	void render(SDL_Renderer* renderer);

	void setImage(int goType, const SDL_Rect& pacmanDiePos, SDL_Renderer* renderer, GameMap& renderMap, BaseObject& renderBackground);

	void setPos(SDL_Rect posScr);

private:
	int width_frame_;
	int height_frame_;

	int current_frame_;
	int direction_die_;

	int x_pos_;
	int y_pos_;

	SDL_Rect clip_rect_[PACMAN_DIE_FRAME_];
};

#endif // !PACMAN_DIE_H_


