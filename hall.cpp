#include <string>
#include <iostream>

#include "hall.h"
#include "colors.h"
#include "screen_utility.h"

using namespace std;

int Hall::current_id = 1;

Hall::Hall() = default;

Hall::Hall(int noOfRows, int noOfCols) {
    this->noOfRows = noOfRows;
    this->noOfCols = noOfCols;
    current_id++;
    this->id = current_id;
	// Create seating where all is not booked
	vector<vector<bool>> newSeating(noOfRows, vector<bool>(noOfCols, false));
	this->seating = newSeating;
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

    serializedString += ",";
    int i = 0;
    for (int r = 0; r < this->noOfRows; r++) {
        for (int c = 0; c < this->noOfCols; c++) {
            if (this->seating[r][c]) serializedString += "1";
            else serializedString += "0";
            serializedString += '|';
        }
    }

    return serializedString;
}

void Hall::deserialize(string dataString) {
    const int expectedSize = 4;
    vector<string> attributes = Hall::extractAttributesFromDataString(dataString);

    if (attributes.size() < expectedSize)
        throw ParseAttributeMismatchException(typeid(this).name(), expectedSize, (int)attributes.size());

    this->id = stoi(attributes[0]);
    this->noOfRows = stoi(attributes[1]);
    this->noOfCols = stoi(attributes[2]);
    this->current_id = this->id + 1;

    // Create booking seating
	vector<vector<bool>> newSeating(noOfRows, vector<bool>(noOfCols, false));
	this->seating = newSeating;

    vector<string> seatingDataString = Hall::extractAttributesFromDataString(attributes[3], '|');
    int i = 0;
    for (int r = 0; r < this->noOfRows; r++) {
        for (int c = 0; c < this->noOfCols; c++) {
            this->seating[r][c] = seatingDataString[i] == "1";
            i++;
        }
    }
}

istream& operator>>(istream& in, Hall* newHall)
{
	int rows, cols;
	cout << "Hall rows: ";
	in >> newHall->noOfRows;
	while (in.fail()) {
		cout << "Invalid input, only accept numbers" << endl;
		in.clear();
		in.ignore(256, '\n');
		ScreenUtility::pause();
		cout << "Hall rows: ";
		in >> newHall->noOfRows;
	}
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Hall columns: ";
	in >> newHall->noOfCols;
	while (in.fail()) {
		cout << "Invalid input, only accept numbers" << endl;
		in.clear();
		in.ignore(256, '\n');
		ScreenUtility::pause();
		cout << "Hall columns: ";
		in >> newHall->noOfCols;
	}
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<vector<bool>> newSeating(newHall->noOfRows, vector<bool>(newHall->noOfCols, false));
	newHall->seating = newSeating;
	newHall->current_id++;
	newHall->id = newHall->current_id;
	return in;
}