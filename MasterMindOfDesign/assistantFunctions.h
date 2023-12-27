#ifndef ASSISTANTFUNCTION_H
#define ASSISTANTFUNCTION_H

#include <iostream>
#include<windows.h>
#include<conio.h>
#include<string>
using namespace std;

// assistant functions

// colors text
void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

//moves the console cursor to (x,y) position
void gotoXY(short x, short y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// get the current cursor position coordinates
COORD GetConsoleCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

// clears part of screen from start row number until end row number
void partialScreenClear(int startrow, int endrow = 0) {
    string x = "";
    for (int i = 0; i < endrow; i++)
    {
        x += "                                                                                                                       \n";
    }
    gotoXY(0,startrow);
    cout << x;
    gotoXY(0, startrow);

}

// hide the windows cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}



#endif 






