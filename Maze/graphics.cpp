#include "graphics.h"
#include "sprite.h"

void Graphics::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
        "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    _window = SDL_CreateWindow("Hello Maze", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    _renderer = SDL_CreateRenderer(_window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture* background)
{
    if (background == nullptr) {
        SDL_RenderClear(_renderer);
        SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(_renderer);
    }
    else {
        SDL_RenderCopy(_renderer, background, NULL, NULL);
        
    }
}


void Graphics::presentScene()
{
    SDL_RenderPresent(_renderer);
}

SDL_Texture* Graphics::loadTexture(const char* filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
        "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(_renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(_renderer, texture, NULL, &dest);
}

void Graphics::quit()
{
    IMG_Quit();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Graphics::render(int x, int y, const Sprite& sprite) {
    //const SDL_Rect* clip = sprite.getCurrentClip();
    //SDL_Rect renderQuad = { x, y, clip->w, clip->h };
    //SDL_RenderCopy(_renderer, sprite.texture, clip, &renderQuad);
}
