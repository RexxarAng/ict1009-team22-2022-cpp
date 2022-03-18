#pragma once
typedef void (*Menu_Processing_Function_Ptr)();

class Menu_Item {
private:
	unsigned int number;
	const char* text;
	Menu_Processing_Function_Ptr p_processing_function;
public:
	Menu_Item(unsigned int, const char*, Menu_Processing_Function_Ptr);
	friend void Menu_Engine(Menu_Item*, unsigned int);
};