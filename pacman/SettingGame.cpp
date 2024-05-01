#include "SettingGame.h"

bool initData(SDL_Window* window, SDL_Renderer*& renderer,
	TTF_Font*& fontText)
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(GAME_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) success = false;
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, COLOR_RENDER_DEFAULT, COLOR_RENDER_DEFAULT,
				COLOR_RENDER_DEFAULT, COLOR_RENDER_DEFAULT);
			int imgFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlag) & imgFlag))
			{
				success = false;
			}

			if (TTF_Init() == -1)
			{
				success = false;
			}
			else
			{
				fontText = TTF_OpenFont("font//pacman.ttf", SIZE_TEXT_);
				if (fontText == NULL)
				{
					success = false;
				}
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				success = false;
			}
		}
	}
	return success;
}

void startGame(SDL_Renderer* renderer, SDL_Event* event_)
{
	BaseObject startBackground;
	startBackground.loadImage("image/start_game_.png", renderer);

	MouseButton buttonStartGame;
	buttonStartGame.setPositionObject(X_BUTTON_START_GAME_, Y_BUTTON_START_GAME_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	MouseButton buttonIntroduction;
	buttonIntroduction.setPositionObject(X_BUTTON_INTRODUCTION_, Y_BUTTON_INTRODUCTION_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	MouseButton buttonOutIntroduction;
	buttonOutIntroduction.setPositionObject(X_BUTTON_OUT_INTRODUCTION_, Y_BUTTON_OUT_INTRODUCTION_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	MouseButton buttonDifferentGame;
	buttonDifferentGame.setPositionObject(X_BUTTON_DIFFERENT_GAME_, Y_BUTTON_DIFFERENT_GAME_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	BaseObject smallLight;
	smallLight.loadImage("image/small_light.png", renderer);

	bool startGame = false;
	while (!startGame)
	{
		SDL_PollEvent(event_);
		if (event_->type == SDL_QUIT)
		{
			exit(1);
		}

		SDL_RenderClear(renderer);
		startBackground.render(renderer);

		if (buttonStartGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_START_GAME_, Y_BUTTON_START_GAME_);
			smallLight.render(renderer);

			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				startGame = true;
			}
		}

		if (buttonIntroduction.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_INTRODUCTION_, Y_BUTTON_INTRODUCTION_);
			smallLight.render(renderer);

			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				BaseObject instructionImage;
				instructionImage.loadImage("image/instruction_game_.png", renderer);
				smallLight.setRect(X_BUTTON_OUT_INTRODUCTION_, Y_BUTTON_OUT_INTRODUCTION_);

				bool isOutInstruction = false;
				while (!isOutInstruction)
				{
					SDL_RenderClear(renderer);
					instructionImage.render(renderer);
					SDL_PollEvent(event_);
					if (event_->type == SDL_QUIT)
					{
						exit(1);
					}
					if (buttonOutIntroduction.handleEvent(event_, renderer))
					{

						smallLight.render(renderer);
						if (event_->type == SDL_MOUSEBUTTONDOWN)
						{
							isOutInstruction = true;

						}
					}

					SDL_RenderPresent(renderer);
				}
			}
		}

		if (buttonDifferentGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_DIFFERENT_GAME_, Y_BUTTON_DIFFERENT_GAME_);
			smallLight.render(renderer);

			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_OpenURL("https:///gamevui.vn/");
			}
		}

		SDL_RenderPresent(renderer);
	}
}

void stopAndResumeGame(SDL_Event* event_, Timer& timeGame, MusicGame& gameMusic, bool& stopSound, bool& newGame)
{
	if (event_->type == SDL_QUIT)
	{
		exit(1);
	}
	if (event_->key.keysym.sym == SDLK_p && SDL_GetModState() & KMOD_CTRL)
	{
		timeGame.paused();

		bool isStopSound = false;
		if (stopSound == true)
		{
			isStopSound = true;
			stopSound = false;
		}
		statusSound(stopSound, gameMusic);
		while (true)
		{
			SDL_PollEvent(event_);
			if (event_->type == SDL_QUIT)
			{
				exit(1);
			}
			if (event_->key.keysym.sym == SDLK_r && SDL_GetModState() & KMOD_CTRL)
			{
				break;
			}
			if (event_->key.keysym.sym == SDLK_n && SDL_GetModState() & KMOD_CTRL)
			{
				newGame = true;
				return;
			}
		}
		timeGame.unpaused();
		if (isStopSound == false)
		{
			statusSound(stopSound, gameMusic);
		}

	}
	
}

void loadImageAndSetPosition(BaseObject& gBackground, BaseObject& pacmanLivesImage, BaseObject& smallLight, SDL_Renderer* renderer,
	MouseButton& buttonStopMusic, MouseButton& buttonStopSound, GameMap& gameMap, const int& mapNumber)
{
	gBackground.loadImage("image/background" + to_string(mapNumber) + ".png", renderer);
	pacmanLivesImage.loadImage("image/pacman_lives.png", renderer);
	smallLight.loadImage("image/small_light64.png", renderer, &COLOR_KEY_WHITE_);

	buttonStopMusic.setPositionObject(X_BUTTON_STOP_MUSIC_, Y_BUTTON_STOP_MUSIC_, WIDTH_BUTTON_SOUND_, HEIGHT_BUTTON_SOUND_);
	buttonStopSound.setPositionObject(X_BUTTON_STOP_SOUND_, Y_BUTTON_STOP_SOUND_, WIDTH_BUTTON_SOUND_, HEIGHT_BUTTON_SOUND_);

	gameMap.loadMap("map/map0" + to_string(mapNumber) + ".dat");
	gameMap.loadTiles(renderer);
}

