#include "TextObject.h"


TextObject::TextObject()
{
	int width_ = 0;
	int height_ = 0;

	text_color_.r = COLOR_RENDER_DEFAULT;
	text_color_.g = COLOR_RENDER_DEFAULT;
	text_color_.b = COLOR_RENDER_DEFAULT;
	texture_ = NULL;

	string_val_ = "";

}

TextObject::~TextObject()
{
	free();
}

bool TextObject::loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, string_val_.c_str(), text_color_);
	if (textSurface)
	{
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		width_ = textSurface->w;
		height_ = textSurface->h;
		SDL_FreeSurface(textSurface);
	}

	return texture_ != NULL;
}

void TextObject::setColor(int red, int green, int blue)
{
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}

int TextObject::getWidth() const
{
	return width_;
}

void TextObject::setColor(int typeColor)
{
	switch (typeColor)
	{
	case BLACK_:
		text_color_ = { 0,0,0 }; break;
	case WHITE_:
		text_color_ = { 255, 255, 255 }; break;
	case RED_:
		text_color_ = { 255, 0, 0 }; break;
	case GREEN_:
		text_color_ = { 0,255,0 }; break;
	case PURPLE_:
		text_color_ = { 0,0,255 }; break;
	case YELLOW_:
		text_color_ = { 255, 255, 0 }; break;
	case BLUE_:
		text_color_ = { 0,255,255 }; break;
	case PINK_:
		text_color_ = { 255, 0, 255 }; break;
	}
}

void TextObject::renderText(SDL_Renderer* renderer, int xPos, int yPos, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { xPos, yPos, width_, height_ };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture_, clip, &renderQuad, 0, NULL, SDL_FLIP_NONE);
}


void TextObject::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

int TextObject::getHeight() const
{
	return height_;
}

string TextObject::getText() const
{
	return string_val_;
}

void TextObject::setText(const string& textInput)
{
	string_val_ = textInput;
}

