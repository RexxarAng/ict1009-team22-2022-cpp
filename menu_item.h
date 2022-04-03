#pragma once

typedef void (*MenuProcessingFunctionPtr)();

class MenuItem {
private:
	unsigned int number;
	const char* text;
	MenuProcessingFunctionPtr p_processing_function;
public:
	MenuItem(unsigned int, const char*, MenuProcessingFunctionPtr);
	friend void openMenu(MenuItem *p_menu, unsigned int item_quantity);
};