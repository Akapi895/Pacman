#include "SettingGame.h"
#include <time.h>

void letsPlay() {
    initData(gWindow, gRenderer, gFontText);

	int levelDifficult = 5;
	int mapNumber = 1;
	int score = 0;
	bool winGame = false;

	SDL_Event event;

	while(true) {
//        int x, y;
//        SDL_GetMouseState(&x, &y);
//        cerr << "Down at (" << x << ", " << y << ")\n";

		bool newGame = false;
		bool isQuitGame = false;

		int numberDie = 0;
		int timeCurrent = 0;

		MusicGame gameMusic;
		gameMusic.loadMusic();

		Mix_PlayMusic(gameMusic.getMusicBackground(), -1);

		if (Mix_PausedMusic() == 1) Mix_ResumeMusic();

		BaseObject gBackground;
		BaseObject pacmanLivesImage;
		BaseObject smallLight;

		GameMap gameMap;

		MouseButton buttonStopMusic;
		MouseButton buttonStopSound;
		bool stopSound = false;

		loadImageAndSetPosition(gBackground, pacmanLivesImage, smallLight, gRenderer, buttonStopMusic, buttonStopSound, gameMap, mapNumber);
		int numberItems = gameMap.getNumberItems();

		PacmanObject pacman;
		PetObject pets[NUMBER_PET_];
		settingPacmanAndPets(gRenderer, pacman, pets, numberItems, score);

		if (winGame == false) {
			startGame(gRenderer, &gEvent);
			renderSelectDifficulty(gRenderer, &gEvent, isQuitGame, levelDifficult);
		}

		Timer fpsTimer;
		Timer timeGame;
		timeGame.start();

		TextObject scoreGame;
		TextObject textTimeGame;
		TextObject pacmanLives;

		Mix_PlayChannel(-1, gameMusic.getMusicStartGame(), 0);
		while (!isQuitGame) {
			srand(time(0));
			SDL_RenderClear(gRenderer);

			fpsTimer.start();
			gBackground.render(gRenderer, NULL);

			while (SDL_PollEvent(&gEvent) != 0) {
				if (gEvent.type == SDL_QUIT) exit(1);

				if (gEvent.key.keysym.sym == SDLK_n && SDL_GetModState() & KMOD_CTRL) {
					newGame = true;
					mapNumber = 1;
					pacman.setScore(0);
					winGame = false;
					settingLostGame(gameMusic, gRenderer, numberDie, score, gFontText, scoreGame, &gEvent);
				}

				stopAndResumeGame(&gEvent, timeGame, gameMusic, stopSound, newGame);

				if (renderStopSound(smallLight, &gEvent, gRenderer, buttonStopSound))
                    statusSound(stopSound, gameMusic);

				if (renderStopMusic(smallLight, &gEvent, gRenderer, buttonStopMusic))
                    statusMusic();

				pacman.handleInput(gEvent);
			}

			renderLineStop(gRenderer, stopSound);
			gameMap.drawMap(gRenderer);
			pacmanDoing(pacman, gameMap, gRenderer, &gameMusic, levelDifficult);
			petDoing(pets, gameMap, gRenderer, pacman, levelDifficult);

			score = pacman.getScore();
			timeCurrent = TIME_PLAY - timeGame.getTicks() / 1000;

			renderScoreText(score, gFontText, scoreGame, gRenderer);
			renderTimeText(timeCurrent, gFontText, textTimeGame, gRenderer);
			renderPacmanLiveText(NUMBER_LIVES_ - numberDie, gFontText, pacmanLives, gRenderer, pacmanLivesImage);

			SDL_RenderPresent(gRenderer);

			settingTime(fpsTimer);
			checkCollisionPacmanWithPets(pacman, gRenderer, gameMap, gBackground, pets, numberDie, gameMusic);
			statusGame(pacman, isQuitGame, winGame, timeCurrent, numberDie);

            winGame == true;
			if (isQuitGame == true && winGame == false) {
				settingLostGame(gameMusic, gRenderer, numberDie, score, gFontText, scoreGame, &gEvent);
			}
			else if (isQuitGame == true && winGame == true) {
				settingWinGame(gameMusic, gRenderer, gBackground, mapNumber);
			}
			else if (newGame == true) {
				break;
			}
		}
	}
}
