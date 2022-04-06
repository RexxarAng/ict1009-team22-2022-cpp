#include "main.h"

using namespace std;

extern Repository<Movie> movieRepository;
extern Repository<Hall> hallRepository;
extern Repository<Show> showRepository;

int main()
{
    movieRepository.load();
    hallRepository.load();
    showRepository.load();

    displayMainMenu();

    ScreenUtility::clearScreen();

    return 0;

}
