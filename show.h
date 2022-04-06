#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <string>
#include "hall.h"
using namespace std;

class Show {
private:
	int showID;
	tm date;
	Hall hallOfShow;
public:
	Show(int, tm, Hall);
	tm getDate();
	int getHallId();
	void showHallSeatingPlan();
};

