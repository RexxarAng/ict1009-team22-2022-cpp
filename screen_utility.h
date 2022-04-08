#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;

class ScreenUtility {
public:
	static void clearScreen();

	static void quit();

	static void pause();

	static string promptAndSanitizeInput(string);
};


