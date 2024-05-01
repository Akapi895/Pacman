	#pragma once
	#ifndef SPRITE_H
	#define SPRITE_H

	#include "defs.h"


	const SDL_Rect SLIME[] = {
		{0, 0, 32, 32},
		{32, 0, 32, 32},
		{64, 0, 32, 32},
		{96, 0, 32, 32},
		{128, 0, 32, 32},
		{160, 0, 32, 32},
		{192, 0, 32, 32},
		{224, 0, 32, 32},
	};
	const int SLIME_FRAMES = sizeof(SLIME) / sizeof(int) / 4;


	const SDL_Rect SAMURAI[] = {
		{ 0, 0, 100, 100 },
		{ 100, 0, 100, 100 },
		{ 200, 0, 100, 100 },
		{ 300, 0, 100, 100 },
		{ 400, 0, 100, 100 },
		{ 500, 0, 100, 100 },
		{ 600, 0, 100, 100 },
		{ 700, 0, 100, 100 },
		{ 800, 0, 100, 100 },
		{ 900, 0, 100, 100 },
		{ 1000, 0, 100, 100 },
		{ 1100, 0, 100, 100 },
		{ 1200, 0, 100, 100 },
		{ 1300, 0, 100, 100 },
		{ 1400, 0, 100, 100 },//15 slash

		{ 0, 100, 100, 100 },
		{ 100, 100, 100, 100 },
		{ 200, 100, 100, 100 },
		{ 300, 100, 100, 100 },
		{ 400, 100, 100, 100 },
		{ 500, 100, 100, 100 },
		{ 600, 100, 100, 100 },
		{ 700, 100, 100, 100 },
		{ 800, 100, 100, 100 },
		{ 900, 100, 100, 100 },
		{ 1000, 100, 100, 100 },
		{ 1100, 100, 100, 100 },
		{ 1200, 100, 100, 100 },
		{ 1300, 100, 100, 100 },//14 jump

		{ 0, 200, 100, 100 },
		{ 100, 200, 100, 100 },
		{ 200, 200, 100, 100 },
		{ 300, 200, 100, 100 },
		{ 400, 200, 100, 100 },
		{ 500, 200, 100, 100 },
		{ 600, 200, 100, 100 },
		{ 700, 200, 100, 100 },
		{ 800, 200, 100, 100 },
		{ 900, 200, 100, 100 },//10 walk

		{ 0, 300, 100, 100 },
		{ 100, 300, 100, 100 },
		{ 200, 300, 100, 100 },
		{ 300, 300, 100, 100 },//4 dead

		{ 0, 400, 100, 100 },
		{ 100, 400, 100, 100 },
		{ 200, 400, 100, 100 },//3 defend
	};
	const int SAMURAI_FRAMES = sizeof(SAMURAI) / sizeof(int) / 4;

	/*
	struct Sprite {
		SDL_Texture* texture;
		std::vector<SDL_Rect> clips;
		int currentFrame = 0;

		void init(SDL_Texture* _texture, int frames, const int _clips[][4]);
		void tick();

		const SDL_Rect* getCurrentClip() const;
	};
	*/

	class Sprite
	{
	public:
		Sprite(); 
		~Sprite();
		bool LoadImg(std::string path, SDL_Renderer* des);

		//void HandleCamera(SDL_Rect& camera);
		//void Update(); // cho map
	
		//void HandleInput(SDL_Event& event);
		void handleMovementInput(SDL_Event& event);
		void updateMovement(float deltaTime);

		void render(SDL_Renderer* des);

	private:
		float x_pos_ = 0;
		float y_pos_ = 0;

		//float x_val_;
		//float y_val_;

		int frame_count = 0;
		const int MAX_FRAME = 8;

		SDL_Texture* p_text;

	};



	#endif // !SPRITE_H

