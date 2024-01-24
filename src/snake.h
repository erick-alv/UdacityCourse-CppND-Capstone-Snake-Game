#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <mutex>
#include "renderable.h"
#include "SDL.h"

class Snake: public Renderable {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  int GetLives();
  void IncreaseLives();

  void RenderObject(SDL_Renderer *sdl_renderer, SDL_Rect &block);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int lives{1};
  bool justLostLive{false};
  std::mutex _mutex;
};

#endif