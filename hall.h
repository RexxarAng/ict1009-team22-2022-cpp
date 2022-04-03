#pragma once
class Hall {
private:
	int id;
	int noOfRows;
	int noOfCols;
	bool** seating;
	void printHallId() const;
	void printScreen();
	void printLegend();
public:
	Hall(int, int);
	static int current_id;
	int getId();
	void showSeatingPlan(bool showColumnInformation = true, bool showRowInformation = true);
	bool bookSeat(int, int);
};