#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <utility>
#include "show.h"

void printColor(string, int = 0);

Show::Show() = default;

Show::Show(string title, string time, Hall hall) {
	this->title = std::move(title);
	this->time = std::move(time);
    this->hall = std::move(hall);
}

string Show::getTitle() {
	return this->title;
}

string Show::getTime() {
    return this->time;
}

Hall* Show::getHall() {
    return &(this->hall);
}

int Show::getHallId() {
	return hall.getId();
}

void Show::showHallSeatingPlan() {
	printColor(title, 1);
	cout << " " << this->time << endl;
	hall.showSeatingPlan();
}

string Show::serialize() {
    string serializedString = this->getTitle();
    serializedString += ";" + this->getTime();
    serializedString += ";" + this->getHall()->serialize();
    return serializedString;
}

void Show::deserialize(string dataString) {
    vector<string> attributes = Show::extractAttributesFromDataString(dataString, ';');

    if (attributes.size() < 3) throw ParseAttributeMismatchException();

    this->title = std::move(attributes[0]);
    this->time = std::move(attributes[1]);
    this->hall.deserialize(attributes[2]);
}
