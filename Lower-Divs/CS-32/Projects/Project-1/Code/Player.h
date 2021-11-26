//
//  Player.h
//  proj1
//
//  Created by Charles Zhang on 1/9/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>
using namespace std;

class Arena;

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonVial();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* Player_h */
