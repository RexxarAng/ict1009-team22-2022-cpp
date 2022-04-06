#include "booking.h"
#include <string>
#include <iostream>

using namespace std;

Booking::Booking(int bookingID, int pax, int hallID, string tconst, string title, Show show) : show(show) {
	this->bookingID = bookingID;	
}

bool Booking::bookSeat(int row, int column) {
	
}