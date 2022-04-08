#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "show_controller.h"
#include "movie_controller.h"
#include "hall_controller.h"
#include "screen_utility.h"
#include "show.h"
#include "menu.h"
#include "repository.h"
#include <regex>

extern Repository<Show> showRepository;

void ShowController::viewShows() {
    extern vector<Show*>* shows;
    ScreenUtility::clearScreen();
    if (!shows->empty()) {
        while (true) {
            ScreenUtility::clearScreen();
            ShowController::displayShowList();
            Show* selectedShow = ShowController::promptShowSelection();
            if (selectedShow == nullptr) {
                break;
            }
            cout << "You have selected " << selectedShow->getMovie()->getTitle() << " " << selectedShow->getTime() << endl;
            selectedShow->showHallSeatingPlan();
            ScreenUtility::pause();
            
        }
    }
    else {
        cout << "No movies currently showing" << endl;
    }

    ScreenUtility::pause();
}

void ShowController::addShows() {
    extern vector<Show*>* shows;
    extern vector<Movie*>* movies;
    extern vector<Hall*>* halls;
    vector<string> row;
    string movieName;
    int movieDuration;
    cout << "Adding Shows..." << endl;
    bool cont = true;
    while (cont) {
        ScreenUtility::clearScreen();
        if (halls->empty()) {
            cout << "No available halls" << endl;
            ScreenUtility::pause();
            break;
        } 
        else if (movies->empty()) {
            cout << "No available movies" << endl;
            ScreenUtility::pause();
            break;
        }
        
        MovieController::displayMovieList();
        Movie* selectedMovie = MovieController::promptMovieSelection();
        if (selectedMovie == nullptr) break;
        
        HallController::displayHallList();
        Hall* selectedHall = HallController::promptHallSelection();
        if (selectedHall == nullptr) break;
        Show* newShow = new Show();
        newShow->setHall(*selectedHall);
        newShow->setMovie(*selectedMovie);
        cin >> newShow;

        shows->insert(shows->end(), newShow);
        string input;
        cout << "Do you still want to add more shows(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(input[0]) != 'Y')
            cont = false;
    }
    showRepository.save();
}

void ShowController::displayShowList() {
    extern vector<Show*>* shows;
    int movieIndex = 1;
    cout << "=================================" << endl;
    cout << "CHAW THEATERS MOVIE SHOWTIMES: " << endl;
    cout << "=================================" << endl << endl;
    for (Show* i : *shows) {
        cout << movieIndex << ") " << i->getMovie()->getTitle() << " " << i->getTime() << endl;
        movieIndex++;
    }
    cout << endl;
}

Show* ShowController::promptShowSelection() {
    extern vector<Show*>* shows;
    if (!shows->empty()) {
        while (true) {
            cout << "To quit select: -1" << endl;
            cout << "Please select the movies by index: ";
            unsigned int selection;
            cin >> selection;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            if (selection > 0 && selection <= shows->size()) {
                return shows->at(selection - 1);
            }
            else if (selection == -1) {
                return nullptr;
            }
            else {
                cout << "Invalid option, please try again." << endl;
            }
        }
    }
    return nullptr;
}

void ShowController::removeShows(Movie* removedMovie) {
    extern vector<Show*>* shows;
    for (Show* i: *shows) {
        
    }
}

void ShowController::removeShows(Hall* removedHall) {
    extern vector<Show*>* shows;

}

