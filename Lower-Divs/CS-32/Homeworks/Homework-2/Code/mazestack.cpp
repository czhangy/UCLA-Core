////
////  mazestack.cpp
////  hw2
////
////  Created by Charles Zhang on 2/1/20.
////  Copyright © 2020 Charles Zhang. All rights reserved.
////
//
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

class Coord {
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> path;
    path.push(Coord(sr, sc));
    maze[sr][sc] = 'X';
    while(!path.empty()) {
        Coord test = path.top();
        path.pop();
        if (test.r() == er && test.c() == ec) {
            return true;
        }
        if (maze[test.r()][test.c() + 1] != 'X') { // check east
            path.push(Coord(test.r(), test.c() + 1));
            maze[test.r()][test.c() + 1] = 'X';
        }
        if (maze[test.r() + 1][test.c()] != 'X') { // check south
            path.push(Coord(test.r() + 1, test.c()));
            maze[test.r() + 1][test.c()] = 'X';
        }
        if (maze[test.r()][test.c() - 1] != 'X') { // check west
            path.push(Coord(test.r(), test.c() - 1));
            maze[test.r()][test.c() - 1] = 'X';
        }
        if (maze[test.r() - 1][test.c()] != 'X') { // check north
            path.push(Coord(test.r() - 1, test.c()));
            maze[test.r() - 1][test.c()] = 'X';
        }
    }
    return false;
}

int main()
{
    string maze1[10] = {
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

    assert(!pathExists(maze1, 10, 10, 4, 3, 1, 2));

    string maze2[10] = {
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

    assert(pathExists(maze2, 10,10, 4,3, 1,8));

    cout << "All mazeStack tests passed" << endl;
}
