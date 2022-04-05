#include <string>
#include <iostream>

#include "hall.h"
#include "colors.h"

using namespace std;

int Hall::current_id = 0;

Hall::Hall() = default;

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

int Hall::getId() const {
	return this->id;
}

void Hall::showSeatingPlan(bool showColumnInformation, bool showRowInformation) {
	printHallId();
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
 			if (seating[r][c]) {
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

bool Hall::bookSeat(int row, int column) {
	if (row < 0 || row >= noOfRows || column < 0 || column >= noOfCols) {
		cout << "Invalid seat" << endl;
		return false;
	}
	if (seating[row][column]) {
		cout << "Seat is already occupied" << endl;
		return false;
	}
	seating[row][column] = true;
	cout << "Successfully booked " << (char)('A' + row) << column << endl;
	return true;
}

void Hall::printHallId() const {
	string hallId = "Hall " + to_string(this->id);
	int lengthOfScreen = noOfCols * 5;
	int lengthOfWord = hallId.size();
	int halfDashes = (lengthOfScreen - lengthOfWord) / 2;
	cout << "    ";
	for (int c = 0; c < halfDashes - 1; c++) {
		cout << " ";
	}
	printColor(hallId, -1);
	for (int c = 0; c < lengthOfScreen - halfDashes - lengthOfWord - 1; c++) {
		cout << " ";
	}
	cout << endl << endl;
}
void Hall::printScreen() const {
	string screen = "SCREEN";
	int lengthOfWord = screen.size();
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

string Hall::serialize() {
    string serializedString = to_string(this->id);
    serializedString += "," + to_string(this->noOfRows);
    serializedString += "," + to_string(this->noOfCols);
    return serializedString;
}

void Hall::deserialize(string dataString) {
    vector<string> attributes = Hall::extractAttributesFromDataString(dataString);

    cout << attributes.size() << endl;
    if (attributes.size() < 3) throw ParseAttributeMismatchException();

    this->id = stoi(attributes[0]);
    this->noOfRows = stoi(attributes[1]);
	this->noOfCols = stoi(attributes[2]);
	seating = new bool* [this->noOfRows];
	for (int i = 0; i < this->noOfRows; i++) {
		seating[i] = new bool[this->noOfCols];
	}
}

