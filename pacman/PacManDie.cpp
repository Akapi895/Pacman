#include "PacManDie.h"

PacmanDie::PacmanDie()
{
	width_frame_ = 0;
	height_frame_ = 0;

	current_frame_ = -1;

	x_pos_ = 0;
	y_pos_ = 0;
}

PacmanDie::~PacmanDie()
{

}

bool PacmanDie::loadImage(string path, SDL_Renderer* renderer, bool isVertical, SDL_Color* colorKey)
{
	bool success = BaseObject::loadImage(path, renderer, colorKey);
	if (success == true)
	{
		if (isVertical == false) {
			width_frame_ = rect_.w / PACMAN_DIE_FRAME_;
			height_frame_ = rect_.h;
			setClips();
		}
		else
		{
			width_frame_ = rect_.w;
			height_frame_ = rect_.h / PACMAN_DIE_FRAME_;
			setClips(isVertical);
		}

	}
	return success;
}

void PacmanDie::setClips(bool isVertical)
{
	if (isVertical == false)
	{
		for (int i = 0; i < PACMAN_DIE_FRAME_; i++)
		{
			clip_rect_[i].x = width_frame_ * i;
			clip_rect_[i].y = 0;
			clip_rect_[i].w = width_frame_;
			clip_rect_[i].h = height_frame_;
		}
	}
	else
	{
		for (int i = 0; i < PACMAN_DIE_FRAME_; i++)
		{
			clip_rect_[i].x = 0;
			clip_rect_[i].y = height_frame_ * i;
			clip_rect_[i].w = width_frame_;
			clip_rect_[i].h = height_frame_;
		}
	}
}

void PacmanDie::render(SDL_Renderer* renderer)
{
	current_frame_++;
	if (current_frame_ >= PACMAN_DIE_FRAME_)
	{
		current_frame_ = 0;
	}
	SDL_Rect posScreen = { x_pos_, y_pos_, width_frame_, height_frame_ };
	SDL_RenderCopy(renderer, texture_, &clip_rect_[current_frame_], &posScreen);
}

void PacmanDie::setImage(int goType, const SDL_Rect& pacmanDiePos, SDL_Renderer* renderer,
	GameMap& renderMap, BaseObject& renderBackground)
{
	if (goType == GO_DOWN)
	{
		loadImage("image/pacman_die_down.png", renderer, false, &COLOR_KEY_WHITE_);
	}
	else if (goType == GO_UP)
	{
		loadImage("image/pacman_die_up.png", renderer, false, &COLOR_KEY_WHITE_);
	}
	else if (goType == GO_RIGHT)
	{
		loadImage("image/pacman_die_right.png", renderer, true, &COLOR_KEY_WHITE_);
	}
	else if (goType == GO_LEFT)
	{
		loadImage("image/pacman_die_left.png", renderer, true, &COLOR_KEY_WHITE_);
	}

	setPos(pacmanDiePos);

	for (int i = 0; i < PACMAN_DIE_FRAME_; i++)
	{
		SDL_RenderClear(renderer);

		renderBackground.render(renderer);
		renderMap.drawMap(renderer);
		render(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(150);
	}
}

void PacmanDie::setPos(SDL_Rect posScr)
{
	x_pos_ = posScr.x;
	y_pos_ = posScr.y;
}
