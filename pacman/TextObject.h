#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction.h"

enum TextColor
{
	BLACK_ = 0,
	WHITE_ = 1,
	RED_ = 2,
	GREEN_ = 3,
	PURPLE_ = 4,
	YELLOW_ = 5,
	BLUE_ = 6,
	PINK_ = 7
};

class TextObject
{
public:
	TextObject();
	~TextObject();

	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* renderer);
	void setColor(int red, int green, int blue);
	void setColor(int typeColor);

	void renderText(SDL_Renderer* renderer, int xPos, int yPos, SDL_Rect* clip = NULL);

	int getWidth() const;
	int getHeight() const;

	void setText(const string& textInput);
	string getText() const;

	void free();
private:
	string string_val_;
	SDL_Color text_color_;
	SDL_Texture* texture_;
	int width_;
	int height_;
};

#endif TEXT_OBJECT_H