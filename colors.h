#pragma once
#pragma warning(disable : 4067)

#include <iostream>
#include <string>
using namespace std;

#ifdef _WIN32
/* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#include <windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void printColor(string text, int style = 0) {
    if (style == 0) SetConsoleTextAttribute(hConsole, 7);
    else if (style == 1) SetConsoleTextAttribute(hConsole, 10);
    else if (style == 2) SetConsoleTextAttribute(hConsole, 12);
    else if (style == -1) SetConsoleTextAttribute(hConsole, 8);
    cout << text;
    SetConsoleTextAttribute(hConsole, 7);
}
#elif __unix__
void printColor(string text, int style = 1) {
    cout << text;
}
cout << "unix";
#else
void printColor(string text, int style = 1) {
    cout << text;
}
#endif
