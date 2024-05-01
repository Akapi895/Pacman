#include "PacmanObject.h"

PacmanObject::PacmanObject()
{
	current_frame_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	direction_current_ = GO_NONE;
	direction_input_ = GO_NONE;

	number_items = 0;
	score_ = 0;
}

PacmanObject::~PacmanObject()
{

}

void PacmanObject::setStartPacman(SDL_Renderer* renderer, SDL_Color* colorKey)
{
	x_pos_ = START_PACMAN_X_ * PIXEL_CLIP_;
	y_pos_ = START_PACMAN_Y_ * PIXEL_CLIP_;

	direction_current_ = GO_RIGHT;
	direction_input_ = GO_RIGHT;

	loadImage("image/pacman_right.png", renderer, false, colorKey);
}

void PacmanObject::setNumberItems(int numberItems)
{
	number_items = numberItems;
}

void PacmanObject::setCurrentFrame(const int numberFrame)
{
	current_frame_ = numberFrame;
}

void PacmanObject::setScore(const int score)
{
	score_ = score;
}

int PacmanObject::getScore() const
{
	return score_;
}

int PacmanObject::getNumberItems() const
{
	return number_items;
}

bool PacmanObject::loadImage(string path, SDL_Renderer* renderer, bool isVertical, SDL_Color* colorKey)
{
	bool success = BaseObject::loadImage(path, renderer, colorKey);
	if (success == true)
	{
		if (isVertical == false) {
			width_frame_ = rect_.w / PACMAN_FRAME_;
			height_frame_ = rect_.h;
			setClips();
		}
		else
		{
			width_frame_ = rect_.w;
			height_frame_ = rect_.h / PACMAN_FRAME_;
			setClips(isVertical);
		}

	}
	return success;
}

void PacmanObject::setClips(bool isVertical)
{
	if (isVertical == false)
	{
		for (int i = 0; i < PACMAN_FRAME_; i++)
		{
			clip_rect_[i].x = width_frame_ * i;
			clip_rect_[i].y = 0;
			clip_rect_[i].w = width_frame_;
			clip_rect_[i].h = height_frame_;
		}
	}
	else
	{
		for (int i = 0; i < PACMAN_FRAME_; i++)
		{
			clip_rect_[i].x = 0;
			clip_rect_[i].y = height_frame_ * i;
			clip_rect_[i].w = width_frame_;
			clip_rect_[i].h = height_frame_;
		}
	}
}

void PacmanObject::render(SDL_Renderer* renderer)
{
	current_frame_++;
	if (current_frame_ >= PACMAN_FRAME_)
	{
		current_frame_ = 0;
	}
	SDL_Rect posScreen = { x_pos_, y_pos_, width_frame_, height_frame_ };
	SDL_RenderCopy(renderer, texture_, &clip_rect_[current_frame_], &posScreen);
}

void PacmanObject::updateImageDirect(SDL_Renderer* renderer)
{
	SDL_Color colorKey = { 255, 255, 255 };
	if (direction_current_ == GO_DOWN)
	{
		loadImage("image//pacman_down.png", renderer, true, &colorKey);
	}
	else if (direction_current_ == GO_UP)
	{
		loadImage("image//pacman_up.png", renderer, true, &colorKey);
	}
	else if (direction_current_ == GO_LEFT)
	{
		loadImage("image//pacman_left.png", renderer, false, &colorKey);
	}
	else if (direction_current_ == GO_RIGHT)
	{
		loadImage("image//pacman_right.png", renderer, false, &colorKey);
	}
}

void PacmanObject::handleInput(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			direction_input_ = GO_RIGHT;
			break;
		}
		case SDLK_d:
		{
			direction_input_ = GO_RIGHT;
			break;
		}
		case SDLK_LEFT:
		{
			direction_input_ = GO_LEFT;
			break;
		}
		case SDLK_a:
		{
			direction_input_ = GO_LEFT;
			break;
		}
		case SDLK_UP:
		{
			direction_input_ = GO_UP;
			break;
		}
		case SDLK_w:
		{
			direction_input_ = GO_UP;
			break;
		}
		case SDLK_DOWN:
		{
			direction_input_ = GO_DOWN;
			break;
		}
		case SDLK_s:
		{
			direction_input_ = GO_DOWN;
			break;
		}
		default:
			break;
		}
	}
}

