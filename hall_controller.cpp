#include "hall_controller.h"
#include "repository.h"
#include "hall.h"
#include "menu.h"

extern Repository<Hall> hallRepository;

void HallController::viewHallList() {
    extern vector<Hall*>* halls;
    cout << "All Halls: " << endl;
    cout << "==============================" << endl;
    int hallIndex = 1;
    for (Hall* i : *halls) {
        cout << hallIndex << ") " << "Hall " << i->getId() << endl;
        hallIndex++;
    }
    cout << "Please select the hall by index: ";
}

void HallController::viewHalls() {
	extern vector<Hall*>* halls;
    ScreenUtility::clearScreen();
    if (!halls->empty()) {
        viewHallList();
        unsigned int selection;
        cin >> selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
        if (selection > 0 && selection <= halls->size()) {
            cout << "You have selected " << halls->at(selection - 1)->getId() << endl;
            halls->at(selection - 1)->showSeatingPlan();
        }
        else {
            cout << "Invalid option, please try again." << endl;
        }
    }
    else {
        cout << "No halls available" << endl;
    }
    ScreenUtility::pause();
    displayMainMenu();
}

void HallController::addHalls() {
    extern vector<Hall*>* halls;
    ScreenUtility::clearScreen();
    vector<string> row;
    int rows, cols;
    cout << "Adding Halls..." << endl;
    bool cont = true;
    while (cont) {
        cout << "Hall rows: ";
        cin >> rows;
        if (cin.fail()) {
            cout << "Invalid input, only accept numbers" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }
        cout << "Hall columns: ";
        cin >> cols;
        while (cin.fail()) {
            cout << "Invalid input, only accept numbers" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> cols;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Hall* newHall = new Hall(rows, cols);
        halls->insert(halls->end(), newHall);
        string input;
        cout << "Do you still want to add more halls(Y/N): ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(input[0]) != 'Y')
            cont = false;
    }
    hallRepository.save();
    ScreenUtility::pause();
    displayAdminMenu();
}

void HallController::removeHalls() {
    cout << "To be implemented" << endl;
    ScreenUtility::pause();
    displayAdminMenu();
}
