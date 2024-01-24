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

# Student notes for submission

## Instructions
* Once the game starts the player must provide a name in order to store the score. If the name already exists, the player must confirm with 'yes' or 'no' that the name belongs to the player. If the player answers 'no', then a new name must be provided.
* Once the game starts you can collect 3 types of items which are represented as squares of different color:
  * The yellow squares are food. You increase the score by 1 each time that you collect one.
  * The turquoise squares are a special powerup. Once you collect this powerup, every time that you collect a food item you increase the score by 2. The effect of the powerup has a determined duration. This item appears during an interval of time and it has a cooldown time before appearing again.
  * The green squares are additional lives. You gain an additional live each time that you collect this one. This item also appears during an interval of time and it has a cooldown time before appearing again.
* Each time that the snake intersects with itself you loose a live. Once you reach 0 lives, the game stops. At the top of the window there is an indicator of the number of lives.


## Additional features
* **Storing scores:** This game saves the scores of the players in a file named 'scores.txt'. In this file we save the name of the player, the last achieved score and the best scored with comma separated format. Each line saves the information for each player. In order to identify a player, the user must insert a name at the beginning. Furthermore, we verify if the name already exists in the file to avoid duplicates. If the name already exists, the player can choose to continue with that name or a new one.

* **Addition of powerups:** We add two additional types of items that can be collected and work as powerup for the games. One is an item that provides an additional live and the other an item that duplicates the number of score points obtained when collecting food. In our implementation these items do not show permanently. Therefore, we create additional threads that change the state of these items between visible(collectable) and not visible(not collectable). The duration of the effect of the item that duplicates the score is also controlled by a thread. See the class Powerup for details.

* **Virtual methods and derived classes:** In order to facilitate the extension of the game with new objects, we create the class Renderable with a virtual function. The derived classes must implement this method in order to render an object on the game. With this and a modification in the Renderer class, it is easy to include new objects in the scene. We also create a Powerup class that implements the logic of items that can be collected and handles the creation of threads. This helps us to define the additional items for the game.

## Addressed rubric points

* With respect to Loops, Functions, I/O:
  * For storing the scores, we read and write to a file.
  * We read the name of the user with the console input. Here we also process the information of the file to verify the existence of the name. By doing this we also process the user input.
  * Overall we structure our code in different functions and use multiple control structures.
  * We use different structures, like vectors, to store game objects and immutable variables, like the name of the scores file and the duration of the cycles of the threads.
* With respect to Object Oriented Programming:
  * We create additional classes with the corresponding access specifiers. These classes are Powerup and the derived classes ExtraLive and DoubleScore.
  * We make use of virtual functions and override them. See classes Renderable, Powerup and the corresponding derived classes.
  * We use initialization lists when possible in our classes.
* With respect to Memory Management:
  * The project uses RAII concept and scope. For reading the file we have the class ScoreFileHandler to handle the fstream to the file as a resource that is opened in the constructor and closed on the destructor. In the class Powerup we handle the threads as resource in a similar way.
  * We follow the rule of 5 in the classes that we implemented.
  * We use smart pointers, in specific for the members of Games class
  * We use references in functions definitions when necessary.
* With respect to Concurrency:
  * In the class Powerup we use threads and async tasks.
  * We use mutex and lock to protect data of the classes Powerup, Game and Snake.


