#ifndef EXTRALIVE_H
#define EXTRALIVE_H

#include "powerup.h"

class ExtraLive: public Powerup {
public:
    using Powerup::Powerup;
    void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block);

private:
    void CollectedActionStart();
    void CollectedActionFinish();
    
};

#endif