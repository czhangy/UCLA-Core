//
//  Game.h
//  proj1
//
//  Created by Charles Zhang on 1/9/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <string>
using namespace std;

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

#endif /* Game_h */
