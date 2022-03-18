#pragma once
#include <string>

using namespace std;

class Movie {
private:
	string title;
	string desc;
	string genre;
	int duration;
public:
	Movie(string, string, string, int);
	string getTitle();
	void setTitle(string);
	string getDesc();
	void setDesc(string);
	string getGenre();
	void setGenre(string);
	int getDuration();
	void setDuration(int);
};