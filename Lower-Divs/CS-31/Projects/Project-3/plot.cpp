//
//  main.cpp
//  plot
//
//  Created by Charles Zhang on 10/22/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

#include "grid.h"
#include <cctype>
#include <cassert>
#include <iostream>

using namespace std;

// Global Variables
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;

// plotLine
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
bool drawHorizontal(int r, int c, int distance, char ch, int fgbg);
bool drawVertical(int r, int c, int distance, char ch, int fgbg);

// Commands
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
int lineDrawing (string commandString, int& i, int dir, int& badPos, int& currentRow, int& currentColumn, char plotChar, int mode);

// Warm Up Functions
void plotHorizontalLine(int r, int c, int distance, char ch);
void plotVerticalLine(int r, int c, int distance, char ch);
void plotRectangle(int r, int c, int height, int width, char ch);

int main() {
    setSize(20, 30);
    clearGrid();
    char currentChar = '*';
    int currentMode = FG;
    for (;;) {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "") {
            break;
        }
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status) {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position + 1 << endl;
                break;
            case 2:
                cout << "Cannot perform command at position " << position + 1 << endl;
                break;
            default: // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
        }
    }
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
    if (r <= 0 || r > getRows() || c <= 0 || c > getCols() || (dir != 0 && dir != 1) || (fgbg != 0 && fgbg != 1) || (! isprint(plotChar))) {
        return false;
    }
    if (dir == HORIZ) {
        return drawHorizontal(r, c, distance, plotChar, fgbg);
    } else {
        return drawVertical(r, c, distance, plotChar, fgbg);
    }
}

bool drawHorizontal(int r, int c, int distance, char ch, int fgbg) {
    if (c + distance > getCols() || c + distance < 1) { // checks if drawing is in bounds
        return false;
    }
    if (distance < 0) {
        if (fgbg == 0) {
            for (int i = 0; i >= distance; i--) {
                setChar(r, c + i, ch);
            }
        } else {
            for (int i = 0; i >= distance; i--) {
                if (getChar(r, c + i) == ' ') {
                    setChar(r, c + i, ch);
                }
            }
        }
    } else {
        if (fgbg == 0) {
            for (int i = 0; i <= distance; i++) {
                setChar(r, c + i, ch);
            }
        } else {
            for (int i = 0; i <= distance; i++) {
                if (getChar(r, c + i) == ' ') {
                    setChar(r, c + i, ch);
                }
            }
        }
    }
    return true;
}

bool drawVertical(int r, int c, int distance, char ch, int fgbg) {
    if (r + distance > getRows() || r + distance < 0) {
        return false;
    }
    if (distance < 0) {
        if (fgbg == 0) {
            for (int i = 0; i >= distance; i--) {
                setChar(r + i, c, ch);
            }
        } else {
            for (int i = 0; i >= distance; i--) {
                if (getChar(r + i, c) == ' ') { // checks for spaces
                    setChar(r + i, c, ch);
                }
            }
        }
    } else {
        if (fgbg == 0) {
            for (int i = 0; i <= distance; i++) {
                setChar(r + i, c, ch);
            }
        } else {
            for (int i = 0; i <= distance; i++) {
                if (getChar(r + i, c) == ' ') { // checks for spaces
                    setChar(r + i, c, ch);
                }
            }
        }
    }
    return true;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    int currentRow = 1; // resets to (1,1)
    int currentColumn = 1;
    for (int i = 0; i < commandString.size(); i++) {
        if (commandString[i] == 'H' || commandString[i] == 'h') {
            if (! (lineDrawing(commandString, i, HORIZ, badPos, currentRow, currentColumn, plotChar, mode) == 0)) {
                return lineDrawing(commandString, i, HORIZ, badPos, currentRow, currentColumn, plotChar, mode);
            }
        } else if (commandString[i] == 'V' || commandString[i] == 'v') {
            if (! (lineDrawing(commandString, i, VERT, badPos, currentRow, currentColumn, plotChar, mode) == 0)) {
                return lineDrawing(commandString, i, VERT, badPos, currentRow, currentColumn, plotChar, mode);
            }
        } else if (commandString[i] == 'F' || commandString[i] == 'f') {
            if ((! isprint(commandString[i + 1])) || (i + 1 == commandString.size() - 1)) { // checks if character following F is print and it exists
                badPos = i + 1;
                return 1;
            } else {
                mode = FG;
                plotChar = commandString[i + 1]; // sets new character
                i += 1; // adjusts i to account for the character
            }
        } else if (commandString[i] == 'B' || commandString[i] == 'b') {
            if ((! isprint(commandString[i + 1])) || (i + 1 == commandString.size() - 1)) { // checks if character following B is print and it exists
                badPos = i + 1;
                return 1;
            } else {
                mode = BG;
                plotChar = commandString[i + 1]; // sets new character
                i += 1; // adjusts i to account for the character
            }
        } else if (commandString[i] == 'C' || commandString[i] == 'c') {
            clearGrid();
            plotChar = '*';
            mode = FG;
        } else {
            badPos = i;
            return 1; // if not one of given characters, throw syntax error
        }
    }
    return 0; // draws
}

