#ifndef ICT1009_TEAM22_2022_CPP_BOOKING_CONTROLLER_H
#define ICT1009_TEAM22_2022_CPP_BOOKING_CONTROLLER_H
#include "screen_utility.h"
#include "movie.h"
#include "colors.h"
#include "show.h"

class BookingController {
private:
public:
    static void viewBookings();
    static void promptSeatSelection(Show*);
    static void bookMovies();
};

#endif