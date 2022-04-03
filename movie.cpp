#include "movie.h"
#include <iostream>
#include <string>
#include <utility>

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
    string serializedString;
    serializedString += this->getTitle();
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
