#pragma once
#include <iostream>
#include "menu_item.h"

using namespace std;

void Menu_Engine(Menu_Item* p_menu, unsigned int item_quantity);

void displayMainMenu();

void viewMovies();
void viewBookings();
void viewSomething();
void displayAdminMenu();
void displayMainMenu();
void quit();
void addMovies();
void addShows();
void pause();
