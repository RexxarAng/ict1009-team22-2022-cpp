#include "main.h"
#include "actions.h"

using namespace std;

int main()
{
    Repository<Movie> newMovieRepository("movieCatalog.csv");
    newMovieRepository.load();
    newMovieRepository.save();

    loadMovies();
    displayMainMenu();
    clearScreen();
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

    pause();

    return 0;

}
