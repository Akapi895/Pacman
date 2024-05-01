#ifndef PET_OBJECT_H_
#define PET_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "PacmanObject.h"
#include "GameMap.h"

class PetObject : public BaseObject
{
public:
	PetObject();
	~PetObject();

	void setStartPet(SDL_Renderer* renderer, SDL_Color* colorKey);
	void setPetNumber(const int petNumber);

	bool loadImage(string path, SDL_Renderer* renderer, SDL_Color* colorKey = NULL);
	void setClips();
	void render(SDL_Renderer* renderer);

	void updateImageDirect(SDL_Renderer* renderer);


	void autoInputDirect(GameMap& checkMap);
	void autoAiInputDirect(GameMap& checkMap, PacmanObject& pacman);
	void setDirection(GameMap& checkMap, SDL_Renderer* renderer);

	void petMove(GameMap& checkMap);
	bool checkToMap(GameMap& checkMap);

	SDL_Rect getRect() const;
private:
	int current_frame_;

	int width_frame_;
	int height_frame_;

	int x_pos_;
	int y_pos_;

	int direction_current_;
	int direction_auto_;

	SDL_Rect clip_rect_[PET_FRAME_];

	int pet_number_;
};
#endif // !PET_OBJECT_H_



