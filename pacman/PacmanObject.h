#ifndef PACMAN_OBJECT_H_
#define PACMAN_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MusicGame.h"

class PacmanObject : public BaseObject
{
public:
	PacmanObject();
	~PacmanObject();

	void setStartPacman(SDL_Renderer* renderer, SDL_Color* colorKey);

	bool loadImage(string path, SDL_Renderer* renderer, bool isVertical = false, SDL_Color* colorKey = NULL);
	void setClips(bool isVertical = false);
	void render(SDL_Renderer* renderer);

	void updateImageDirect(SDL_Renderer* renderer);
	void handleInput(SDL_Event events);

	void pacmanMove(GameMap& checkMap);
	bool checkToMap(GameMap& checkMap);
	void checkToItem(GameMap& checkMap, MusicGame* musicEatItems);

	void setDirection();
	void setDirection(GameMap& checkMap, SDL_Renderer* renderer);

	void setNumberItems(int numberItems);
	void setCurrentFrame(const int numberFrame);

	void setScore(const int score);
	int getScore() const;
	int getNumberItems() const;
	int getGoType() const;
	SDL_Rect getPos() const;
protected:

	int width_frame_;
	int height_frame_;

	int current_frame_;

	int x_pos_;
	int y_pos_;

	int direction_current_;
	int direction_input_;

	int number_items;
	int score_;
	SDL_Rect clip_rect_[PACMAN_FRAME_];
};

#endif // !PACMAN_OBJECT_H_
