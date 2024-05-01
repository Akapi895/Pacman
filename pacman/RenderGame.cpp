#include "RenderGame.h"

void renderScoreText(const int& scoreGame, TTF_Font*& fontText, TextObject& moneyText, SDL_Renderer* renderer)
{
	moneyText.setText("SCORE:");
	moneyText.loadFromRenderText(fontText, renderer);
	moneyText.renderText(renderer, SCREEN_WIDTH - 195, 45);

	string scoreRender = to_string(scoreGame);

	moneyText.setText(scoreRender);
	moneyText.loadFromRenderText(fontText, renderer);
	moneyText.renderText(renderer, 995 - moneyText.getWidth() / 2, 90);
}

bool renderStopMusic(BaseObject& smallLight, SDL_Event* event_, SDL_Renderer* renderer, MouseButton& buttonStopMusic)
{
	if (!buttonStopMusic.handleEvent(event_, renderer))
	{
		return false;
	}
	smallLight.setRect(X_BUTTON_STOP_MUSIC_, Y_BUTTON_STOP_MUSIC_);
	smallLight.render(renderer);
	if (event_->type == SDL_MOUSEBUTTONDOWN)
	{
		return true;
	}
	return false;
}

void renderSlectDifficulty(SDL_Renderer* renderer, SDL_Event* event_, bool& isQuitGame, int& numberDifficult)
{
	BaseObject imageSelectDifficulty;
	imageSelectDifficulty.loadImage("image/selectDifficulty.png", renderer);

	BaseObject startBackground;
	startBackground.loadImage("image/start_game_.png", renderer);

	BaseObject smallLight;
	smallLight.loadImage("image/small_light.png", renderer);

	MouseButton buttonEasyGame;
	buttonEasyGame.setPositionObject(X_BUTTON_EASY_GAME_, Y_BUTTON_EASY_GAME_, WIDTH_BUTTON_1_, HEIGHT_BUTTON_1_);

	MouseButton buttonNomalGame;
	buttonNomalGame.setPositionObject(X_BUTTON_NOMAL_GAME_, Y_BUTTON_NOMAL_GAME_, WIDTH_BUTTON_1_, HEIGHT_BUTTON_1_);

	MouseButton buttonHardGame;
	buttonHardGame.setPositionObject(X_BUTTON_HARD_GAME_, Y_BUTTON_HARD_GAME_, WIDTH_BUTTON_1_, HEIGHT_BUTTON_1_);

	MouseButton buttonVeryHardGame;
	buttonVeryHardGame.setPositionObject(X_BUTTON_VERY_HARD_GAME_, Y_BUTTON_VERY_HARD_GAME_, WIDTH_BUTTON_1_, HEIGHT_BUTTON_1_);

	MouseButton buttonCancel;
	buttonCancel.setPositionObject(X_BUTTON_CANCEL_, Y_BUTTON_CANCEL_, WIDTH_BUTTON_1_, HEIGHT_BUTTON_1_);

	bool isQuitImage = false;
	while (!isQuitImage)
	{
		SDL_RenderClear(renderer);
		startBackground.render(renderer);
		imageSelectDifficulty.render(renderer);
		SDL_PollEvent(event_);
		if (event_->type == SDL_QUIT)
		{
			exit(5);
		}
		if (buttonEasyGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_EASY_GAME_, Y_BUTTON_EASY_GAME_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				numberDifficult = 10;
				return;
			}
		}
		if (buttonNomalGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_NOMAL_GAME_, Y_BUTTON_NOMAL_GAME_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				numberDifficult = 5;
				return;
			}
		}
		if (buttonHardGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_HARD_GAME_, Y_BUTTON_HARD_GAME_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				numberDifficult = 3;
				return;
			}
		}
		if (buttonVeryHardGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_VERY_HARD_GAME_, Y_BUTTON_VERY_HARD_GAME_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				numberDifficult = 2;
				return;
			}
		}
		if (buttonCancel.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_CANCEL_, Y_BUTTON_CANCEL_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				isQuitGame = true;
				return;
			}
		}

		SDL_RenderPresent(renderer);
	}
}

