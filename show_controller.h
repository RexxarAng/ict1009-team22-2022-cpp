#ifndef ICT1009_TEAM22_2022_CPP_SHOW_CONTROLLER_H
#define ICT1009_TEAM22_2022_CPP_SHOW_CONTROLLER_H
#include "screen_utility.h"
#include "movie.h"
#include "colors.h"
#include "show.h"
#include "hall.h"

class ShowController {
private:
public:
    static void viewShows();
    static void displayShowList();
    static Show* promptShowSelection();
    static void addShows();
    static void removeShows(Hall*);
    static void removeShows(Movie*);

};


#endif