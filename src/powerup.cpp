#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <algorithm>
#include <thread>
#include <future>
#include "powerup.h"
#include "game.h"


const int powerupDuration = 6000;
const int minCycleDuration = 6000;
const int maxCycleDuration = 8000;

Powerup::Powerup(Game* g): game(g) {}

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

Powerup::Powerup(Powerup&& other){
    std::unique_lock<std::mutex> lck(other._mutex);
    x = other.x;
    y = other.y;
    game = other.game;
    threads = std::move(other.threads);
    _state = other._state;
    _runThread = other._runThread;
    //Cannot move mutex   

    other.game = nullptr;
}

Powerup& Powerup::operator=(Powerup&& other) {
    if(this == &other) {
        return *this;
    }
    //stop threads of this
    std::unique_lock<std::mutex> lck(_mutex);
    _runThread = false;
    lck.unlock();
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });

    std::unique_lock<std::mutex> lck_other(other._mutex);
    x = other.x;
    y = other.y;
    game = other.game;
    threads = std::move(other.threads);
    _state = other._state;
    _runThread = other._runThread;
    //Cannot move mutex   

    other.game = nullptr;

    return *this;
}

void Powerup::CheckCollection(int snake_x, int snake_y){
    std::lock_guard<std::mutex> lg(_mutex);
    PowerupState currentState = _state;
    if(currentState == PowerupState::ON_FIELD && x == snake_x && y == snake_y) {
        CollectedActionStart();
        _state = PowerupState::COLLECTED;
    }
}

void Powerup::ToggleState() {
    double thisCycleDuration = 0;
    double currentDuration = 0;
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    //variables for random generation
    std::uniform_int_distribution<long> distr(minCycleDuration, maxCycleDuration);
    std::random_device rd;
    std::mt19937 engine = std::mt19937(rd());
    
    lastUpdate = std::chrono::system_clock::now();
    std::unique_lock<std::mutex> lck(_mutex);//Lock to read condition for while
    PowerupState prevState = _state;
    while (_runThread)
    {
        lck.unlock();//Unlock for the rest
        
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
                    std::future<SDL_Point> ftrFreePos = std::async(&Game::GetFreePosition, game, true);
                    SDL_Point freePos = ftrFreePos.get();
                    lck.lock();
                    x = freePos.x;
                    y = freePos.y;
                }
            } else if (prevState == PowerupState::ON_FIELD && currentState == PowerupState::COLLECTED) { //It was collected in the meantime
                //Set the durations of the cycles for the durations of the poweruo
                thisCycleDuration = powerupDuration;
                currentDuration = 0;
            } else if(prevState==PowerupState::COLLECTED && currentState == PowerupState::COLLECTED) {//The time of collected state ends
                _state = PowerupState::OFF_FIELD;
                CollectedActionFinish();
            }
            lck.unlock();
        } else { //Verify if was collected in the time in between
            if (prevState == PowerupState::ON_FIELD && currentState == PowerupState::COLLECTED) {
                //Set the durations of the cycles for the durations of the poweruo
                thisCycleDuration = powerupDuration;
                currentDuration = 0;
            }
        }
        //Lock to read condition for while
        lck.lock();
        prevState = currentState; //To keep track when the powerup is collected   
    }

}
