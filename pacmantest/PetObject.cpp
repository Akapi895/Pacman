#include "PetObject.h"
#include <algorithm>

PetObject::PetObject() {
	current_frame_ = 0;
	width_frame_   = 0;
	height_frame_  = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	direction_current_ = GO_NONE;
	direction_auto_    = GO_NONE; //GO_RIGHT

	pet_number_ = 0;
}

void PetObject::setStartPet(SDL_Renderer* renderer, SDL_Color* colorKey) {
	current_frame_ = PET_FRAME_;

	x_pos_ = START_PET_X_ * PIXEL_CLIP_;
	y_pos_ = START_PET_Y_ * PIXEL_CLIP_;

	direction_current_ = GO_DOWN;
	direction_auto_ = GO_DOWN;

	loadImage("image//pet_" + to_string(pet_number_) + "_down.png", renderer, colorKey);
}

void PetObject::setPetNumber(const int petNumber) {
	pet_number_ = petNumber;
}

void PetObject::render(SDL_Renderer* renderer) {
	current_frame_++;

	if (current_frame_ >= PET_FRAME_)
		current_frame_ = 0;

	SDL_Rect posScreen = { x_pos_, y_pos_, width_frame_, height_frame_ };
	SDL_RenderCopy(renderer, texture_, &clip_rect_[current_frame_], &posScreen);
}

bool PetObject::loadImage(string path, SDL_Renderer* renderer, SDL_Color* colorKey) {
	bool success = BaseObject::loadImage(path, renderer, colorKey);

	if (success == true) {
		width_frame_ = rect_.w / PET_FRAME_;
		height_frame_ = rect_.h;
		setClips();
	}

	return success;
}

void PetObject::setClips() {
	for (int i = 0; i < PET_FRAME_; i++)
	{
		clip_rect_[i].x = width_frame_ * i;
		clip_rect_[i].y = 0;
		clip_rect_[i].w = width_frame_;
		clip_rect_[i].h = height_frame_;
	}
}

SDL_Rect PetObject::getRect() const {
	SDL_Rect posPet;
	posPet.x = x_pos_;
	posPet.y = y_pos_;
	posPet.h = height_frame_;
	posPet.w = width_frame_;
	return posPet;
}

void PetObject::updateImageDirect(SDL_Renderer* renderer) {
	if (direction_current_ == GO_DOWN)
		loadImage("image//pet_" + to_string(pet_number_) + "_down.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_UP)
		loadImage("image//pet_" + to_string(pet_number_) + "_up.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_LEFT)
		loadImage("image//pet_" + to_string(pet_number_) + "_left.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_RIGHT)
		loadImage("image//pet_" + to_string(pet_number_) + "_right.png", renderer, &COLOR_KEY_BLACK_);
}

void PetObject::autoInputDirect(GameMap& checkMap) {
	vector<int> candidatesDir;
	if (direction_current_ != GO_LEFT) {
		x_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_RIGHT);
		}
		x_pos_ -= VEL_PACMAN_;
	}

	if (direction_current_ != GO_RIGHT) {
		x_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_LEFT);
		}
		x_pos_ += VEL_PACMAN_;
	}

	if (direction_current_ != GO_UP) {
		y_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_DOWN);
		}
		y_pos_ -= VEL_PACMAN_;

	}

	if (direction_current_ != GO_DOWN) {
		y_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_UP);
		}
		y_pos_ += VEL_PACMAN_;
	}

	if (candidatesDir.size() == 0) {
		switch (direction_current_) {
            case GO_UP: direction_auto_ = GO_DOWN; break;
            case GO_DOWN: direction_auto_ = GO_UP; break;
            case GO_RIGHT: direction_auto_ = GO_LEFT; break;
            case GO_LEFT: direction_auto_ = GO_RIGHT; break;
		}
	}
	else {
		int randomDirect = rand() % candidatesDir.size();
		direction_auto_ = candidatesDir[randomDirect];
	}
}


int PetObject::getDirectionToPos(int targetX, int targetY) {
    int currentX = getRect().x;
    int currentY = getRect().y;

    int dx = targetX - currentX;
    int dy = targetY - currentY;

    if (dx == 0 && dy > 0) {
        return GO_UP;
    } else if (dx > 0 && dy == 0) {
        return GO_RIGHT;
    } else if (dx == 0 && dy < 0) {
        return GO_DOWN;
    } else if (dx < 0 && dy == 0) {
        return GO_LEFT;
    }
}

