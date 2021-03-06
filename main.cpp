#include "main.h"

using namespace std;

extern Repository<Movie> movieRepository;
extern Repository<Hall> hallRepository;
extern Repository<Show> showRepository;

int main()
{
    try {
        movieRepository.load();
        hallRepository.load();
        showRepository.load();
    }
    catch (ParseException& e) {
        printColor("Error: ", 2);
        cout << e.what() << endl;
        ScreenUtility::pause();
    }
    catch (exception& e) {
        cout << "No records loaded" << endl;
        ScreenUtility::pause();
    }

    Menu::displayMainMenu();

    ScreenUtility::clearScreen();

    return 0;

}
