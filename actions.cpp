#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "actions.h"
#include "movie.h"
#include "show.h"
#include "menu.h"
#include "menu_item.h"
#include "file.h"
#include "colors.h"
#include "screen_utility.h"

extern vector<Movie*>* movies;


//void viewMovies() {
//    clearScreen();
//
//    if (!movies->empty()) {
//        int movieIndex = 1;
//        cout << "Movies now showing: " << endl;
//        cout << "==============================" << endl;
//        for (Movie* i : *movies) {
//            cout << movieIndex << ") " << i->getTitle() << endl;
//            movieIndex ++;
//        }
//
//        cout << "Please select the movies by index: ";
//        unsigned int selection;
//        cin >> selection;
//        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
//        if (selection > 0 && selection <= movies->size()) {
//            cout << "You have selected " << movies->at(selection-1)->getTitle() << endl;
//            viewShowTimesByMovie(movies->at(selection-1));
//        }
//        else {
//            cout << "Invalid option, please try again." << endl;
//        }
//    }
//    else {
//        cout << "No movies currently showing" << endl;
//    }
//    pause();
//    displayMainMenu();
//}

//void viewShowTimesByMovie(Movie* movie) {
//    unsigned int selection;
//
//    while (true) {
//        clearScreen();
//        cout << movie->getTitle() << endl;
//        cout << "==============================" << endl;
//        cout << "Today " << endl;
//        cout << "1) Timeslot 1" << endl;
//        cout << "2) Timeslot 2" << endl;
//        cout << "3) Timeslot 3" << endl;
//        cout << "Please selected the option:";
//
//        cin >> selection;
//        if (!cin.fail()) break;
//        cin.clear(); // get rid of failure state
//        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        printColor("ERROR -- You did not enter an integer\n", 2);
//        pause();
//    }
//    cout << "You have selected " << selection << endl;
//
//    // TODO: Mock showtime
//    Hall a(12, 12);
//    string movieName = movie->getTitle();
//    time_t now = time(0);
//    tm localtm = *localtime(&now);
//    Show s(movieName, localtm, a);
//    viewBookingByShowTime(&s);
//}

//void viewBookingByShowTime(Show* showtime) {
//    string selection;
//
//    while (true) {
//        showtime->showHallSeatingPlan();
//
//        cout << "==============================" << endl;
//        cout << "Book any seat numbers" << endl;
//        cout << "q) Back" << endl;
//        cout << "Please selected the option:";
//
//        cin >> selection;
//        if (cin.fail()) {
//            cin.clear(); // get rid of failure state
//            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            printColor("ERROR -- Invalid option\n", 2);
//            pause();
//        }
//        else if (selection == "q") {
//            break;
//        }
//        else {
//            if (selection.size() < 2) {
//                printColor("ERROR -- Invalid seat number, please try again\n", 2);
//                pause();
//            }
//            int column = (int)(unsigned char)selection[0] - (int)('A');
//            int row = stoi(selection.substr(1, selection.size()-1));
//
//            cout << "Booking " << column << ":" << row << endl;
//            if (showtime->getHall()->bookSeat(column, row)) {
//                printColor("You have booked " + selection + "\n");
//                pause();
//            }
//            else {
//                printColor("Invalid option : " + selection + ", Please try again.\n", 2);
//                pause();
//            }
//        }
//    }
//
//}
//
void viewBookings() {
    ScreenUtility::clearScreen();
    cout << "view booking not implemented yet" << endl;
}

void viewSomething() {
    ScreenUtility::clearScreen();
    cout << "not sure what this is yet" << endl;
}

//void quit() {
//    cout << "thank you for using this movie booking system." << endl;
//}

void loadMovies() {
    ifstream movieCatalogFile;
    vector<string> row;
    string word, line;
    movieCatalogFile.open(MOVIE_FILE);
    if (!movieCatalogFile) {
        cout << "No movies loaded" << endl;
        ScreenUtility::pause();
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
                movies->insert(movies->begin(), newMovie);
            }

            if (movieCatalogFile.eof())
                break;
        }
        for (Movie* i : *movies) {
            cout << i->getTitle() << endl;
        }
        movieCatalogFile.close();
    }
}

void addMovies() {
    ifstream movieCatalogFile;
    fstream fout;
    vector<string> row;
    string line, word, movieName, currentMovieName, movieDesc, movieGenre;
    int movieDuration;
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
                    ScreenUtility::pause();
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
        cin >> movieDuration;
        while (cin.fail()) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> movieDuration;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        fout.open(MOVIE_FILE, ios::app);
        fout << movieName << ", "
            << movieDesc << ", "
            << movieGenre << ", "
            << movieDuration << "\n";
        Movie* newMovie = new Movie(movieName, movieDesc, movieGenre, movieDuration);
        movies->insert(movies->begin(), newMovie);
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

void addHalls() {
    ScreenUtility::clearScreen();
}

void addShows() {
    ScreenUtility::clearScreen();
}

//void pause() {
//    cout << endl << "Press <Enter> to continue...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
////    cin.get();
//}