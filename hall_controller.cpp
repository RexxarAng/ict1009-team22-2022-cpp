#include "hall_controller.h"
#include "repository.h"
#include "hall.h"
#include "menu.h"

extern Repository<Hall> hallRepository;

void HallController::displayHallList() {
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
        displayHallList();
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
    extern vector<Hall*>* halls;
    while (true) {
        ScreenUtility::clearScreen();
        if (!halls->empty()) {
            displayHallList();
            cout << endl;
            cout << "To quit select: -1" << endl;
            cout << "Please select the halls by index: ";
            unsigned int selection;
            cin >> selection;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            if (selection > 0 && selection <= halls->size()) {
                cout << "You have selected Hall " << halls->at(selection - 1)->getId() << endl;
                cout << "Are you sure you want to remove this hall (Y/N): ";
                string input;
                cin >> input;
                while (cin.fail()) {
                    cout << "Please enter characters only";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> input;
                }
                if (toupper(input.at(0)) != 'Y') {
                    cout << "Invalid selection" << endl;
                    ScreenUtility::pause();
                    continue;
                }
                cout << "Hall " << halls->at(selection - 1)->getId() << " successfully deleted" << endl;;
                halls->erase(halls->begin() + selection - 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
                ScreenUtility::pause();
            }
            else if (selection == -1) {
                break;
            }
            else {
                cout << "Invalid option, please try again." << endl;
                ScreenUtility::pause();
            }
        }
        else {
            cout << "No halls currently" << endl;
            break;
        }
    }
     ScreenUtility::pause();
    displayAdminMenu();
}
