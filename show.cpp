#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include "show.h"

void printColor(string, int = 0);

Show::Show(int showID, tm date, Hall hallOfShow) : hallOfShow(hallOfShow) {
	this->showID = showID;
	this->date = date;
}

tm Show::getDate() {
	return this->date;
}

int Show::getHallId() {
	return hallOfShow.getId();
}

void Show::showHallSeatingPlan() {
	//printColor(title, 1);
	cout << " " << asctime(&date) << endl;
	hallOfShow.showSeatingPlan();
}