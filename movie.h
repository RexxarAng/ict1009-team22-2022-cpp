#pragma once
#include <string>
#include <vector>
#include "show.h"
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Movie : AbstractDataModel {
private:
	string title;
	string desc;
	string genre;
	int duration{};

    vector<Show> shows;

public:
    Movie(); // for deserialization
	Movie(string, string, string, int);

	string getTitle();
	void setTitle(string);
	string getDesc();
	void setDesc(string);
	string getGenre();
	void setGenre(string);
	int getDuration() const;
	void setDuration(int);

    string serialize() override;
    void deserialize(string) override;
};