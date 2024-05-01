#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void setRect(const int& x, const int& y);

	SDL_Rect getRect() const;
	SDL_Texture* getTexture() const;
	
	virtual bool loadImage(string path, SDL_Renderer* renderer, SDL_Color* colorKey = NULL);
	virtual void render(SDL_Renderer* renderer, const SDL_Rect* srcrect = NULL);
	void free();
protected:
	SDL_Texture* texture_;
	SDL_Rect rect_;
};


#endif // !BASE_OBJECT_H_
