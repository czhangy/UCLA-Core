//
//  History.cpp
//  proj1
//
//  Created by Charles Zhang on 1/9/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>

History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_value[i][j] = 0;
        }
    }
}

bool History::record(int r, int c) {
    if (r < 1 || r > m_rows || c < 1 || c > m_cols) {
        return false;
    }
    m_value[r - 1][c - 1]++;
    return true;
}

void History::display() const {
    char displayGrid[MAXROWS][MAXCOLS];
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (m_value[i][j] == 0) {
                displayGrid[i][j] = '.';
            } else if (m_value[i][j] < 26) {
                displayGrid[i][j] = 'Z' - (26 - m_value[i][j]); // conversion from number to desired letter
            } else {
                displayGrid[i][j] = 'Z';
            }
        }
    }
    clearScreen();
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << displayGrid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// ask about <stdio.h>
// ask about the class prototypes in other files
// ask about why namespace std gives a warning