void renderPacmanLiveText(const int& numberLives, TTF_Font*& fontText, TextObject& livesText, SDL_Renderer* renderer, BaseObject& livesImage)
{
	livesText.setText("LIVES:");
	livesText.loadFromRenderText(fontText, renderer);
	livesText.renderText(renderer, SCREEN_WIDTH - 195, 315);

	for (int i = 0; i < numberLives; i++)
	{
		livesImage.setRect(i * (TILE_SIZE * 1.5) + 930, 355);
		livesImage.render(renderer);
	}

}

void renderTimeText(const int& gameTime, TTF_Font*& fontText, TextObject& timeText, SDL_Renderer* renderer)
{
	timeText.setText("TIME:");
	timeText.loadFromRenderText(fontText, renderer);
	timeText.renderText(renderer, SCREEN_WIDTH - 185, 175);

	string stringRender = to_string(gameTime);

	timeText.setText(stringRender);
	timeText.loadFromRenderText(fontText, renderer);
	timeText.renderText(renderer, 995 - timeText.getWidth() / 2, 220);
}

void renderImageWinGame(SDL_Renderer* renderer, BaseObject* background)
{
	BaseObject imageBackGroundWinGame;
	imageBackGroundWinGame.loadImage("image/backgroundWinGame.PNG", renderer);

	MouseButton buttonNextGame;
	buttonNextGame.setPositionObject(X_BUTTON_NEXT_GAME_, Y_BUTTON_NEXT_GAME_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	BaseObject smallLight;
	smallLight.loadImage("image/small_light.png", renderer);

	SDL_Event event_;

	bool isQuit = false;

	while (!isQuit)
	{
		SDL_RenderClear(renderer);
		background->render(renderer);

		imageBackGroundWinGame.setRect(150, 25);
		imageBackGroundWinGame.render(renderer);


		SDL_PollEvent(&event_);

		if (event_.type == SDL_QUIT)
		{
			isQuit = true;
			exit(6);
		}
		if (buttonNextGame.handleEvent(&event_, renderer))
		{
			smallLight.setRect(X_BUTTON_NEXT_GAME_, Y_BUTTON_NEXT_GAME_);
			smallLight.render(renderer);
			if (event_.type == SDL_MOUSEBUTTONDOWN)
			{
				isQuit = true;
			}
		}

		SDL_RenderPresent(renderer);
	}
}


void renderLineStop(SDL_Renderer* renderer, bool stopSound)
{
	if (Mix_PausedMusic() == true)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderDrawLine(renderer, X1_LINE_STOP_MUSIC_ - 1, Y1_LINE_STOP_MUSIC_, X2_LINE_STOP_MUSIC_ - 1, Y2_LINE_STOP_MUSIC_);
		SDL_RenderDrawLine(renderer, X1_LINE_STOP_MUSIC_, Y1_LINE_STOP_MUSIC_, X2_LINE_STOP_MUSIC_, Y2_LINE_STOP_MUSIC_);
		SDL_RenderDrawLine(renderer, X1_LINE_STOP_MUSIC_ + 1, Y1_LINE_STOP_MUSIC_, X2_LINE_STOP_MUSIC_ + 1, Y2_LINE_STOP_MUSIC_);
	}

	if (stopSound == true)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderDrawLine(renderer, X1_LINE_STOP_SOUND_ - 1, Y1_LINE_STOP_SOUND_, X2_LINE_STOP_SOUND_ - 1, Y2_LINE_STOP_SOUND_);
		SDL_RenderDrawLine(renderer, X1_LINE_STOP_SOUND_, Y1_LINE_STOP_SOUND_, X2_LINE_STOP_SOUND_, Y2_LINE_STOP_SOUND_);
		SDL_RenderDrawLine(renderer, X1_LINE_STOP_SOUND_ + 1, Y1_LINE_STOP_SOUND_, X2_LINE_STOP_SOUND_ + 1, Y2_LINE_STOP_SOUND_);
	}
}

bool renderStopSound(BaseObject& smallLight, SDL_Event* event_, SDL_Renderer* renderer, MouseButton& buttonStopSound)
{
	if (!buttonStopSound.handleEvent(event_, renderer))
	{
		return false;
	}
	smallLight.setRect(X_BUTTON_STOP_SOUND_, Y_BUTTON_STOP_SOUND_);
	smallLight.render(renderer);
	if (event_->type == SDL_MOUSEBUTTONDOWN)
	{
		return true;
	}
	return false;
}

