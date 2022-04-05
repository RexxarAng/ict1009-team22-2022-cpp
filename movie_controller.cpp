#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "movie_controller.h"
#include "menu.h"
#include "file.h"
#include "repository.h"

extern Repository<Movie> movieRepository;

void MovieController::viewMovies() {
    extern vector<Movie*>* movies;
    ScreenUtility::clearScreen();
    if (!movies->empty()) {
        int movieIndex = 1;
        cout << "Movies now showing: " << endl;
        cout << "==============================" << endl;
        for (Movie* i : *movies) {
            cout << movieIndex << ") " << i->getTitle() << endl;
            movieIndex++;
        }

        cout << "Please select the movies by index: ";
        unsigned int selection;
        cin >> selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
        if (selection > 0 && selection <= movies->size()) {
            cout << "You have selected " << movies->at(selection - 1)->getTitle() << endl;
            viewShowTimesByMovie(movies->at(selection - 1));
        }
        else {
            cout << "Invalid option, please try again." << endl;
        }
    }
    else {
        cout << "No movies currently showing" << endl;
    }
    ScreenUtility::pause();
    displayMainMenu();
}

void MovieController::viewShowTimesByMovie(Movie* movie) {
    unsigned int selection;

    while (true) {
        ScreenUtility::clearScreen();
        cout << movie->getTitle() << endl;
        cout << "==============================" << endl;
        cout << "Today " << endl;
        cout << "1) Timeslot 1" << endl;
        cout << "2) Timeslot 2" << endl;
        cout << "3) Timeslot 3" << endl;
        cout << "Please selected the option:";

        cin >> selection;
        if (!cin.fail()) break;
        cin.clear(); // get rid of failure state
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printColor("ERROR -- You did not enter an integer\n", 2);
        ScreenUtility::pause();
    }
    cout << "You have selected " << selection << endl;

    // TODO: Mock showtime
    Hall a(12, 12);
    string movieName = movie->getTitle();
    time_t now = time(0);
    tm localtm = *localtime(&now);
    Show s(movieName, "0800 hrs", a);
    viewBookingByShowTime(&s);
}

void MovieController::viewBookingByShowTime(Show* showtime) {
    string selection;

    while (true) {
        showtime->showHallSeatingPlan();

        cout << "==============================" << endl;
        cout << "Book any seat numbers" << endl;
        cout << "q) Back" << endl;
        cout << "Please selected the option:";

        cin >> selection;
        if (cin.fail()) {
            cin.clear(); // get rid of failure state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printColor("ERROR -- Invalid option\n", 2);
            ScreenUtility::pause();
        }
        else if (selection == "q") {
            break;
        }
        else {
            if (selection.size() < 2) {
                printColor("ERROR -- Invalid seat number, please try again\n", 2);
                ScreenUtility::pause();
            }
            int column = (int)(unsigned char)selection[0] - (int)('A');
            int row = stoi(selection.substr(1, selection.size() - 1));

            cout << "Booking " << column << ":" << row << endl;
            if (showtime->getHall()->bookSeat(column, row)) {
                printColor("You have booked " + selection + "\n");
                ScreenUtility::pause();
            }
            else {
                printColor("Invalid option : " + selection + ", Please try again.\n", 2);
                ScreenUtility::pause();
            }
        }
    }
}


void MovieController::addMovies() {
    extern vector<Movie*>* movies;
    vector<string> row;
    string line, word, movieName, currentMovieName, movieDesc, movieGenre;
    int movieDuration;
    cout << "Adding Movies..." << endl;
    bool cont = true;
    while (cont) {
        cout << "Movie Name: ";
        getline(cin, movieName);
        for (Movie* i : *movies) {
            if (movieName == i->getTitle()) {
                cout << "Movie already exists";
                ScreenUtility::pause();
                addMovies();
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
        Movie* newMovie = new Movie(movieName, movieDesc, movieGenre, movieDuration);
        movies->insert(movies->end(), newMovie);
        string input;
        cout << "Do you still want to add more movies(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(input[0]) != 'Y')
            cont = false;
    }
    movieRepository.save();
    displayAdminMenu();
}

void MovieController::displayMovieList() {
    extern vector<Movie*>* movies;
    if (!movies->empty()) {
        int movieIndex = 1;
        cout << "Movies now showing: " << endl;
        cout << "==============================" << endl;
        for (Movie* i : *movies) {
            cout << movieIndex << ") " << i->getTitle() << endl;
            movieIndex++;
        }
    }
}

void MovieController::removeMovies() {
    extern vector<Movie*>* movies;
    while (true) {
        ScreenUtility::clearScreen();
        if (!movies->empty()) {
            displayMovieList();
            cout << endl;
            cout << "To quit select: -1" << endl;
            cout << "Please select the movies by index: ";
            unsigned int selection;
            cin >> selection;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            if (selection > 0 && selection <= movies->size()) {
                cout << "You have selected " << movies->at(selection - 1)->getTitle() << endl;
                cout << "Are you sure you want to remove this movie (Y/N): ";
                string input;
                cin >> input;
                while (cin.fail()) {
                    cout << "Please enter characters only";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> input;
                }
                if (toupper(input.at(0)) != 'Y') {
                    cout << "Invalid selection" << endl;
                    ScreenUtility::pause();
                    continue;
                }
                cout << movies->at(selection - 1)->getTitle() << " successfully deleted" << endl;;
                movies->erase(movies->begin() + selection - 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
                ScreenUtility::pause();
            }
            else if (selection == -1) {
                break;
            }
            else {
                cout << "Invalid option, please try again." << endl;
                ScreenUtility::pause(); 
            }
        }
        else {
            cout << "No movies currently showing" << endl;
            break;
        }
    }
    movieRepository.save();
    ScreenUtility::pause();
    displayAdminMenu();
}
