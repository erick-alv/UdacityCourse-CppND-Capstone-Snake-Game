#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <thread>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "doubleScore.h"
#include "extraLive.h"
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
  void IncreaseLives();
  

 private:
  std::shared_ptr<Snake> snake;
  std::shared_ptr<Food> food;
  std::vector<std::shared_ptr<Renderable>> objectsToRender;
  std::shared_ptr<DoubleScore> doubleScrPowerup;
  std::shared_ptr<ExtraLive> livePowerup;
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