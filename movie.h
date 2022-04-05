#pragma once
#include <string>
#include <list>
#include "show.h"

using namespace std;

class Movie {
private:
	string title;
	string desc;
	string genre;
	int movieID;
	int duration;
	list<Show> shows;
public:
	Movie(string, string, string, int);
	string getTitle();
	void setTitle(string);
	string getDesc();
	void setDesc(string);
	string getGenre();
	void setGenre(string);
	int getmovieID();
	void setmovieID(int);
	int getDuration();
	void setDuration(int);
	list<Show> getShows();
};