#ifndef ICT1009_TEAM22_2022_CPP_HALL_CONTROLLER_H
#define ICT1009_TEAM22_2022_CPP_HALL_CONTROLLER_H
#include "hall.h"

class HallController {
public:
	static void viewHalls();
	static void displayHallList();
	static void addHalls();
	static void removeHalls();
	static Hall* promptHallSelection();
};

#endif