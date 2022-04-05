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
#include "file.h"
#include "repository.h"
#include <regex>

extern Repository<Show> showRepository;

void ShowController::viewShows() {
    extern vector<Show*>* shows;
    ScreenUtility::clearScreen();
    if (!shows->empty()) {
        while (true) {
            ScreenUtility::clearScreen();
            int movieIndex = 1;
            cout << "Movies now showing: " << endl;
            cout << "==============================" << endl;
            for (Show* i : *shows) {
                cout << movieIndex << ") " << i->getTitle() << endl;
                movieIndex++;
            }
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
                Show* selectedShow = shows->at(selection - 1);
                cout << "You have selected " << selectedShow->getTitle()  << " " << selectedShow->getTime() << endl;
                selectedShow->showHallSeatingPlan();
                ScreenUtility::pause();
            }
            else if (selection == -1) {
                break;
            }
            else {
                cout << "Invalid option, please try again." << endl;
            }
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

        string time;
        cout << "Enter a time (HH:MM): ";
        cin >> time;
        while (cin.fail() || !regex_match(time, regex("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$"))) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Enter a time (HH:MM): ";
            cin >> time;
        }

        Show* newShow = new Show(selectedMovie->getTitle(), time, *selectedHall);
        shows->insert(shows->begin(), newShow);
        string input;
        cout << "Do you still want to add more shows(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(input[0]) != 'Y')
            cont = false;
    }
    showRepository.save();
}

