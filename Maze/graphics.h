#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "defs.h"

struct Sprite;

struct Graphics {
    SDL_Renderer* _renderer;
    SDL_Window* _window;

    void logErrorAndExit(const char* msg, const char* error);

    void init();

    void prepareScene(SDL_Texture* background = nullptr);
    
    void presentScene();

    SDL_Texture* loadTexture(const char* filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void render(int x, int y, const Sprite& sprite);

    void quit();
};


#endif

