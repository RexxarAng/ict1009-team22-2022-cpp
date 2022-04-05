#pragma once
#include <string>
#include <list>
#include "show.h"

using namespace std;

class Movie {
private:
    int movieID; //a unique running number for the system
    string tconst; //a unique indentifier for the movie
	string title; //title of move
	string desc; //breif description of movie
	string genre; //Genres of the movie
	int runtime; //duration in mins
    int maturity; //0 =G, 1 = PG, 2 = PG13, 3 = NC16, 4 = M18, 5 =R21
    float rating; //rating upon 10
    string mainCast; //main casts of movie
    string language;
    bool isShowing; //if the movie is showing
	list<Show> shows;
public:
//	Movie(string, string, string, int);
    Movie(int, string, string, string, int, int, string, float, string, string);
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
};
