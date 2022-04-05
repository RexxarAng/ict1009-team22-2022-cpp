#include "main.h"

using namespace std;

extern Repository<Movie> movieRepository;

int main()
{
    movieRepository.load();
    movieRepository.save(); // testing save function

// TODO: To be removed
//    loadMovies();
    displayMainMenu();
    ScreenUtility::clearScreen();
    Hall a(12, 12);
    string movieName = "Venom";
    time_t now = time(0);
    tm localtm = *localtime(&now);
    Show s(movieName, localtm, a);
    //a.bookSeat(2, 4);
    //a.bookSeat(2, 5);

    //a.bookSeat(3, 1);
    //a.bookSeat(3, 2);

    s.showHallSeatingPlan();

    ScreenUtility::clearScreen();

    return 0;

}
