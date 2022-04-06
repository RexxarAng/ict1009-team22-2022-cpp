#pragma once
#include <string>
#include "show.h"
#include "hall.h"
#include "movie.h"

class Booking{
private:
	int bookingID;
	int pax;
	int hallID;
	string tconst;
	string title;
	Show show;
public:
	Booking(int, int, int, string, string, Show);
	void makeBooking(); //rmb to make friend functions for movie, hall, and show)
	Hall getHall();
	friend void getTConst(Movie);
	bool bookSeat(int, int);
};