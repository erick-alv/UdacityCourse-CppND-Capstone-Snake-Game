#include "doubleScore.h"
#include "game.h"

void DoubleScore::CollectedActionStart() {
    game->SetIncr(2);
}

void DoubleScore::CollectedActionFinish() {
    game->SetIncr(1);
}

void DoubleScore::RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block){
    std::unique_lock<std::mutex> lck(_mutex);
    PowerupState currentState = _state;
    lck.unlock();
    if(currentState == PowerupState::ON_FIELD) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xCC, 0xFF, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}