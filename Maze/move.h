#pragma once
#ifndef MOVE_H
#define MOVE_H

#define INITIAL_SPEED 10
#include "defs.h"

//struct Graphics;
//struct Sprite;

struct Mouse {
    int x, y;
    int posx, posy;
    int dx = 0, dy = 0;
    
    const Uint8* currentKeyStates;
    SDL_Texture* _char;

    
    Mouse();
    Mouse(int a, int b);
    void move();
    void keyPress();
    void turnNorth();
    void turnSouth();
    void turnWest();
    void turnEast();
    void turnNorthEast();
    void turnNorthWest();
    void turnSouthWest();
    void turnSouthEast();


    void render();
    bool gameOver();
};


#endif // !MOVE_H
