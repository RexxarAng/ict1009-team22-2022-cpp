#include "main.h"
#include "movie_repo.h"

using namespace std;

//extern list<Movie*>movies;

void loadMovies() {
    ifstream movieCatalogFile;
    vector<string> row;
    string word, line;
    movieCatalogFile.open(MOVIE_FILE);
    if (!movieCatalogFile) {
        cout << "No movies loaded" << endl;
        pause();
    }
    else {
        cout << "Here are the movies that are showing " << endl;
        while (!movieCatalogFile.eof()) {
            row.clear();
            getline(movieCatalogFile, line);
            stringstream s(line);
            while (getline(s, word, ',')) {
                row.push_back(word);
            }
            if (row.size() == 4) {
                string movieName = row[0];
                string movieDes = row[1];
                string movieGenre = row[2];
                int movieDuration = stoi(row[3]);
                Movie* newMovie = new Movie(movieName, movieDes, movieGenre, movieDuration);
                movies.insert(movies.begin(), newMovie);
            }

            if (movieCatalogFile.eof())
                break;
        }
        for (Movie* i : movies) {
            cout << i->getTitle() << endl;
        }
        movieCatalogFile.close();
    }
}

//list<Show*> loadShows() {
//
//}

int main()
{
    //loadMovies();
    //displayMainMenu();
    Hall a(12, 6);
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
