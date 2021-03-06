#include "hall_controller.h"
#include "repository.h"
#include "hall.h"
#include "menu.h"
#include "show.h"

extern Repository<Hall> hallRepository;
extern Repository<Show> showRepository;

void HallController::displayHallList() {
    extern vector<Hall*>* halls;
    cout << "All Halls: " << endl;
    cout << "==============================" << endl;
    int hallIndex = 1;
    for (Hall* i : *halls) {
        cout << hallIndex << ") " << "Hall " << i->getId() << endl;
        hallIndex++;
    }
}

void HallController::viewHalls() {
	extern vector<Hall*>* halls;
    if (!halls->empty()) {
        while (true) {
            ScreenUtility::clearScreen();
            displayHallList();
            cout << endl;
            cout << "To quit select: -1" << endl;
            cout << "Please select the hall by index: ";
            unsigned int selection;
            cin >> selection;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            if (selection > 0 && selection <= halls->size()) {
                cout << "You have selected " << halls->at(selection - 1)->getId() << endl;
                halls->at(selection - 1)->showSeatingPlan();
                ScreenUtility::pause();
            }
            else if (selection == -1) {
                break;
            }
            else {
                cout << "Invalid option, please try again." << endl;
            }
        }
    }
    else {
        cout << "No halls available" << endl;
    }
    cout << endl;
    ScreenUtility::pause();
}

void HallController::addHalls() {
    extern vector<Hall*>* halls;
    ScreenUtility::clearScreen();
    vector<string> row;
    int rows, cols;
    cout << "Adding Halls..." << endl;
    bool cont = true;
    while (cont) {
        ScreenUtility::clearScreen();
        displayHallList();

        Hall *newHall = new Hall();
        cin >> newHall;

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
}

void HallController::removeHalls() {
    extern vector<Show*>* shows;
    extern vector<Hall*>* halls;
    while (true) {
        ScreenUtility::clearScreen();
        if (!halls->empty()) {
            displayHallList();
            cout << endl << "Which hall would you like to remove?" << endl;
            Hall* hallSelected = promptHallSelection();
            if (hallSelected == nullptr)
                break;
            cout << "You have selected Hall " << hallSelected->getId() << endl;
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

            for (auto& hallPtr : *shows) {
                if (hallPtr->getHallId() == hallSelected->getId()) {
                    delete hallPtr;
                    hallPtr = nullptr;
                }
            }
            shows->erase(remove(shows->begin(), shows->end(), nullptr), shows->end());
            cout << "Hall " << hallSelected->getId() << " successfully deleted" << endl;;
            halls->erase(remove(halls->begin(), halls->end(), hallSelected));
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            ScreenUtility::pause();
        }
        else {
            cout << "No halls currently" << endl;
            break;
        }
    }
    showRepository.save();
    hallRepository.save();
    ScreenUtility::pause();
}

Hall* HallController::promptHallSelection()
{
    extern vector<Hall*>* halls;
    if (!halls->empty()) {
        while (true) {
            cout << "To quit select: -1" << endl;
            cout << "Please select the halls by index: ";
            unsigned int selection;
            cin >> selection;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
            if (selection > 0 && selection <= halls->size()) {
                return halls->at(selection - 1);
            }
            else if (selection == -1) {
                return nullptr;
            }
            else {
                cout << "Invalid option, please try again." << endl;
            }
        }
    }
    return nullptr;
}
