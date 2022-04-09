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
    string serializedString = "\"" + this->getTitle() + "\"";
    serializedString += ",\"" + this->getDesc() + "\"";
    serializedString += ",\"" + this->getGenre() + "\"";
    serializedString += "," + to_string(this->getDuration());
    serializedString += "," + to_string(this->getMaturity());
    serializedString += "," + to_string(this->getRating());
    serializedString += ",\"" + this->getMainCast() + "\"";
    serializedString += ",\"" + this->getLanguage() + "\"";
    
    return serializedString;
}

void Movie::deserialize(string dataString) {
    const int expectedSize = 8;
    vector<string> attributes = Movie::extractAttributesFromDataString(dataString);
    if (attributes.size() < expectedSize) throw ParseAttributeMismatchException(typeid(this).name(), expectedSize, attributes.size());

    this->setTitle(attributes[0]);
    this->setDesc(attributes[1]);
    this->setGenre(attributes[2]);
    this->setDuration(stoi(attributes[3]));
    this->setMaturity(stoi(attributes[4]));
    this->setRating(stof(attributes[5]));
    this->setMainCast(attributes[6]);
    this->setLanguage(attributes[7]);
}

istream& operator>>(istream& in, Movie* newMovie)
{
    extern vector<Movie*>* movies;
    string movieName, currentMovieName, movieDesc, movieGenre, movieMainCast, movieLanguage;
    int movieDuration, movieMaturity;
    float movieRating;
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
        movieDesc = ScreenUtility::promptAndSanitizeStringInput("Movie Description: ");
        movieGenre = ScreenUtility::promptAndSanitizeStringInput("Movie Genre: ");
        cout << "Movie Duration(in mins): ";
        cin >> movieDuration;
        while (cin.fail()) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Movie Duration(in mins): ";
            cin >> movieDuration;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "0:G 1:PG 2:PG13 3:NC16 4:M18 5:R21" << endl;
        cout << "Maturity rating: ";
        cin >> movieMaturity;
        while (cin.fail() || movieMaturity < 0 || movieMaturity > 5) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Maturity rating: ";
            cin >> movieMaturity;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Imdb rating: ";
        cin >> movieRating;
        while (cin.fail()) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Imdb rating: ";
            cin >> movieRating;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        movieMainCast = ScreenUtility::promptAndSanitizeStringInput("Movie Main Casts: ");
        movieLanguage = ScreenUtility::promptAndSanitizeStringInput("Movie Language: ");

        newMovie->setTitle(movieName);
        newMovie->setDesc(movieDesc);
        newMovie->setGenre(movieGenre);
        newMovie->setDuration(movieDuration);
        newMovie->setMaturity(movieMaturity);
        newMovie->setRating(movieRating);
        newMovie->setMainCast(movieMainCast);
        newMovie->setLanguage(movieLanguage);
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return in;
    }
}


ostream& operator<<(ostream& out, Movie* movie) {
    string maturity[] = { "G", "PG", "PG13", "NC16", "M18", "R21" };
    for (int i = 0; i < movie->getTitle().size(); i++) {
        out << "=";
    }
    out << endl;
    out << movie->title << endl;
    for (int i = 0; i < movie->getTitle().size(); i++) {
        out << "=";
    }
    out << endl;
    out << maturity[movie->getMaturity()].c_str();
    out << " " << movie->getDuration() << "mins";
    out << " " << movie->getRating() << " / 10 IMDb" << endl;
    
    out << movie->genre << endl << endl;

    out << movie->desc << endl << endl;

    out << "Starring: " << movie->mainCast << endl << endl;

    out << "Available in: " << movie->language << endl;

    return out;
}