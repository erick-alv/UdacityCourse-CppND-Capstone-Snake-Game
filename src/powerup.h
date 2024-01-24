#ifndef POWERUP_H
#define POWERUP_H


#include "renderable.h"
#include <mutex>
#include <thread>
#include <memory>

class Game; //Forward declaration


enum PowerupState {
    ON_FIELD,
    OFF_FIELD,
    COLLECTED
};

class Powerup: public Renderable {
public:

    Powerup(Game* g);
    ~Powerup();
    Powerup(Powerup& other) = delete;
    Powerup& operator=(Powerup& other) = delete;
    Powerup(Powerup&& other);
    Powerup& operator=(Powerup&& other);

    void Start();
    void CheckCollection(int snake_x, int snake_y);
    void ToggleState(); //Run by a separate thread

    int x = 0;
    int y = 0;
    Game* game;

protected:

    virtual void CollectedActionStart() = 0;
    virtual void CollectedActionFinish() = 0;

    std::vector<std::thread> threads;
    //variables accessed by multiple threads
    PowerupState _state{PowerupState::OFF_FIELD};
    bool _runThread{true};
    std::mutex _mutex;  
};

#endif