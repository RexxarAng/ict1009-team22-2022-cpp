#include "menu_item.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "movie_controller.h"
#include "hall_controller.h"
#include "show_controller.h"
#include "booking_controller.h"
#include "movie.h"
#include "menu.h"
#include "screen_utility.h"
using namespace std;

void openMenu(MenuItem* p_menu, unsigned int item_quantity)
{
    unsigned int i = 0;
    // Display the menu
    for (i = 0; i < item_quantity; ++i)
    {
        cout << p_menu[i].number
            << ". "
            << p_menu[i].text
            << "\n";
    }
    cout << endl << "Enter selection: ";
    unsigned int selection;
    cin >> selection;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
    for (i = 0; i < item_quantity; ++i)
    {
        if (selection == p_menu[i].number)
        {
            // Execute the processing function for the selection.
            (p_menu[i].p_processing_function)();
            break;
        }
    }
    if (i >= item_quantity)
    {
        cout << "invalid selection\n";
    }
}


MenuItem main_menu[] =
{
    {1, "View Movies", MovieController::viewMovies},
    {2, "Book Movies", BookingController::bookMovies},
    {3, "View Halls", HallController::viewHalls},
    {4, "Admin", displayAdminMenu},
    {5, "Quit", ScreenUtility::quit}
};

static const unsigned int main_menu_size = sizeof(main_menu) / sizeof(main_menu[0]);

MenuItem admin_main_menu[] =
{
    {1, "Add Movies", MovieController::addMovies},
    {2, "Remove Movies", MovieController::removeMovies},
    {3, "Add Shows", ShowController::addShows},
    {4, "Add Halls", HallController::addHalls},
    {5, "Remove Halls", HallController::removeHalls},
    {6, "Back", displayMainMenu},
    {7, "Quit", ScreenUtility::quit}
};

static const unsigned int admin_menu_size = sizeof(admin_main_menu) / sizeof(admin_main_menu[0]);

void displayMainMenu() {
    while (true) {
        ScreenUtility::clearScreen();
        cout << "Movie Booking System" << endl;
        cout << "==============================" << endl;
        cout << "Main Menu" << endl;
        // Process the menu
        openMenu(&main_menu[0], main_menu_size);
    }
}

void displayAdminMenu() {
    while (true) {
        ScreenUtility::clearScreen();
        cout << "Admin Movie Booking System" << endl;
        cout << "==============================" << endl;
        cout << "Admin Menu" << endl;
        openMenu(&admin_main_menu[0], admin_menu_size);
    }
}

//void clearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}