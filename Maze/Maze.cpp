#include "defs.h"
#include "graphics.h"
#include "move.h"
#include "sprite.h"

using namespace std;

namespace {
    bool Init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            return false;
        }
            //logErrorAndExit("SDL_Init", SDL_GetError());

        _window = SDL_CreateWindow("Hello Maze", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (_window == nullptr)
        {
            Graphics::logErrorAndExit("CreateWindow", SDL_GetError());
            return false;
        }
        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        {
            Graphics::logErrorAndExit("SDL_image error:", IMG_GetError());
            return false;
        }            
        _renderer = SDL_CreateRenderer(_window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (_renderer == nullptr)
        { 
            Graphics::logErrorAndExit("CreateRenderer", SDL_GetError());
            return false;
        }    
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        return true;
    }

}

int main(int argc, char** argv) {
    //Graphics graphics;
    //graphics.init();
    if (!Init())
    {
        return -1;
    }

    //Mouse mouse(SIZE * 5 / 2, SIZE * 5 / 2);
    
    SDL_Event event;

    Sprite slime;
    slime.LoadImg("image\\sprites\\Red_Slime\\Idle.png", _renderer);

    bool flag = 1;
    while (flag) {
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                flag = false;
            }
            slime.HandleInput(event);
        }
        //Graphics::prepareScene();

        SDL_RenderClear(_renderer);
        
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

        slime.render(_renderer);
        SDL_RenderPresent(_renderer);

        SDL_Delay(20);
    }


    Graphics::quit();

    return 0;

}
