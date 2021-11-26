//
//  History.hpp
//  proj1
//
//  Created by Charles Zhang on 1/9/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"
using namespace std;

class History {
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_value[MAXROWS][MAXCOLS];
};

#endif /* History_h */
