#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "defs.h"

struct Sprite;

static SDL_Renderer* _renderer;
static SDL_Window* _window;

namespace Graphics 
{
    

    void logErrorAndExit(const char* msg, const char* error);

    void init();

    void prepareScene(SDL_Texture* background = nullptr);
    
    void presentScene();

    SDL_Texture* loadTexture(const char* filename);

    //bool checkCollision(SDL_Rect& a, SDL_Rect& b);
    //bool checkOnMap(SDL_Rect& box); 
    
    void renderTexture(SDL_Texture* texture, int x, int y);

    void render(int x, int y, const Sprite& sprite);

    void quit();
};


#endif

