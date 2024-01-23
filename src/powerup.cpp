#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <future>
#include <thread>
#include "powerup.h"
#include "game.h"

//TODO delete not necessary inlcudes


Powerup::Powerup(int* incrementer, Game* g): gameScoreIncrementer(incrementer) {
    game = g;
}

Powerup::~Powerup() {
    std::unique_lock<std::mutex> lck(_mutex);
    _runThread = false;
    lck.unlock();
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

void Powerup::Start() {
    threads.emplace_back(std::thread(&Powerup::ToggleState, this));
}

void Powerup::RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block){
    std::unique_lock<std::mutex> lck(_mutex);
    PowerupState currentState = _state;
    lck.unlock();
    if(currentState == PowerupState::ON_FIELD) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xCC, 0xFF, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    } else if(currentState == PowerupState::COLLECTED){//todo to debug render something while collected
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}

void Powerup::CheckCollection(int snake_x, int snake_y){
    std::lock_guard<std::mutex> lg(_mutex);
    PowerupState currentState = _state;
    if(currentState == PowerupState::ON_FIELD && x == snake_x && y == snake_y) {
        game->SetIncr(2);
        _state = PowerupState::COLLECTED;
    }

}

PowerupState Powerup::GetState() {
    std::lock_guard<std::mutex> lg(_mutex);
    return _state;

}


void Powerup::ToggleState() {
    double thisCycleDuration = 0;
    double currentDuration = 0;
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    //variables for random generation
    std::uniform_int_distribution<long> distr(6000, 8000);
    std::random_device rd;
    std::mt19937 engine = std::mt19937(rd());
    
    lastUpdate = std::chrono::system_clock::now();
    std::unique_lock<std::mutex> lck(_mutex);//Lock to read condition for while
    PowerupState prevState = _state;
    while (_runThread)
    {
        lck.unlock();//Unlock for the rest
        

        //std::cout << "Here";
        //Set duration for cycle
        if(thisCycleDuration == 0) {
            thisCycleDuration = distr(engine);
            currentDuration = 0;
        }

        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        lck.lock();
        PowerupState currentState = _state;
        lck.unlock();

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        currentDuration += timeSinceLastUpdate;
        lastUpdate = std::chrono::system_clock::now();
        if(currentDuration >= thisCycleDuration) {
            thisCycleDuration = 0;

            lck.lock();
            if(currentState == PowerupState::ON_FIELD) {
                {
                    _state = PowerupState::OFF_FIELD;
                }
            } else if(currentState == PowerupState::OFF_FIELD){
                {
                    _state = PowerupState::ON_FIELD;
                    lck.unlock();
                    std::future<SDL_Point> ftrFreePos = std::async(&Game::GetFreePosition, game, true);//TODO make shared pointer for game
                    SDL_Point freePos = ftrFreePos.get();
                    lck.lock();
                    x = freePos.x;
                    y = freePos.y;
                }
            } else if (prevState == PowerupState::ON_FIELD && currentState == PowerupState::COLLECTED) { //It was collected in the meantime
                //Set the durations of the cycles for the durations of the poweruo
                thisCycleDuration = 10000; //TODO make variable
                currentDuration = 0;
            } else if(prevState==PowerupState::COLLECTED && currentState == PowerupState::COLLECTED) {//The time of collected state ends
                _state = PowerupState::OFF_FIELD;
                game->SetIncr(1);
            }
            lck.unlock();
        } else { //Verify if was collected in tehtime in between
            if (prevState == PowerupState::ON_FIELD && currentState == PowerupState::COLLECTED) {
                //Set the durations of the cycles for the durations of the poweruo
                thisCycleDuration = 10000; //TODO make variable
                currentDuration = 0;
            }

        }
        //TODO check if was collected
        //Lock to read condition for while
        lck.lock();
        prevState = currentState; //To keep track when the powerup is collected   
    }
    //TODO wait for this thread on game.cpps

}
