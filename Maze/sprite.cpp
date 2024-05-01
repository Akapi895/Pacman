#include "sprite.h"
#include "graphics.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

/*void Sprite::HandleInput(SDL_Event& event)
{
	/*bool move_up(false), move_down(false), move_left(false), move_right(false);
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			move_up = true;
			break;
		case SDLK_s:
			move_down = true;
			break;
		case SDLK_a:
			move_left = true;
			break;
		case SDLK_d:
			move_right = true;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			move_up = false;
			break;
		case SDLK_s:
			move_down = false;
			break;
		case SDLK_a:
			move_left = false;
			break;
		case SDLK_d:
			move_right = false;
			break;
		default:
			break;
		}
	}

	// Update movement based on direction flags in your game loop
	if (move_up && move_left) {
		// Move diagonally northwest
		x_val_ -= SPEED / sqrt(2);
		y_val_ -= SPEED / sqrt(2);
	}
	else if (move_up && move_right) {
		// Move diagonally northeast
		x_val_ += SPEED / sqrt(2);
		y_val_ -= SPEED / sqrt(2);
	}
	else if (move_down && move_left) {
		// Move diagonally southwest
		x_val_ -= SPEED / sqrt(2);
		y_val_ += SPEED / sqrt(2);
	}
	else if (move_down && move_right) {
		// Move diagonally southeast
		x_val_ += SPEED / sqrt(2);
		y_val_ += SPEED / sqrt(2);
	}
	else if (move_up) {
		y_val_ -= SPEED;
	}
	else if (move_down) {
		y_val_ += SPEED;
	}
	else if (move_left) {
		x_val_ -= SPEED;
	}
	else if (move_right) {
		x_val_ += SPEED;
	}//

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ -= SPEED;
			break;
		case SDLK_s:
			y_val_ += SPEED;
			break;
		case SDLK_a:
			x_val_ -= SPEED;
			break;
		case SDLK_d:
			x_val_ += SPEED;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ += SPEED;
			break;
		case SDLK_s:
			y_val_ -= SPEED;
			break;
		case SDLK_a:
			x_val_ += SPEED;
			break;
		case SDLK_d:
			x_val_ -= SPEED;
			break;
		default:
			break;
		}
	}
}*/

#include <math.h> // for sqrt

enum Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

Direction movementDirection = NONE;
float x_val = 0.0f, y_val = 0.0f;
const static float SPEED = 5.0f; // Adjust speed as needed

void Sprite::handleMovementInput(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			movementDirection |= UP;
			break;
		case SDLK_s:
			movementDirection |= DOWN;
			break;
		case SDLK_a:
			movementDirection |= LEFT;
			break;
		case SDLK_d:
			movementDirection |= RIGHT;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			movementDirection &= ~UP;
			break;
		case SDLK_s:
			movementDirection &= ~DOWN;
			break;
		case SDLK_a:
			movementDirection &= ~LEFT;
			break;
		case SDLK_d:
			movementDirection &= ~RIGHT;
			break;
		default:
			break;
		}
	}
}

void Sprite::updateMovement(float deltaTime) {
	float diagonalSpeed = SPEED / sqrt(2.0f);

	// Clear movement if no direction keys are pressed
	if (movementDirection == NONE) {
		x_val = 0.0f;
		y_val = 0.0f;
		return;
	}

	// Handle diagonal movement
	if ((movementDirection & UP) && (movementDirection & LEFT)) {
		x_val -= diagonalSpeed * deltaTime;
		y_val -= diagonalSpeed * deltaTime;
	}
	else if ((movementDirection & UP) && (movementDirection & RIGHT)) {
		x_val += diagonalSpeed * deltaTime;
		y_val -= diagonalSpeed * deltaTime;
	}
	else if ((movementDirection & DOWN) && (movementDirection & LEFT)) {
		x_val -= diagonalSpeed * deltaTime;
		y_val += diagonalSpeed * deltaTime;
	}
	else if ((movementDirection & DOWN) && (movementDirection & RIGHT)) {
		x_val += diagonalSpeed * deltaTime;
		y_val += diagonalSpeed * deltaTime;
	}

	// Handle horizontal and vertical movement (combine for efficiency)
	x_val += (movementDirection & RIGHT ? SPEED : 0) * deltaTime -
		(movementDirection & LEFT ? SPEED : 0) * deltaTime;
	y_val += (movementDirection & DOWN ? SPEED : 0) * deltaTime -
		(movementDirection & UP ? SPEED : 0) * deltaTime;
}
bool Sprite::LoadImg(std::string path, SDL_Renderer* des)
{
	bool success = true;
	p_text = IMG_LoadTexture(des, path.c_str());
	if (p_text == NULL)
	{
		std::cout << "LOAD IMG ERROR " << IMG_GetError() << std::endl;
		success = false;
	}
	return success;
}

void Sprite::render(SDL_Renderer* des)
{
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	SDL_Rect Renderquad = { x_pos_, y_pos_, 100, 100 };
	SDL_RenderCopyEx(des, p_text, &SLIME[frame_count], &Renderquad, 0, NULL, SDL_FLIP_NONE);
	frame_count++;
	if (frame_count >= MAX_FRAME)
	{
		frame_count = 0;
	}
}