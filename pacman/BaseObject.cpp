#include "BaseObject.h"


BaseObject::BaseObject()
{
	texture_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject()
{
	free();
}

void BaseObject::setRect(const int& x, const int& y)
{
	rect_.x = x;
	rect_.y = y;
}

SDL_Rect BaseObject::getRect() const
{ 
	return rect_;
}

SDL_Texture* BaseObject::getTexture() const
{
	return texture_;
}

bool BaseObject::loadImage(string path, SDL_Renderer* renderer, SDL_Color* colorKey)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());

	int colorKeyR = COLOR_KEY_R;
	int colorKeyG = COLOR_KEY_G;
	int colorKeyB = COLOR_KEY_B;

	if (colorKey != NULL)
	{
		colorKeyR = colorKey->r;
		colorKeyG = colorKey->g;
		colorKeyB = colorKey->b;
	}

	if (loadSurface != NULL)
	{
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, colorKeyR, colorKeyG, colorKeyB));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		if (newTexture != NULL)
		{
			rect_.w = loadSurface->w;
			rect_.h = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}
	texture_ = newTexture;
	return texture_ != NULL;
}

void BaseObject::render(SDL_Renderer* renderer, const SDL_Rect* srcrect)
{
	SDL_RenderCopy(renderer, texture_, srcrect, &rect_);
}

void BaseObject::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}