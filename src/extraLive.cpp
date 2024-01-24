#include "extraLive.h"
#include "game.h"

void ExtraLive::CollectedActionStart() {
    game->IncreaseLives();
}

void ExtraLive::CollectedActionFinish() {}

void ExtraLive::RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block){
    std::unique_lock<std::mutex> lck(_mutex);
    PowerupState currentState = _state;
    lck.unlock();
    if(currentState == PowerupState::ON_FIELD) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}