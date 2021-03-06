#ifndef ICT1009_TEAM22_2022_CPP_MOVIE_CONTROLLER_H
#define ICT1009_TEAM22_2022_CPP_MOVIE_CONTROLLER_H
#include "screen_utility.h"
#include "movie.h"
#include "colors.h"
#include "show.h"

class MovieController {
private:
public:
	static void viewMovies();
    static void displayMovieList();
    static Movie* promptMovieSelection();
    static void addMovies();
    static void removeMovies();
};


#endif