int PetObject::getCost(int tileType) {
    // Example: Assign different costs for different tile types
    switch (tileType) {
      case 0: // Open space (low cost)
        return 1;
      case 1: // Wall (impassable)
        return numeric_limits<int>::max();
      case 2: // Water (high cost)
        return 5;
      default:
        return 3; // Default cost
    }
  }

void PetObject::autoAiInputDirect(GameMap& checkMap, PacmanObject& pacman) {
	map<int, int> candidatesGoType;
	SDL_Rect pacmanPos = pacman.getPos();
	//int distanceMin = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
    if (direction_current_ != GO_UP)
    {
        y_pos_ += VEL_PACMAN_;
        if (!checkToMap(checkMap))
        {
            int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
//            candidatesGoType.insert({ distance_, GO_DOWN });
            candidatesGoType[distance_] = GO_DOWN;
        }
        y_pos_ -= VEL_PACMAN_;
    }

	if (direction_current_ != GO_LEFT)
	{
		x_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
//			candidatesGoType.insert({ distance_, GO_RIGHT });
			candidatesGoType[distance_] = GO_RIGHT;
		}
		x_pos_ -= VEL_PACMAN_;
	}

	if (direction_current_ != GO_RIGHT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
//			candidatesGoType.insert({ distance_, GO_LEFT });
			candidatesGoType[distance_] = GO_LEFT;
		}
		x_pos_ += VEL_PACMAN_;
	}

	if (direction_current_ != GO_DOWN)
	{
		y_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
//			candidatesGoType.insert({ distance_, GO_UP });
			candidatesGoType[distance_] = GO_UP;
		}
		y_pos_ += VEL_PACMAN_;
	}

	if (candidatesGoType.size() == 0)
	{
		switch (direction_current_)
		{
            case GO_UP: direction_auto_ = GO_DOWN; break;
            case GO_DOWN: direction_auto_ = GO_UP; break;
            case GO_RIGHT: direction_auto_ = GO_LEFT; break;
            case GO_LEFT: direction_auto_ = GO_RIGHT; break;
		}
	}
	else
	{
		for (auto i : candidatesGoType)
		{
			direction_auto_ = i.second;
			break;
		}
	}
}

void PetObject::setDirection(GameMap& checkMap, SDL_Renderer* renderer) {
	if (x_pos_ % TILE_SIZE != 0 || y_pos_ % TILE_SIZE != 0)
	{
		return;
	}

	if (direction_current_ != GO_DOWN && direction_auto_ == GO_DOWN)
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
	if (direction_current_ != GO_UP && direction_auto_ == GO_UP)
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
	if (direction_current_ != GO_LEFT && direction_auto_ == GO_LEFT)
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
	if (direction_current_ != GO_RIGHT && direction_auto_ == GO_RIGHT)
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


void PetObject::petMove(GameMap& checkMap) {
	if (direction_current_ == GO_DOWN)
	{
		y_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
			y_pos_ -= VEL_PACMAN_;
	}
	if (direction_current_ == GO_LEFT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
			x_pos_ += VEL_PACMAN_;
	}
	if (direction_current_ == GO_RIGHT)
	{
		x_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
			x_pos_ -= VEL_PACMAN_;
	}
	if (direction_current_ == GO_UP)
	{
		y_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
			y_pos_ += VEL_PACMAN_;
	}
}

bool PetObject::checkToMap(GameMap& checkMap)
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

bool PetObject::checkToMap(GameMap& checkMap, int newx, int newy)
{
	int xPosImage1 = newx / TILE_SIZE;
	int yPosImage1 = newy / TILE_SIZE;

	int xPosImage2 = (newx + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage2 = newy / TILE_SIZE;

	int xPosImage3 = newx / TILE_SIZE;
	int yPosImage3 = (newy + TILE_SIZE - 1) / TILE_SIZE;

	int xPosImage4 = (newx + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage4 = (newy + TILE_SIZE - 1) / TILE_SIZE;

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




