#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoreFileHandler.h"


const std::string scoresFileName = "scores.txt";

void readPlayerName(std::string &name, ScoreFileHandler &scoreFile) {
  bool name_chosen = false;
  while(!name_chosen) {
    std::cout << "Please enter your name: ";
    std::cin >> name;
    if(scoreFile.nameIsSaved(name)) {
      std::cout << "The name " << name << " already exists. Do you want to continue with this name?\n";
      std::string answer;
      bool valid_answer = false;
      while(!valid_answer) {
        std::cout << "Please answer yes or no: ";
        std::cin >> answer;
        if(answer == "yes" || answer == "no"){
          valid_answer = true;
          if(answer == "yes") {
            name_chosen = true;
          }
        }
      }
    } else {
      name_chosen = true;
    }
  }
}

int main() {
  //Read/Create scores file and read user input for name
  ScoreFileHandler scoreFile(scoresFileName);  
  std::string playerName;
  readPlayerName(playerName, scoreFile);


  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  //write score to file
  scoreFile.writeFinalScore(playerName, game.GetScore());
  return 0;
}