void renderImageLossGame(const int& scoreGame, TTF_Font*& fontText, TextObject& moneyText,
	SDL_Renderer* renderer, SDL_Event* event_)
{
	BaseObject imageBackGroundLostGame;
	imageBackGroundLostGame.loadImage("image/backgroundLostGame.PNG", renderer);

	MouseButton buttonReturnGame;
	buttonReturnGame.setPositionObject(X_BUTTON_RETURN_GAME_, Y_BUTTON_RETURN_GAME_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	BaseObject smallLight;
	smallLight.loadImage("image/small_light.png", renderer, &COLOR_KEY_BLACK_);

	MouseButton buttonSaveScore;
	buttonSaveScore.setPositionObject(X_BUTTON_SAVE_SCORE_, Y_BUTTON_SAVE_SCORE_, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	bool isQuit = false;

	string scoreRender = to_string(scoreGame);
	moneyText.setColor(WHITE_);
	moneyText.setText(scoreRender);
	moneyText.loadFromRenderText(fontText, renderer);

	while (!isQuit)
	{
		SDL_RenderClear(renderer);
		imageBackGroundLostGame.render(renderer);
		moneyText.renderText(renderer, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 200);
		SDL_PollEvent(event_);

		if (event_->type == SDL_QUIT)
		{
			isQuit = true;
			exit(5);
		}

		if (buttonReturnGame.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_RETURN_GAME_, Y_BUTTON_RETURN_GAME_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				isQuit = true;
			}
		}

		if (buttonSaveScore.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_SAVE_SCORE_, Y_BUTTON_SAVE_SCORE_);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				ofstream outFile("map/rankScore.txt", ios::app);
				outFile << scoreGame << endl;
				ifstream inFile("map/rankScore.txt");
				vector<int> v;
				while (!inFile.eof())
				{
					int tmp;
					if (inFile >> tmp)
					{
						v.push_back(tmp);
					}
				}
				sort(v.rbegin(), v.rend());
				renderImageRankScore(imageBackGroundLostGame, v, event_, renderer, fontText);
			}
		}

		SDL_RenderPresent(renderer);
	}

}

void renderImageRankScore( BaseObject& imageLossGame, vector<int> rankScore, SDL_Event* event_, SDL_Renderer* renderer, TTF_Font*& fontText)
{
	BaseObject imageRankScore;
	imageRankScore.loadImage("image/rankGame.png", renderer);

	BaseObject smallLight;
	smallLight.loadImage("image/small_light.png", renderer, &COLOR_KEY_BLACK_);

	MouseButton buttonReturnRank;
	buttonReturnRank.setPositionObject(X_BUTTON_DIFFERENT_GAME_ - 330, Y_BUTTON_DIFFERENT_GAME_ - 80, WIDTH_BUTTON_, HEIGHT_BUTTON_);

	TextObject scoreText;
	scoreText.setColor(WHITE_);
	bool inRank = true;
	
	while (inRank)
	{
		SDL_RenderClear(renderer);
		SDL_PollEvent(event_);
		if (event_->type == SDL_QUIT)
		{
			exit(2);
		}

		imageLossGame.render(renderer);
		imageRankScore.render(renderer);
		for (int i = 0; i < 5 && i < rankScore.size(); i++)
		{
			scoreText.setText(to_string(i + 1) + ".   " + to_string(rankScore[i]));
			scoreText.loadFromRenderText(fontText, renderer);
			scoreText.renderText(renderer, 430, 180 + i * 50);
		}
		if (buttonReturnRank.handleEvent(event_, renderer))
		{
			smallLight.setRect(X_BUTTON_DIFFERENT_GAME_ - 330, Y_BUTTON_DIFFERENT_GAME_ - 80);
			smallLight.render(renderer);
			if (event_->type == SDL_MOUSEBUTTONDOWN)
			{
				inRank = false;
			}
		}
		SDL_RenderPresent(renderer);
	}
}
