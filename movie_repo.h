#ifndef ICT1009_TEAM22_2022_CPP_MOVIE_REPO_H
#define ICT1009_TEAM22_2022_CPP_MOVIE_REPO_H
#include <vector>
#include "movie.h"
#include "repository.h"


Repository<Movie> movieRepository("movieCatalog.csv");
vector<Movie*>* movies = movieRepository.getRecords();

#endif //ICT1009_TEAM22_2022_CPP_MOVIE_REPO_H