#include "main.h"
using namespace std;

extern list<Movie*>movies;



//list<Show*> loadShows() {
//
//}

int main(){
    loadMovies();
    displayMainMenu();
    Hall a(12, 6);
    string movieName = "Venom";
    time_t now = time(0);
    tm localtm = *localtime(&now);
    int id = 1;
    Show s(id, localtm, a);
    //a.bookSeat(2, 4);
    //a.bookSeat(2, 5);

    //a.bookSeat(3, 1);
    //a.bookSeat(3, 2);

//  s.showHallSeatingPlan();

    pause();

    return 0;

}
