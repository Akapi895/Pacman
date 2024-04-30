#include "move.h"
#include "graphics.h"
#include "sprite.h"

Mouse::Mouse() {
    //_char = SDL_IMGLOAD
}
Mouse::Mouse(int a, int b) { x = a; y = b; }

void Mouse::move() {
    if (dx < 0) { //le trai
        if (x < speed) return;
    }
    if (dy < 0) { //le tren
        if (y < speed) return;
    }
    if (dx > 0) // le phai
        if (x + speed >= SCREEN_WIDTH - SPRITE_SIZE) return;
    if (dy > 0) // le duoi
        if (y + speed >= SCREEN_HEIGHT - SPRITE_SIZE) return;


    x += dx;
    y += dy;
    //chi di chuyen 1 lan moi click
    dx = 0;
    dy = 0;
}
void Mouse::keyPress() {
    currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W]) {
        turnNorth();

    }
    if (currentKeyStates[SDL_SCANCODE_S]) turnSouth();
    if (currentKeyStates[SDL_SCANCODE_A]) turnWest();
    if (currentKeyStates[SDL_SCANCODE_D]) turnEast();

    move();
}
void Mouse::turnNorth() {
    dy = -speed;
    dx = 0;
}
void Mouse::turnSouth() {
    dy = speed;
    dx = 0;
}
void Mouse::turnWest() {
    dy = 0;
    dx = -speed;
}
void Mouse::turnEast() {
    dy = 0;
    dx = speed;
}
void Mouse::turnNorthEast() {
    dx = speed;
    dy = speed;
}
void Mouse::turnNorthWest() {
    dx = -speed;
    dy = -speed;
}
void Mouse::turnSouthWest() {
    dx = -speed;
    dy = speed;
}
void Mouse::turnSouthEast() {
    dx = speed;
    dy = -speed;
}

void Mouse::render(Graphics& graphics) {
    Sprite sprite;

    //sprite.("image//sprites//demon.png", graphics);    
    
    
    int frame = 0;
    if (dx != 0) {
        
    }
    else {
        
    }
    
    
    
    //sprite.render(graphics, x, y, &sprite._spriteClips[0]);
    
    
    SDL_Rect filled_rect;
    filled_rect.x = x;
    filled_rect.y = y;
    filled_rect.w = 20;
    filled_rect.h = 20;
    SDL_SetRenderDrawColor(graphics._renderer, 255, 0, 255, 0); // blue
    SDL_RenderFillRect(graphics._renderer, &filled_rect);

}
bool Mouse::gameOver() {
    return x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT;
}