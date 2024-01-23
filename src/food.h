#ifndef FOOD_H
#define FOOD_H

#include "renderable.h"

class Food: public Renderable {
public:
    
    void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block);

    int x = 0;
    int y = 0;

};

#endif