#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "movie_controller.h"
#include "menu.h"
#include "repository.h"

extern Repository<Movie> movieRepository;
extern Repository<Show> showRepository;

void MovieController::viewMovies() {
    extern vector<Movie*>* movies;
    string maturity[] = {"G", "PG", "PG13", "NC16", "M18", "R21"};
    ScreenUtility::clearScreen();
    if (!movies->empty()) {

        while (true) {
            ScreenUtility::clearScreen();
            int movieIndex = 1;
            cout << "=================================" << endl;
            cout << "CHAW THEATERS MOVIES NOW SHOWING: " << endl;
            cout << "=================================" << endl<<endl;
            for (Movie* i : *movies) {
                int matureRate = i->getMaturity();
                if ((i->getMaturity() > 6) || (i->getMaturity() < 0)){
                    cerr << "ERROR: Mature Ratings is out of range." << endl;
                    matureRate = 0;
                }
                char buffer[10000];
                
                sprintf(buffer, "%d) %s\n\t%-4s || %-3d mins",
                        movieIndex,
                        i->getTitle().c_str(),
                        maturity[i->getMaturity()].c_str(),
                        i->getDuration());
                cout << buffer;
                cout << endl << endl;
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
            if (selection > 0 && selection <= movies->size()) {
                ScreenUtility::clearScreen();
                Movie* selectedMovie = movies->at(selection - 1);
                cout << selectedMovie;
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

Movie* MovieController::promptMovieSelection() {
    extern vector<Movie*>* movies;
    if (!movies->empty()) {

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
            if (selection > 0 && selection <= movies->size()) {
                return movies->at(selection - 1);
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

void MovieController::addMovies() {
    extern vector<Movie*>* movies;
    vector<string> row;
    string line, word;
    bool cont = true;
    while (cont) {
        ScreenUtility::clearScreen();
        MovieController::displayMovieList();
        cout << "Adding Movies..." << endl;
        Movie* newMovie = new Movie();
        cin >> newMovie;
        movies->insert(movies->end(), newMovie);
        string input;
        cout << "Do you still want to add more movies(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(input[0]) != 'Y')
            cont = false;
    }
    movieRepository.save();
}

void MovieController::displayMovieList() {
    extern vector<Movie*>* movies;
    if (!movies->empty()) {
        int movieIndex = 1;
        cout << "==============================" << endl;
        cout << "NOW SHOWING: " << endl;
        cout << "==============================" << endl;
        for (Movie* i : *movies) {
            cout << movieIndex << ") " << i->getTitle() << endl;
            movieIndex++;
        }
        cout << endl;
    }
}

void MovieController::removeMovies() {
    extern vector<Movie*>* movies;
    extern vector<Show*>* shows;
    while (true) {
        ScreenUtility::clearScreen();
        if (!movies->empty()) {
            displayMovieList();
            cout << endl << "Which movie would you like to remove?" << endl;
            Movie* selectedMovie = promptMovieSelection();
            if (selectedMovie == nullptr)
                break;
            cout << "You have selected " << selectedMovie->getTitle() << endl;
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
            cout << selectedMovie->getTitle() << " successfully deleted" << endl;
            for (auto& showPtr : *shows) {
                if (showPtr->getMovie()->getTitle() == selectedMovie->getTitle()) {
                    delete showPtr;
                    showPtr = nullptr;
                }
            }
            shows->erase(remove(shows->begin(), shows->end(), nullptr), shows->end());
            movies->erase(remove(movies->begin(), movies->end(), selectedMovie));
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            ScreenUtility::pause();
        }
        else {
            cout << "No movies currently showing" << endl;
            break;
        }
    }
    showRepository.save();
    movieRepository.save();
    ScreenUtility::pause();
}
