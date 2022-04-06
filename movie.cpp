#include "movie.h"
#include <string>

Movie::Movie(int movieID, string tconst, string title , string desc, int runtime, int maturity, string genre, float rating, string maincast, string language){
    this -> movieID = movieID; //a unique running number for the system
    this -> tconst = tconst; //a unique indentifier for the movie
    this -> title = title; //title of move
    this -> desc = desc; //breif description of movie
    this -> genre = genre; //Genres of the movie
    this -> runtime = runtime; //duration in mins
    this -> maturity = maturity; // maturity of movie
    this -> rating = rating; //rating upon 10
    this -> mainCast = maincast; //main casts of movie
    this -> language = language; //main langauge of movie
}
string Movie::getTitle() {
	return this->title;
}

void Movie::setTitle(string title) {
	this->title = title;
}

string Movie::getDesc() {
	return this->desc;
}

void Movie::setDesc(string desc) {
	this->desc = desc;
}

string Movie::getGenre() {
	return this->genre;
}

void Movie::setGenre(string genre) {
	this->genre = genre;
}


int Movie::getmovieID() {
	return this->movieID;
}

void Movie::setmovieID(int movieID) {
	this->movieID = movieID;
}

int Movie::getDuration() {
	return this->runtime;
}

void Movie::setDuration(int runtime) {
    this->runtime = runtime;
}