int lineDrawing(string commandString, int& i, int dir, int& badPos, int& currentRow, int& currentColumn, char plotChar, int mode) {
    string command = "";
    bool isNeg = false;
    if (commandString[i + 1] == '-') { // checks for negative
        isNeg = true;
        i++; // shifts position 1 over to search for digits
    }
    for (int j = i + 1; j < i + 3 && j < commandString.size(); j++) { // checks the next 2 characters
        if (isdigit(commandString[j])) {
            command += commandString[j]; // adds any digits to the command string
        } else {
            break; // exits loop if digit not found
        }
    }
    if (command.size() == 0) { // checks if any digits followed the h/v
        badPos = i + 1; // adjusts position to account for syntax error location
        return 1;
    }
    int d = stoi(command);
    if (isNeg) { // sets negative
        d *= -1;
    }
    if (plotLine(currentRow, currentColumn, d, dir, plotChar, mode) == false) { // checks if the line was drawn within the grid
        if (isNeg) {
            badPos = i - 1; // readjusts error message for negative inputs
        } else {
            badPos = i;
        }
        return 2;
    } else {
        i += command.size(); // adjusts position in string
        if (dir == HORIZ) { // adjusts position on grid
            currentColumn += d;
        } else {
            currentRow += d;
        }
    }
    return 0;
}

// Warm Ups
void plotHorizontalLine(int r, int c, int distance, char ch) {
    if (distance < 0) {
        return;
    }
    for (int i = 0; i <= distance; i++) {
        if (c + i > getCols() ) {
            return;
        } else if (c + i > 0 && r + i > 0) {
                setChar(r, c + i, ch);
        }
    }
}

void plotVerticalLine(int r, int c, int distance, char ch) {
    if (distance < 0) {
        return;
    }
    for (int i = 0; i <= distance; i++) {
        if (r + i > getRows()) {
            return;
        } else {
            if (c + i > 0 && r + i > 0) {
                setChar(r + i, c, ch);
            }
        }
    }
}

void plotRectangle(int r, int c, int height, int width, char ch) {
    if (height < 0 || width < 0) {
        return;
    } else {
        plotVerticalLine(r, c, height, ch);
        plotHorizontalLine(r, c, width, ch);
        plotVerticalLine(r, c + width - 1, height, ch);
        plotHorizontalLine(r + height - 1, c, width, ch);
    }
}

// cb h1v1f#h2h-2v4v-2h1h-1v-2h2b h2f#v4h2v-4b h2f#v4h2h-2v-4h2b h2f#v4v-2h1b h1v-1f#v-1v1b v2f#v1b v2h-14f#h1v4v-4h1b h2f#v4v-2h2v2v-4b h2f#h1v4h-1h2h-1v-4h1b h2f#h2h-2v2h2v2h-2b v2h-12f#v4h2h-2v-4h2b h2f#v4h2h-2v-4b h4f#v4v-4h2v4v-2h-1h1v-2b h2f#v2h2v2h-2h2v-2h-2v-2h2b h2f#v2h2v2h-2h2v-2h-2v-2h2
