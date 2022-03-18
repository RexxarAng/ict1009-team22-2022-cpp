#include "menu_item.h"
#include <iostream>

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

//  Forward declarations
void viewMovies();
void viewBookings();
void viewSomething();
void quit();
Menu_Item main_menu[] =
{
    {1, "View Movies", viewMovies},
    {2, "View Bookings", viewBookings},
    {3, "View Something", viewSomething},
    {4, "Quit", quit}
};

void displayMainMenu() {
  
    static const unsigned int main_menu_size = sizeof(main_menu) / sizeof(main_menu[0]);
    cout << "Movie Booking System" << endl;
    cout << "==============================" << endl;
    cout << "Main Menu" << endl;
    // Process the menu
    Menu_Engine(&main_menu[0], main_menu_size);
}


void viewMovies() {
    system("cls");
    cout << "View Movie not implemented yet" << endl;
    
}

void viewBookings() {
    system("cls");
    cout << "View Booking not implemented yet" << endl;
}

void viewSomething() {
    system("cls");
    cout << "Not sure what this is yet" << endl;
}

void quit() {
    cout << "Thank you for using this movie booking system." << endl;
}