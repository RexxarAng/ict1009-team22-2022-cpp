#include <vector>
#pragma once

typedef void (*MenuProcessingFunctionPtr)();

<<<<<<< Updated upstream
class MenuItem {
=======

class Menu_Item {
>>>>>>> Stashed changes
private:
	unsigned int number;
	const char* text;
	MenuProcessingFunctionPtr p_processing_function;
public:
<<<<<<< Updated upstream
	MenuItem(unsigned int, const char*, MenuProcessingFunctionPtr);
	friend void openMenu(MenuItem *p_menu, unsigned int item_quantity);
};
=======
	Menu_Item(unsigned int, const char*, Menu_Processing_Function_Ptr);
	friend void Menu_Engine(Menu_Item*, unsigned int);
    friend void Menu_Engine(std::vector<Menu_Item>, unsigned int);
};
>>>>>>> Stashed changes
