#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <list>
#include "movie.h"
#include "menu.h"
#include "menu_item.h"
#include "file.h"

extern list<Movie*> movies; //a list of loaded movies

using namespace std;
void loadMovies() {
    cout << "DEBUG: opening loadMovies()" << endl;
    ifstream movieCatalogFile;
    vector<string> row;
    string word, line;
    string fileOpenError = "File failed to open.";
    try{
        movieCatalogFile.open(MOVIE_FILE);
        if (movieCatalogFile.fail()) throw (fileOpenError);
    }
    catch(string fileOpenError){
        cout << "ERROR: " << fileOpenError << endl;
        cout << "No movies loaded" << endl;
        pause();
    }
    cout << "DEBUG: loadMovies suceeded" << endl;
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
    pause();
    displayMainMenu();
}

void viewBookings() {
    system("cls");
    cout << "View Booking not implemented yet" << endl;
}

void viewSomething() {
    system("cls");
    cout << "What's the movie ID?" << endl;
    int movieID;
    cin >> movieID;
    for (Movie* i : movies) {
        if (i->getmovieID() == movieID) {
            Movie selectedMovie = *i;
            cout << "Which time slots do you want?" << endl << endl;
            cout << "Available time slots:" << endl;
            list<Show>::iterator it;
            tm currentDate;
            for (it = selectedMovie.getShows().begin(); it != selectedMovie.getShows().end(); it++) {
                //unsure if I'm making a shallow or deep copy here
                currentDate = it->getDate();
                mktime(&currentDate);
                cout << asctime(&currentDate) << "-" << "calc end of movie here" << endl; //mktime converts tm to time_t
            }
            cin >> 
        }
    }
    
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