void PacmanObject::setDirection()
{
	direction_current_ = GO_RIGHT;
}

void PacmanObject::setDirection(GameMap& checkMap, SDL_Renderer* renderer)
{
	if ((x_pos_ % TILE_SIZE != 0 || y_pos_ % TILE_SIZE != 0)
		&& ((direction_current_ == GO_DOWN && direction_input_ != GO_UP)
			|| (direction_current_ == GO_UP && direction_input_ != GO_DOWN)
			|| (direction_current_ == GO_RIGHT && direction_input_ != GO_LEFT)
			|| (direction_current_ == GO_LEFT && direction_input_ != GO_RIGHT)))
	{
		return;
	}

	if (direction_current_ != GO_DOWN && direction_input_ == GO_DOWN)
	{
		y_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_DOWN;
			updateImageDirect(renderer);
		}
		y_pos_ -= VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_UP && direction_input_ == GO_UP)
	{
		y_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_UP;
			updateImageDirect(renderer);
		}
		y_pos_ += VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_LEFT && direction_input_ == GO_LEFT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_LEFT;
			updateImageDirect(renderer);
		}
		x_pos_ += VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_RIGHT && direction_input_ == GO_RIGHT)
	{
		x_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_RIGHT;
			updateImageDirect(renderer);
		}
		x_pos_ -= VEL_PACMAN_;
		return;
	}
}

void PacmanObject::pacmanMove(GameMap& checkMap)
{
	if (direction_current_ == GO_DOWN)
	{
		y_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
		{
			y_pos_ -= VEL_PACMAN_;
		}
	}
	if (direction_current_ == GO_LEFT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
		{
			x_pos_ += VEL_PACMAN_;
		}
	}
	if (direction_current_ == GO_RIGHT)
	{
		x_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
		{
			x_pos_ -= VEL_PACMAN_;
		}
	}
	if (direction_current_ == GO_UP)
	{
		y_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
		{
			y_pos_ += VEL_PACMAN_;
		}
	}
}

bool PacmanObject::checkToMap(GameMap& checkMap)
{
	int xPosImage1 = x_pos_ / TILE_SIZE;
	int yPosImage1 = y_pos_ / TILE_SIZE;

	int xPosImage2 = (x_pos_ + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage2 = y_pos_ / TILE_SIZE;

	int xPosImage3 = x_pos_ / TILE_SIZE;
	int yPosImage3 = (y_pos_ + TILE_SIZE - 1) / TILE_SIZE;

	int xPosImage4 = (x_pos_ + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage4 = (y_pos_ + TILE_SIZE - 1) / TILE_SIZE;

	Map* checkTileNumber = checkMap.getMap();

	if (checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_2_)
	{
		return true;
	}

	return false;
}

void PacmanObject::checkToItem(GameMap& checkMap, MusicGame* musicEatItems)
{
	int xPosImage1 = x_pos_ / TILE_SIZE;
	int yPosImage1 = y_pos_ / TILE_SIZE;

	Map* checkTileNumber = checkMap.getMap();

	if (xPosImage1 * TILE_SIZE == x_pos_ && yPosImage1 * TILE_SIZE == y_pos_)
	{
		int tileNumber = checkTileNumber->tiles_number_[yPosImage1][xPosImage1];
		if (tileNumber == TILE_PAC_DOTS_)
		{
			Mix_PlayChannel(-1, musicEatItems->getMusicEatDot(), 0);
			score_ += 10;
			number_items--;
		}

		if (tileNumber == TILE_PAC_BIG_DOTS_)
		{
			Mix_PlayChannel(-1, musicEatItems->getMusicEatBigDot(), 0);
			score_ += 25;
			number_items--;
		}
		checkTileNumber->tiles_number_[yPosImage1][xPosImage1] = TILE_NONE_;
	}
}

int PacmanObject::getGoType() const
{
	return direction_current_;
}

SDL_Rect PacmanObject::getPos() const
{
	SDL_Rect posPacman;
	posPacman.x = x_pos_;
	posPacman.y = y_pos_;
	posPacman.w = width_frame_;
	posPacman.h = height_frame_;
	return posPacman;
}
