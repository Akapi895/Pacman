#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	void setRect(const int& x, const int& y);

	SDL_Rect getRect() const;
	SDL_Texture* getTexture() const;

	virtual bool loadImage(const std::string& path, SDL_Renderer* renderer, SDL_Color* colorKey = NULL);
    virtual void render(SDL_Renderer* renderer, const SDL_Rect* sourceRect = NULL);

	void free();

protected:
	SDL_Texture* texture_;
	SDL_Rect rect_;
};


#endif
