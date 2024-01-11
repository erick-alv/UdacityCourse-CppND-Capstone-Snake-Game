#include "food.h"

void Food::RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block) const{
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = x * block.w;
    block.y = y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
}