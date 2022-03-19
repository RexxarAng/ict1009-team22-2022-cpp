#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include "menu.h"
#include "movie.h"
#include "main.h"
#include "file.h"

using namespace std;

extern list<Movie*>movies;

list<Movie*> loadMovies() {
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

        return movies;
    }
}

int main()
{
    loadMovies();
    displayMainMenu();

    return 0;

}
