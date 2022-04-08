#include "screen_utility.h"
#include <string>

void ScreenUtility::clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ScreenUtility::quit() {
	cout << "Thank you for using this movie booking system." << endl;
	pause();
	exit(0);
}

void ScreenUtility::pause() {
	cout << endl << "Press <Enter> to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string ScreenUtility::promptAndSanitizeInput(string message) {
    cout << message;
    string input;
    while (getline(cin, input))
    {
        if (input.empty()) {
            cout << "Empty input" << endl;
            cout << message;
        }
        else {
            input.erase(remove(input.begin(), input.end(), '"'));
            input.erase(remove(input.begin(), input.end(), ';'));
            return input;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
}