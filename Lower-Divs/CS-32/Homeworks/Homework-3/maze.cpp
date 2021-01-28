//
//  maze.cpp
//  hw3
//
//  Created by Charles Zhang on 2/7/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <string>
#include <cassert>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) return true; // if starting location is equal to ending location
    maze[sr][sc] = 'X'; // mark current location as visited
    if (maze[sr - 1][sc] != 'X' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) return true; // check up
    if (maze[sr][sc + 1] != 'X' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) return true; // check right
    if (maze[sr + 1][sc] != 'X' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) return true; // check down
    if (maze[sr][sc - 1] != 'X' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) return true; // check left
    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X.XXX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };

    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "pathExists() tests:" << endl;
    assert(pathExists(maze, 10, 10, 4, 3, 1, 8));
    cerr << "pathExists returns correctly when a path is found" << endl;
    assert(!pathExists(maze, 10, 10, 4, 3, 1, 1));
    cerr << "pathExists returns correctly when no path is found" << endl;
    cerr << "----------------------------------------" << endl;
    cerr << "----------------------------------------" << endl;

    cerr << endl;
    cerr << "***********************" << endl << "ALL MAZE TESTS PASSED" << endl << "***********************" << endl;
}

