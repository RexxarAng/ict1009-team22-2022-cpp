#include "colors.h"

#ifdef _WIN32     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#include <windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void printColor(string text, int style) {
    if (style == 0) SetConsoleTextAttribute(hConsole, 7);
    else if (style == 1) SetConsoleTextAttribute(hConsole, 10);
    else if (style == 2) SetConsoleTextAttribute(hConsole, 12);
    else if (style == -1) SetConsoleTextAttribute(hConsole, 8);
    cout << text;
    SetConsoleTextAttribute(hConsole, 7);
}
#elif __unix__
void printColor(string text, int style) {
    cout << text;
}
cout << "unix";
#else
void printColor(string text, int style) {
    int font_style = 21;
    int font_color = 39;
    if (style == -1) {
        font_style = 0;
        font_color = 37;
    }
    else if (style == 1) {
        font_style = 1;
        font_color = 32;
    }
    else if (style == 2) {
        font_style = 1;
        font_color = 31;
    }
    cout << "\033[" << font_style << ";" << font_color << "m";
    cout << text;
    cout << "\033[0m";
}
#endif
