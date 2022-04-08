#include "movie.h"
#include <iostream>
#include <string>
#include <utility>
#include "screen_utility.h"

using namespace std;

Movie::Movie() = default;

Movie::Movie(string newTitle, string newDesc, string newGenre, int newDuration) {
	this->title = std::move(newTitle);
	this->desc = std::move(newDesc);
	this->genre = std::move(newGenre);
	this->duration = newDuration;
}

//setters and getters
string Movie::getMovieID(){return this->movieID;}
void Movie::setMovieID(string movieID){this->movieID = movieID;}
string Movie::getTitle() {return this->title;}
void Movie::setTitle(string newTitle) {this->title = std::move(newTitle);}
string Movie::getDesc() {return this->desc;}
void Movie::setDesc(string newDesc) {this->desc = std::move(newDesc);}
string Movie::getGenre() {return this->genre;}
void Movie::setGenre(string newGenre) {this->genre = std::move(newGenre);}
int Movie::getDuration() const {return this->duration;}
void Movie::setDuration(int newDuration) {this->duration = newDuration;}
int Movie::getMaturity(){return this->maturity;}
void Movie::setMaturity(int maturity){this->maturity = maturity;}
float Movie::getRating(){return this->rating;}
void Movie::setRating(float rating){this->rating = rating;}
string Movie::getMainCast(){return this->mainCast;}
void Movie::setMainCast(string mainCast){this-> mainCast = mainCast;}
string Movie::getLanguage(){return this->language;}
void Movie::setLanguage(string language){this->language = language;}

string Movie::serialize() {
    string serializedString = this->getTitle();
    serializedString += "," + this->getDesc();
    serializedString += "," + this->getGenre();
    serializedString += "," + to_string(this->getDuration());
    
    return serializedString;
}

void Movie::deserialize(string dataString) {
    vector<string> attributes = Movie::extractAttributesFromDataString(dataString);
    for(string i: attributes){
        cout << "Item:" << i << endl;
    }
    //cout << attributes.size() << endl;
    if (attributes.size() < 4) throw ParseAttributeMismatchException();
    
    this->setMovieID(attributes[0]);
    this->setTitle(attributes[1]);
    this->setDesc(attributes[2]);
    this->setDuration(stoi(attributes[3]));
    this->setMaturity(stoi(attributes[4]));
    this->setGenre(attributes[5]);
    this->setRating(stof(attributes[6]));
    this->setMainCast(attributes[7]);
    this->setLanguage(attributes[8]);
}

istream& operator>>(istream& in, Movie* newMovie)
{
    extern vector<Movie*>* movies;
    string movieName, currentMovieName, movieDesc, movieGenre;
    int movieDuration;
    while (true) {
        bool isExist = false;
        cout << "Movie Name: ";
        getline(in, movieName);
        for(Movie* i : *movies) {
            if (movieName == i->getTitle()) {
                cout << "Movie already exists";
                isExist = true;
                ScreenUtility::pause();
                break;
            }
        }
        if (isExist)
            continue;
        cout << "Movie Description: ";
        getline(in, movieDesc);
        cout << "Movie Genre: ";
        getline(in, movieGenre);
        cout << "Movie Duration(in mins): ";
        cin >> movieDuration;
        while (cin.fail()) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> movieDuration;
        }
        newMovie->setTitle(movieName);
        newMovie->setDesc(movieDesc);
        newMovie->setGenre(movieGenre);
        newMovie->setDuration(movieDuration);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return in;
    }
}
