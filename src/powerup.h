#ifndef POWERUP_H
#define POWERUP_H


#include "renderable.h"
#include <mutex>

class Game; //Forward declaration


enum PowerupState {
    ON_FIELD,
    OFF_FIELD,
    COLLECTED
};

class Powerup: public Renderable {
public:

    Powerup(int* incrementer, Game* g);
    ~Powerup();
    void Start();
    void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block);
    void CheckCollection(int snake_x, int snake_y);
    void ToggleState(); //Run by a separate thread;
    PowerupState GetState();

    int x = 0;
    int y = 0;

    //TODO not have pointer, but pointer to function that sets the value
    int* gameScoreIncrementer;
    Game *game;

private:

    std::vector<std::thread> threads;

    //variables accessed by multiple threads
    PowerupState _state{PowerupState::OFF_FIELD};
    bool _runThread{true};
    std::mutex _mutex;    
};

#endif