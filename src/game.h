#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "powerup.h"
#include "renderable.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void SetIncr(int value);
  SDL_Point GetFreePosition(bool checkAlsoFood);
  

 private:
  Snake snake;
  Food food;
  std::vector<Renderable*> objectsToRender;
  Powerup powerup;
  int incr{1};
  int score{0};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::mutex _mutex;

  void PlaceFood();
  void Update();
  void IncreaseScore();
};

#endif