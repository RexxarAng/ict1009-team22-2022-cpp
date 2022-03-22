#pragma once
#include "main.h"
#include "colors.h"

void printColor(string, int);

class Hall {
private:
	int id;
	int noOfRows;
	int noOfCols;
	bool** seating;
	void printScreen();
	void printLegend();
public:
	Hall(int, int);
	static int current_id;
	int getId();
	void showSeatingPlan(bool, bool);
	void bookSeat(int, int);
};

int Hall::current_id = 0;

Hall::Hall(int noOfRows, int noOfCols) {
	this->noOfRows = noOfRows;
	this->noOfCols = noOfCols;
	current_id++;
	this->id = current_id;
	seating = new bool* [noOfRows];
	for (int i = 0; i < noOfRows; i++) {
		seating[i] = new bool[noOfCols];
	}

}

int Hall::getId() {
	return this->id;
}

void Hall::showSeatingPlan(bool showColumnInformation = true, bool showRowInformation = true) {
	printScreen();

	if (showColumnInformation) {
		// Print Column Information
		if (showRowInformation) cout << "   ";
		for (int c = 0; c < noOfCols; c++) {
			cout << " ";
			// padd if less than 10
			if (c < 10) cout << " " << c;
			else cout << c;
			cout << "  ";
		}
		cout << endl;
	}

	// Print every seating information
	for (int r = 0; r < noOfRows; r++) {
		if (showRowInformation) cout << " " << (char)('A' + r) << " ";
		for (int c = 0; c < noOfCols; c++) {
			printColor("[", -1);
			// is booked
			if (!seating[r][c]) { 
				printColor(" x ", 2);
			}
			else {
				printColor(" o ", 1);
			}
			printColor("]", -1);
		}
		cout << endl;
	}
	cout << endl;
	printLegend();


}

void Hall::bookSeat(int row, int column) {
	seating[row][column] = false;
}

void Hall::printScreen() {
	string screen = "SCREEN";
	int lengthOfWord = size(screen);
	int lengthOfScreen = noOfCols * 5;
	int halfDashes = (lengthOfScreen - lengthOfWord) / 2;
	printColor("   +", -1);
	for (int c = 0; c < lengthOfScreen - 2; c++) {
		printColor("-", -1);
	}
	printColor("+", -1);
	cout << endl;
	printColor("   |", -1);
	for (int c = 0; c < halfDashes - 1; c++) {
		cout << " ";
	}
	printColor(screen, -1);
	for (int c = 0; c < lengthOfScreen - halfDashes - lengthOfWord - 1; c++) {
		cout << " ";
	}
	printColor("|", -1);
	cout << endl;
	printColor("   +", -1);
	for (int c = 0; c < lengthOfScreen - 2; c++) {
		printColor("-", -1);
	}
	printColor("+", -1);
	cout << endl << endl;
}

void Hall::printLegend() {

	printColor("[", -1);
	printColor(" o ", 1);
	printColor("]", -1);
	printColor(" Available");
	cout << "   ";
	printColor("[", -1);
	printColor(" x ", 2);
	printColor("]", -1);
	printColor(" Sold");
	cout << endl << endl;
}
