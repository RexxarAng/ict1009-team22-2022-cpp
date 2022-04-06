#include "movie.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

Movie::Movie() = default;

Movie::Movie(int movieID, string tconst, string title , string desc, int runtime, int maturity, string genre, float rating, string maincast, string language){
    this -> movieID = movieID; //a unique running number for the system
    this -> tconst = tconst; //a unique indentifier for the movie
    this -> title = title; //title of move
    this -> desc = desc; //breif description of movie
    this -> genre = genre; //Genres of the movie
    this -> runtime = runtime; //duration in mins
    this -> maturity = maturity; // maturity of movie
    this -> rating = rating; //rating upon 10
    this -> mainCast = maincast; //main casts of movie
    this -> language = language; //main langauge of movie

Movie::~Movie() {
    cout << this->title << " is deleted." << endl;

}
  
int Movie::getmovieID() {
	return this->movieID;
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

int Movie::getDuration() {
	return this->runtime;
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
    vector<string> attributes = Movie::extractAttributesFromDataString(dataString);

    cout << attributes.size() << endl;
    if (attributes.size() < 4) throw ParseAttributeMismatchException();

    this->setTitle(attributes[0]);
    this->setDesc(attributes[1]);
    this->setGenre(attributes[2]);
    this->setDuration(stoi(attributes[3]));
}
