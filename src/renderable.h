#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <vector>
#include "SDL.h"

class Renderable {

public:
    virtual void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block) = 0;


};

#endif