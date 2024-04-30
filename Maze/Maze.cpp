#include "defs.h"
#include "graphics.h"
#include "move.h"
#include "sprite.h"

using namespace std;

int main(int argc, char** argv) {
    Graphics graphics;
    graphics.init();

    Mouse mouse(SIZE * 5 / 2, SIZE * 5 / 2);
    
    SDL_Event event;

    Sprite sam;
    SDL_Texture* samTexture = graphics.loadTexture("image\\sprites\\sam.png");
    sam.init(samTexture, SAMURAI_FRAMES, SAMURAI);
    

    bool flag = 1;
    while (flag) {
        SDL_GetMouseState(&mouse.posx, &mouse.posy);

        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:

            break;
        case SDL_MOUSEBUTTONDOWN:
            cerr << "Down at (" << mouse.posx << ", " << mouse.posy << ")\n";
            break;
        case SDL_MOUSEBUTTONUP:
            cerr << "Up at (" << mouse.posx << ", " << mouse.posy << ")\n";
            break;
        }

        sam.tick();
        graphics.prepareScene();
        graphics.render(400, 400, sam);
        
        mouse.keyPress();

        //mouse.render(graphics);


        graphics.presentScene();
        SDL_Delay(50);
    }

    SDL_DestroyTexture(samTexture); samTexture = nullptr;

    graphics.quit();

    return 0;

}
