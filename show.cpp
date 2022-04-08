#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <utility>
#include <regex>

#include "show.h"
#include "screen_utility.h"

void printColor(string, int = 0);

Show::Show() = default;

Show::Show(Movie movie, string time, Hall hall) {
	this->movie = std::move(movie);
	this->time = std::move(time);
    this->hall = std::move(hall);
}

string Show::getTime() {
    return this->time;
}

Hall* Show::getHall() {
    return &(this->hall);
}

Movie* Show::getMovie() {
    return &(this->movie);
}

void Show::setHall(Hall hall)
{
    this->hall = std::move(hall);
}

void Show::setMovie(Movie movie) {
    this->movie = std::move(movie);
}

int Show::getHallId() {
	return hall.getId();
}

void Show::showHallSeatingPlan() {
	printColor(this->getMovie()->getTitle(), 1);
	cout << " " << this->time << endl;
	hall.showSeatingPlan();
}

string Show::serialize() {
    string serializedString = this->getMovie()->serialize();
    serializedString += "~" + this->getTime();
    serializedString += "~" + this->getHall()->serialize();
    return serializedString;
}

void Show::deserialize(string dataString) {
    const int expectedEntities = 3;

    vector<string> entities = Show::extractEntitiesFromDataString(dataString);
    if (entities.size() < expectedEntities) throw ParseAttributeMismatchException(typeid(this).name(), expectedEntities, entities.size());
   
    this->movie.deserialize(entities[0]);
    this->time = std::move(entities[1]);
    this->hall.deserialize(entities[2]);
}


istream& operator>>(istream& in, Show* newShow)
{
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
	in.ignore(numeric_limits<streamsize>::max(), '\n');
    newShow->time = time;
	return in;
}