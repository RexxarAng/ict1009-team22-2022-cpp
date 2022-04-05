#pragma once
#include "repository_template.h"
#include "repository_exception.h"

class Hall : AbstractDataModel {
private:
	int id{};
	int noOfRows{};
	int noOfCols{};
	bool** seating{};
	void printHallId() const;
	void printScreen() const;
	static void printLegend();
public:
    Hall();
	Hall(int, int);
	static int current_id;
	int getId() const;
	void showSeatingPlan(bool showColumnInformation = true, bool showRowInformation = true);
	bool bookSeat(int, int);

    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};