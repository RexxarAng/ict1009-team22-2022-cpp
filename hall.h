#ifndef ICT1009_TEAM22_2022_HALL_H
#define ICT1009_TEAM22_2022_HALL_H

#include "repository_template.h"
#include "repository_exception.h"

class Hall : public AbstractDataModel {
protected:
	int id{};
	int noOfRows{};
	int noOfCols{};
	static int current_id;
	vector<vector<bool>> seating{};
	void printHallId() const;
	void printScreen() const;
	static void printLegend();

public:
    Hall();
	Hall(int, int);
	int getId() const;
	void showSeatingPlan(bool showColumnInformation = true, 
	bool showRowInformation = true);
	bool bookSeat(int, int);
	friend istream& operator>>(istream& in, Hall*);

    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};
#endif
