#pragma once
#include <string>
#include <vector>
#include "show.h"
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Movie : public AbstractDataModel {
private:
	string title;
	string desc;
	string genre;
	int duration{};

public:
    Movie(); // for deserialization
	Movie(string, string, string, int);
	~Movie();
	string getTitle();
	void setTitle(string);
	string getDesc();
	void setDesc(string);
	string getGenre();
	void setGenre(string);
	int getDuration() const;
	void setDuration(int);
	friend istream& operator>>(istream&, Movie*);

    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};