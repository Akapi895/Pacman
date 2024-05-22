#ifndef RENDER_GAME_H
#define RENDER_GAME_H

#include "CommonFunction.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "MouseButton.h"

void renderSelectDifficulty(SDL_Renderer* renderer, SDL_Event* event_,
                           bool& isQuitGame, int& numberDiffcult);

void renderScoreText(const int& scoreGame, TTF_Font*& fontText,
                     TextObject& moneyText, SDL_Renderer* renderer);

void renderTimeText(const int& gameTime, TTF_Font*& fontText,
                    TextObject& timeText, SDL_Renderer* renderer);

void renderPacmanLiveText(const int& numberLives, TTF_Font*& fontText,
                            TextObject& livesText, SDL_Renderer* renderer,
                             BaseObject& livesImage);

bool renderStopMusic(BaseObject& smallLight, SDL_Event* event_,
                     SDL_Renderer* renderer, MouseButton& buttonStopMusic);

void renderLineStop(SDL_Renderer* renderer, bool stopSound);

bool renderStopSound(BaseObject& smallLight, SDL_Event* event_,
                     SDL_Renderer* renderer, MouseButton& buttonStopSound);

void renderImageWinGame(SDL_Renderer* renderer, BaseObject* background);

void renderImageLossGame(const int& scoreGame, TTF_Font*& fontText,
                         TextObject& moneyText, SDL_Renderer* renderer, SDL_Event* events_);

void renderImageRankScore(BaseObject& imageLossGame,
                          vector<int> rankScore, SDL_Event* event_,
                          SDL_Renderer* renderer, TTF_Font*& fontText);

#endif // RENDER_GAME_H

