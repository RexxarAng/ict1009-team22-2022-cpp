#pragma once
#include <ctime>
#include <string>
#include "hall.h"
using namespace std;

class Show {
private:
	string title;
	tm date;
	Hall hallOfShow;
public:
	Show(string, tm, Hall);
	string getTitle();
	int getHallId();
	void showHallSeatingPlan();
	tm getDate();
};

