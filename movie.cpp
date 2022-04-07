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

string Movie::getTitle() {
	return this->title;
}

void Movie::setTitle(string newTitle) {
	this->title = std::move(newTitle);
}

string Movie::getDesc() {
	return this->desc;
}

void Movie::setDesc(string newDesc) {
	this->desc = std::move(newDesc);
}

string Movie::getGenre() {
	return this->genre;
}

void Movie::setGenre(string newGenre) {
	this->genre = std::move(newGenre);
}

int Movie::getDuration() const {
	return this->duration;
}

void Movie::setDuration(int newDuration) {
	this->duration = newDuration;
}

string Movie::serialize() {
    string serializedString = this->getTitle();
    serializedString += "," + this->getDesc();
    serializedString += "," + this->getGenre();
    serializedString += "," + to_string(this->getDuration());
    return serializedString;
}

void Movie::deserialize(string dataString) {
    const int expectedSize = 4;
    vector<string> attributes = Movie::extractAttributesFromDataString(dataString);

    if (attributes.size() < expectedSize) throw ParseAttributeMismatchException(typeid(this).name(), expectedSize, attributes.size());

    this->setTitle(attributes[0]);
    this->setDesc(attributes[1]);
    this->setGenre(attributes[2]);
    this->setDuration(stoi(attributes[3]));
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
        for (Movie* i : *movies) {
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
