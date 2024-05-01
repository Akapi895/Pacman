#ifndef SETTING_GAME_H_
#define SETTING_GAME_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "PacmanObject.h"
#include "Timer.h"
#include "TextObject.h"
#include "PetObject.h"
#include "PacManDie.h"
#include "MusicGame.h"
#include "RenderGame.h"
#include "MouseButton.h"

bool initData(SDL_Window* window, SDL_Renderer*& renderer, TTF_Font*& fontText);
void startGame(SDL_Renderer* renderer, SDL_Event* event_);

void stopAndResumeGame(SDL_Event* event_, Timer& timeGame, MusicGame& gameMusic, bool & stopSound, bool& newGame);

void loadImageAndSetPosition(BaseObject& gBackground, BaseObject& pacmanLivesImage, BaseObject& smallLight, SDL_Renderer* renderer,
	MouseButton& buttonStopMusic, MouseButton& buttonStopSound, GameMap& gameMap, const int& mapNumber);
void settingPacmanAndPets(SDL_Renderer* renderer, PacmanObject& pacman,
	PetObject* pets, const int& numberItems, const int& score);

void pacmanDoing(PacmanObject& pacman, GameMap& gameMap, SDL_Renderer* renderer, MusicGame* gameMusic);
void petDoing(PetObject* pets, GameMap& gameMap, SDL_Renderer* renderer, PacmanObject& pacman, const int& numberDifficult);

void settingTime(Timer& timer);
void statusGame(PacmanObject& pacman, bool& isQuitGame, bool& winGame, int timeCurrent, int numberDie);

void statusMusic();
void statusSound(bool& stopSound, MusicGame& gameMusic);

void checkCollisionPacmanWithPets(PacmanObject& pacman, SDL_Renderer* renderer, GameMap& renderMap,
	BaseObject& renderBacGround, PetObject* pets, int& numberDie, MusicGame& gameMusic);
void solveCollision(PacmanObject& pacman, SDL_Renderer* renderer,
	GameMap& renderMap, BaseObject& renderBackground, PetObject* pets);

void settingWinGame(MusicGame& gameMusic, SDL_Renderer* renderer, BaseObject& background, int& mapNumber);

void settingLostGame(MusicGame& gameMusic, SDL_Renderer* renderer, const int numberDie, int& score,
	TTF_Font*& fontText, TextObject scoreGame, SDL_Event* event_);

#endif // !SETTING_GAME_H_
