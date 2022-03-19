#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include "movie.h"
#include "menu.h"
#include "menu_item.h"
#include "file.h"

extern list<Movie*> movies;

void viewMovies() {
    system("cls");

    if (movies.size() > 0) {
        cout << "Movies now showing: " << endl;
        for (Movie* i : movies) {
            cout << i->getTitle() << endl;
        }
    }
    else {
        cout << "No movies currently showing" << endl;
    }  
}

void viewBookings() {
    system("cls");
    cout << "View Booking not implemented yet" << endl;
}

void viewSomething() {
    system("cls");
    cout << "Not sure what this is yet" << endl;
}

void quit() {
    cout << "Thank you for using this movie booking system." << endl;
}

void addMovies() {
    ifstream movieCatalogFile;
    fstream fout;
    vector<string> row;
    string line, word, movieName, currentMovieName, movieDesc, movieGenre, movieDuration;
    movieCatalogFile.open(MOVIE_FILE);
    cout << "Adding Movies..." << endl;
    bool cont = true;
    while (cont) {
        cout << "Movie Name: ";
        getline(cin, movieName);
        if (movieCatalogFile) {
            while (!movieCatalogFile.eof()) {
                row.clear();
                getline(movieCatalogFile, line);
                stringstream s(line);

                while (getline(s, word, ',')) {
                    row.push_back(word);
                }
                currentMovieName = row[0];
                if (movieName == currentMovieName) {
                    cout << "Movie already exists" << endl;
                    pause();
                    addMovies();
                }
                if (movieCatalogFile.eof())
                    break;
            }
        }

        cout << "Movie Description: ";
        getline(cin, movieDesc);
        cout << "Movie Genre: ";
        getline(cin, movieGenre);
        cout << "Movie Duration(in mins): ";
        getline(cin, movieDuration);
        fout.open(MOVIE_FILE, ios::app);
        fout << movieName << ", "
            << movieDesc << ", "
            << movieGenre << ", "
            << movieDuration << "\n";
        string input;
        cout << "Do you still want to add more movies(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (input[0] != 'Y')
            cont = false;
    }

    fout.close();
    movieCatalogFile.close();
    displayAdminMenu();
}

void addShows() {
    system("cls");

}

void pause() {
    cout << endl << "Press <Enter> to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}