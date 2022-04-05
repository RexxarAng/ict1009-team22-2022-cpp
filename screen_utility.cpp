#include "screen_utility.h"

void ScreenUtility::clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ScreenUtility::quit() {
	cout << "Thank you for using this movie booking system." << endl;
}

void ScreenUtility::pause() {
	cout << endl << "Press <Enter> to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}