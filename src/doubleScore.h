#ifndef DOUBLESCORE_H
#define DOUBLESCORE_H

#include "powerup.h"

class DoubleScore: public Powerup {
public:
    using Powerup::Powerup;
    void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block);

private:
    void CollectedActionStart();
    void CollectedActionFinish();
    
};

#endif