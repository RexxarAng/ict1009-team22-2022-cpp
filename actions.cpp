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