void settingPacmanAndPets(SDL_Renderer* renderer, PacmanObject& pacman, PetObject* pets, const int& numberItems, const int& score)
{
	pacman.setStartPacman(renderer, &COLOR_KEY_WHITE_);
	pacman.setNumberItems(numberItems);
	pacman.setScore(score);

	for (int i = 0; i < NUMBER_PET_; i++)
	{
		pets[i].setPetNumber(i);
		pets[i].setStartPet(renderer, &COLOR_KEY_BLACK_);
	}
}

void pacmanDoing(PacmanObject& pacman, GameMap& gameMap, SDL_Renderer* renderer, MusicGame* gameMusic)
{
	pacman.setDirection(gameMap, renderer);
	pacman.pacmanMove(gameMap);
	pacman.checkToItem(gameMap, gameMusic);
	pacman.render(renderer);
}

void petDoing(PetObject* pets, GameMap& gameMap, SDL_Renderer* renderer, PacmanObject& pacman, const int& levelDifficult)
{
	for (int i = 0; i < NUMBER_PET_; i++)
	{
		int randomAutoDirect = rand() % levelDifficult;
		if (randomAutoDirect % levelDifficult == 0)
		{
			pets[i].autoAiInputDirect(gameMap, pacman);
		}
		else
		{
			pets[i].autoInputDirect(gameMap);
		}

		pets[i].setDirection(gameMap, renderer);
		pets[i].petMove(gameMap);
		pets[i].render(renderer);
	}
}

void settingTime(Timer& timer)
{
	int timeCurrent = timer.getTicks();
	int timePerFrame = 1000 / FRAME_PER_SECOND;

	if (timeCurrent < timePerFrame)
	{
		//cout << timeCurrent << endl;
		SDL_Delay(timePerFrame - timeCurrent);
	}
}

void statusGame(PacmanObject& pacman, bool& isQuitGame, bool& winGame, int timeCurrent, int numberDie)
{
	if (pacman.getNumberItems() == 0)
	{
		isQuitGame = true;
		winGame = true;
	}
	else if (timeCurrent <= 0 || (NUMBER_LIVES_ - numberDie) == 0)
	{
		isQuitGame = true;
		winGame = false;
	}
}

void statusMusic()
{
	if (Mix_PausedMusic() == true)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void statusSound(bool& stopSound, MusicGame& gameMusic)
{
	if (stopSound == false)
	{
		gameMusic.free();
		stopSound = true;
	}
	else
	{
		gameMusic.loadMusic();
		Mix_PlayMusic(gameMusic.getMusicBackground(), -1);
		Mix_ResumeMusic();
		stopSound = false;
	}
}

void checkCollisionPacmanWithPets(PacmanObject& pacman, SDL_Renderer* renderer, GameMap& renderMap,
	BaseObject& renderBackGround, PetObject* pets, int& numberDie, MusicGame& gameMusic)
{
	for (int i = 0; i < NUMBER_PET_; i++)
	{
		SDL_Rect pacmanPos = pacman.getPos();
		SDL_Rect petPos = pets[i].getRect();
		if (checkCollision(pacmanPos, petPos))
		{
			Mix_PlayChannel(-1, gameMusic.getMusicDie(), 0);
			solveCollision(pacman, renderer, renderMap, renderBackGround, pets);
			numberDie++;
		}
	}
}

void solveCollision(PacmanObject& pacman, SDL_Renderer* renderer,
	GameMap& renderMap, BaseObject& renderBackground, PetObject* pets)
{
	const SDL_Rect pacmanDiePos = pacman.getPos();
	const int goType = pacman.getGoType();

	PacmanDie pacmanDie;
	pacmanDie.setImage(goType, pacmanDiePos, renderer, renderMap, renderBackground);

	pacman.setStartPacman(renderer, &COLOR_KEY_WHITE_);
	for (int i = 0; i < NUMBER_PET_; i++)
	{
		pets[i].setStartPet(renderer, &COLOR_KEY_WHITE_);
	}
}

void settingWinGame(MusicGame& gameMusic, SDL_Renderer* renderer, BaseObject& background, int& mapNumber)
{
	Mix_PauseMusic();
	Mix_PlayChannel(-1, gameMusic.getWinGame(), 0);
	renderImageWinGame(renderer, &background);

	mapNumber++;
	if (mapNumber > MAX_NUMBER_MAP_)
	{
		mapNumber = MAX_NUMBER_MAP_;
	}
	Mix_HaltMusic();
}

void settingLostGame(MusicGame& gameMusic, SDL_Renderer* renderer, const int numberDie, int& score,
	TTF_Font*& fontText, TextObject scoreGame, SDL_Event* event_)
{
	Mix_PauseMusic();
	if (NUMBER_LIVES_ - numberDie == 0)
	{
		Mix_PlayChannel(-1, gameMusic.getMusicLiveOut(), 0);
	}
	else
	{
		Mix_PlayChannel(-1, gameMusic.getMusicTimeOut(), 0);
	}
	renderImageLossGame(score, fontText, scoreGame, renderer, event_);
	score = 0;
	Mix_HaltMusic();
}
