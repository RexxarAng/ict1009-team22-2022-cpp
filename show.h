#pragma once
#pragma warning(disable : 4996)
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
	tm getDate();
	int getHallId();
	void showHallSeatingPlan();
};

