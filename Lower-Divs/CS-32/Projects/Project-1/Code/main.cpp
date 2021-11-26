// vampires.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "Game.h"
#include "Vampire.h"
#include "Player.h"
#include "Arena.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
//       Use this instead to create a mini-game:
    Game g(3, 5, 2);
//    Game g(10, 12, 40);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

//#ifdef _MSC_VER  //  Microsoft Visual C++
//
//#pragma warning(disable : 4005)
//#include <windows.h>
//
//void clearScreen()
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    GetConsoleScreenBufferInfo(hConsole, &csbi);
//    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
//    COORD upperLeft = { 0, 0 };
//    DWORD dwCharsWritten;
//    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
//                                                        &dwCharsWritten);
//    SetConsoleCursorPosition(hConsole, upperLeft);
//}
//
//#else  // not Microsoft Visual C++, so assume UNIX interface
//
//#include <iostream>
//#include <cstring>
//#include <cstdlib>
//
//void clearScreen()  // will just write a newline in an Xcode output window
//{
//    static const char* term = getenv("TERM");
//    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
//        cout << endl;
//    else
//    {
//        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
//        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
//    }
//}
//
//#endif
