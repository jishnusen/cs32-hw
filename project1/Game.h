#ifndef GAME_H_
#define GAME_H_

#include "globals.h"

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};

#endif