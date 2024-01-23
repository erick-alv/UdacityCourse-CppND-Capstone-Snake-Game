# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

# Added Features and Satisfied criteria
* **Storing scores:** This game saves the scores of the players in a file named 'scores.txt'. In this file we save the name of the player, the last achieved score and the best scored with comma separated format. Each line saves the information for each player. In order to identify a player, the user must insert a name at the beginning. Furthermore, we verify if the name already exists in the file to avoid duplicates. If the name already exists, the player can choose to continue with that name.
**Satisfied criteria:** With these aspects we read and process user input and read and write to files. This fulfills 2 aspects of the "Loops, Functions, I/O" section. Moreove we wrote a class to handle the file as a resource that is opened in the constructor and closed in the destructor. This uses RAII.

* **Addition of abstracts classes**: In order to facilitate the extension of the game with new objects, we create additional abstract classes. One of this is the Renderable class that has a method to a object. With this we can esily extend the game with new objet that must be renderd on screen.
**Satisfied criteria:** This fulfills an aspect of the "Object Oriented Programming" section.

* **Other satisified criteria:** 
  * Overall we structure our code in different functions and use multiple control structures. This fulfills another criterium of the "Loops, Functions, I/O" section.
  * We use different structures, like vectors, to store game objects and immutable variables, like the name of the scores file. This fulfills another criterium of the "Loops, Functions, I/O" section.


# Game Instructions
* Once the game starts the player must provide a name in order to store the score. This can be either a new name or an existent name.
