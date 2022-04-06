#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <list>

#include "actions.h"
#include "movie.h"
#include "show.h"
#include "menu.h"
#include "menu_item.h"
#include "file.h"
#include "colors.h"
#include "screen_utility.h"

extern vector<Movie*>* movies; //a list of loaded movies

using namespace std;

//prototyping helper function
vector<string> readCSVRow(const string &row);
void loadMovies() {
    /*This function loads all the movie showing from the movies catalog file. Returns error if fail, continues otherwise.*/
    ifstream movieCatalogFile;
    vector<string> row;
    string word, line;
    string fileOpenError = "File failed to open.";
    int index = 0;
    try{
        movieCatalogFile.open(MOVIE_FILE);
        if (movieCatalogFile.fail()) throw (fileOpenError);
    }
    catch(string fileOpenError){
        cerr << "ERROR: " << fileOpenError;
        cerr << " No movies loaded." << endl;
        pause();
        exit(1);
    }
    cout << "DEBUG: loadMovies suceeded" << endl;
    while (!movieCatalogFile.eof()) {
        //Interates thru the entire file row by row
        row.clear();
        getline(movieCatalogFile, line);
        stringstream s(line);
        auto row = readCSVRow(line);
        if (index == 0){
            index++;
            continue;
        }
        if (row.size() == 9) {
            //Ensures that there is no missing information for the row
//            cout << "DEBUG: Inserting: " << row[0] << endl;
            try{
                Movie* newMovie = new Movie(index, row[0], row[1] , row[2], stoi(row[3]), stoi(row[4]), row[5], stof(row[6]), row[7], row[8]);
                //create a new movie object with the data from the file
                movies.insert(movies.end(), newMovie); //insert the movie object into a list of movies
                index ++;
                cout << "DEBUG: Insert Sucessfull." << endl;
            }
            catch(invalid_argument){
                cout << "ERROR: Invalid Argumanet found in row, skipping..." << endl;
                continue;
            }
        }
        else{
            cout << "DEBUG: Missing information in row. Skipping... " << endl;
        }
        if (movieCatalogFile.eof()) break;
    }
    movieCatalogFile.close();
}

void viewMovies() {
    /*This function prints all the movies that is currently showing, fired when user wants to browse catalogs*/
    system("cls");
    //Iterate
    if (movies.size() > 0) {
        //Printe
        cout << "=================================" << endl;
        cout << "CHAW THEATERS MOVIES NOW SHOWING: " << endl;
        cout << "=================================" << endl;
        
        //generate an array of menu items for menu engine to process
        vector<Menu_Item> view_moviesMenu;
        for (Movie* i : movies) {
            int id = i-> getmovieID();
            string text = i->getTitle();
            char* textChar;
            textChar = &text[0];
            Menu_Item* menu_Item = new Menu_Item(id, textChar, viewSomething);
            view_moviesMenu.push_back(*menu_Item);
        }
        // Process the menu
        Menu_Engine(view_moviesMenu, 5);
    }
    else {
        cout << "No movies currently showing" << endl;
    }
    pause();
    displayMainMenu();
}

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

    //testing
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
            /*
            for (it = selectedMovie.getShows().begin(); it != selectedMovie.getShows().end(); it++) {
                //unsure if I'm making a shallow or deep copy here
                currentDate = it->getDate();
                mktime(&currentDate);
                cout << asctime(&currentDate) << "-" << "calc end of movie here" << endl; //mktime converts tm to time_t
            }
            cin >>
            */

    }
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

void pause() {
    cout << endl << "Press <Enter> to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

//helper function to parse CSV files with commas and quotes
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};
vector<string> readCSVRow(const string &row) {
    CSVState state = CSVState::UnquotedField;
    vector<string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}