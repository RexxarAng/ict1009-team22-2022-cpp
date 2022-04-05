#pragma once
#include <ctime>
#include <string>
#include "hall.h"
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Show : public AbstractDataModel {
private:
	string title;
	string time;
	Hall hall;
public:
    Show(); // for deserialization
	Show(string title, string time, Hall hall);
	string getTitle();
    string getTime();
	int getHallId();
	void showHallSeatingPlan();
    Hall* getHall();

    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};

