#include "menu_item.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "movie.h"
#include "Menu.h"
using namespace std;

void Menu_Engine(Menu_Item* p_menu, unsigned int item_quantity)
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

Menu_Item main_menu[] =
{
    {1, "View Movies", viewMovies},
    {2, "View Bookings", viewBookings},
    {3, "View Something", viewSomething},
    {4, "Admin", displayAdminMenu},
    {5, "Quit", quit}
};

static const unsigned int main_menu_size = sizeof(main_menu) / sizeof(main_menu[0]);

Menu_Item admin_main_menu[] =
{
    {1, "Add Movies", addMovies},
    {2, "Add Shows", addShows},
    {3, "Back", displayMainMenu},
    {4, "Quit", quit}
};

static const unsigned int admin_menu_size = sizeof(admin_main_menu) / sizeof(admin_main_menu[0]);

void displayMainMenu() {
    system("cls");
    cout << "Movie Booking System" << endl;
    cout << "==============================" << endl;
    cout << "Main Menu" << endl;
    // Process the menu
    Menu_Engine(&main_menu[0], main_menu_size);
}

void displayAdminMenu() {
    system("cls");
    cout << "Admin Movie Booking System" << endl;
    cout << "==============================" << endl;
    cout << "Main Menu" << endl;
    Menu_Engine(&admin_main_menu[0], admin_menu_size);
}