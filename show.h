#ifndef ICT1009_TEAM22_2022_SHOW_H
#define ICT1009_TEAM22_2022_SHOW_H

#include <ctime>
#include <string>
#include "hall.h"
#include "movie.h"
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Show : public AbstractDataModel {
private:
	string time;
	Hall hall;
	Movie movie;
public:
    Show(); // for deserialization
	Show(Movie movie, string time, Hall hall);
    string getTime();
	int getHallId();
	void setMovie(Movie);
	void setHall(Hall);
	void showHallSeatingPlan();
    Hall* getHall();
	Movie* getMovie();
	friend istream& operator>>(istream&, Show*);
	friend bool operator<(Show const&, Show const&);
    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};
#endif
