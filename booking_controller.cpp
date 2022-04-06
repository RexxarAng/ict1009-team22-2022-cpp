#include "booking_controller.h"
#include "show_controller.h"
#include "repository.h"
#include "screen_utility.h"

extern Repository<Show> showRepository;

void BookingController::bookMovies() {
	extern vector<Show*>* shows;
	ScreenUtility::clearScreen();
	if (!shows->empty()) {
		while (true) {
			ShowController::displayShowList();
			Show* selectedShow = ShowController::promptShowSelection();
			if (selectedShow == nullptr)
				break;
			cout << "You have selected " << selectedShow->getTitle() << " " << selectedShow->getTime() << endl;
            promptSeatSelection(selectedShow);
		}
	}
	else {
		cout << "There is no showtimes vailable" << endl;
	} 
	ScreenUtility::pause();
}


void BookingController::promptSeatSelection(Show* selectedShow) {
    while (true) {
        selectedShow->showHallSeatingPlan();
        cout << "==============================" << endl;
        cout << "Book any seat numbers" << endl;
        cout << "q) Back" << endl;
        cout << "Please select the option:";
        string selection;
        cin >> selection;
        if (cin.fail()) {
            cin.clear(); // get rid of failure state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printColor("ERROR -- Invalid option\n", 2);
            ScreenUtility::pause();
        }
        else if (tolower(selection.at(0)) == 'q') {
            ScreenUtility::clearScreen();
            break;
        }
        else {
            if (selection.size() < 2) {
                printColor("ERROR -- Invalid seat number, please try again\n", 2);
                ScreenUtility::pause();
            }
            int column = (int)(unsigned char)selection[0] - (int)('A');
            int row = stoi(selection.substr(1, selection.size() - 1));

            cout << "Booking " << column << ":" << row << endl;
            if (selectedShow->getHall()->bookSeat(column, row)) {
                printColor("You have booked " + selection + "\n");
                showRepository.save();
                ScreenUtility::pause();
            }
            else {
                printColor("Invalid option : " + selection + ", Please try again.\n", 2);
                ScreenUtility::pause();
            }
        }
    }
   
}