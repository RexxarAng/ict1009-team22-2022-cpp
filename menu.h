#pragma once
#include <iostream>
#include "menu_item.h"
#include "actions.h"

using namespace std;

<<<<<<< Updated upstream
void openMenu(MenuItem* p_menu, unsigned int item_quantity);

=======
void Menu_Engine(Menu_Item* p_menu, unsigned int item_quantity);
void Menu_Engine(vector<Menu_Item> p_menu, unsigned int item_quantity);
>>>>>>> Stashed changes
void displayMainMenu();

//void viewMovies();
//void viewBookings();
//void viewSomething();
//void loadMovies();

void displayAdminMenu();
void displayMainMenu();
//void quit();
//void addMovies();
void addShows();
void addHalls();
//void pause();
//void clearScreen();
