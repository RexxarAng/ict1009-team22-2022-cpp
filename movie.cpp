#include "movie.h"
#include <string>

Movie::Movie(string title, string desc, string genre, int duration) {
	this->title = title;
	this->desc = desc;
	this->genre = genre;
	this->duration = duration;
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
	return this->duration;
}

void Movie::setDuration(int duration) {
	this->duration = duration;
}

list<Show> Movie::getShows() {
	return this->shows;
}