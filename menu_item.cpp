#include <iostream>
#include "menu_item.h"

using namespace std;

Menu_Item::Menu_Item(unsigned int number, const char* text, Menu_Processing_Function_Ptr p_processing_function) {
	this->number = number;
	this->text = text;
	this->p_processing_function = p_processing_function;
}

