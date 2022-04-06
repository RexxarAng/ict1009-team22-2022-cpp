#include <iostream>
#include "menu_item.h"

using namespace std;

MenuItem::MenuItem(unsigned int number, const char* text, MenuProcessingFunctionPtr p_processing_function) {
	this->number = number;
	this->text = text;
	this->p_processing_function = p_processing_function;
}

