#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static TTF_Font* gFontText = NULL;

const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 640;

const int COLOR_RENDER_DEFAULT = 255;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int TILE_SIZE = 32;
const string GAME_TITLE = "PACMAN_23021709";

const int FRAME_PER_SECOND = 8;

const int NUMBER_PET_ = 4; //ảo ma

const int TIME_PLAY = 300; // 5 phút

const int SIZE_TEXT_ = 28;

const int NUMBER_LIVES_ = 3;

const int MAX_NUMBER_MAP_ = 5; // check

#define START_PACMAN_X_ 13
#define START_PACMAN_Y_ 4
#define PACMAN_FRAME_  8
#define VEL_PACMAN_ 8 //la sao

#define PACMAN_DIE_FRAME_ 10

#define START_PET_X_ 13
#define START_PET_Y_ 8
#define PET_FRAME_ 4
#define VEL_PET_ 8 //???

#define PIXEL_CLIP_ 32
#define MAX_MAP_X 35
#define MAX_MAP_Y 20

#define TILE_WALL_ 9
#define TILE_PAC_DOTS_ 8
#define TILE_PAC_BIG_DOTS_ 6
#define TILE_WALL_2_ 5
#define TILE_NONE_ 0

enum GoType
{
	GO_NONE  = 0,
	GO_RIGHT = 1,
	GO_LEFT  = 2,
	GO_UP    = 3,
	GO_DOWN  = 4
};

static SDL_Color COLOR_KEY_WHITE_ = { 255, 255, 255 };
static SDL_Color COLOR_KEY_BLACK_ = { 0, 0, 0 };

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

#define WIDTH_BUTTON_ 130
#define HEIGHT_BUTTON_ 90

#define WIDTH_BUTTON_SOUND_ 64
#define HEIGHT_BUTTON_SOUND_ 64

#define X_BUTTON_START_GAME_ 810
#define Y_BUTTON_START_GAME_ 310

#define X_BUTTON_INTRODUCTION_ 830
#define Y_BUTTON_INTRODUCTION_ 415

#define X_BUTTON_OUT_INTRODUCTION_ 530
#define Y_BUTTON_OUT_INTRODUCTION_ 560

#define X_BUTTON_DIFFERENT_GAME_ 870
#define Y_BUTTON_DIFFERENT_GAME_ 510

#define X_BUTTON_RETURN_GAME_ 335
#define Y_BUTTON_RETURN_GAME_ 540

#define X_BUTTON_SAVE_SCORE_ 700
#define Y_BUTTON_SAVE_SCORE_ 540

#define X_BUTTON_NEXT_GAME_ 383
#define Y_BUTTON_NEXT_GAME_ 430

#define X_BUTTON_STOP_MUSIC_ 930
#define Y_BUTTON_STOP_MUSIC_ 570

#define X_BUTTON_STOP_SOUND_ 1000
#define Y_BUTTON_STOP_SOUND_ 570

#define X1_LINE_STOP_MUSIC_ 950
#define X2_LINE_STOP_MUSIC_ 980
#define Y1_LINE_STOP_MUSIC_ 580
#define Y2_LINE_STOP_MUSIC_ 620

#define X1_LINE_STOP_SOUND_ 1020
#define X2_LINE_STOP_SOUND_ 1050
#define Y1_LINE_STOP_SOUND_ 580
#define Y2_LINE_STOP_SOUND_ 620

#define WIDTH_BUTTON_1_ 150
#define HEIGHT_BUTTON_1_ 60

#define X_BUTTON_EASY_GAME_ 505
#define	Y_BUTTON_EASY_GAME_ 150

#define X_BUTTON_NOMAL_GAME_ 505
#define Y_BUTTON_NOMAL_GAME_ 215

#define X_BUTTON_HARD_GAME_ 505
#define Y_BUTTON_HARD_GAME_ 280

#define X_BUTTON_VERY_HARD_GAME_ 505
#define Y_BUTTON_VERY_HARD_GAME_ 345

#define X_BUTTON_CANCEL_ 525
#define Y_BUTTON_CANCEL_ 435
#endif // COMMON_FUNCTION_H_
