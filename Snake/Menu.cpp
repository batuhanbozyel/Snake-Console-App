#include "Menu.h"
#include "InputUnix.h"
#include <iostream>
#ifdef _WIN32
#define CLEAR system("cls")
#else
#define CLEAR system("clear")
#endif
bool Menu::Move(char DIR)
{
	if (DIR == 'w')
	{
		selectedElement--;
		selectedElement %= menuElements.size();
		return true;
	}
	else if (DIR == 's')
	{
		selectedElement++;
		selectedElement %= menuElements.size();
		return true;
	}
	return false;
}

void Menu::PrintMenu()
{
	for (int i = 0; i < (int)menuElements.size(); i++)
	{
		if (selectedElement == i)
			std::cout << ">" << menuElements[i] << "\n";
		else
			std::cout << "" << menuElements[i] << "\n";
	}
}

std::string Menu::Choose()
{
	char choice;
	do
	{
		CLEAR;
		PrintMenu();
		choice = _getch();
	} while (Move(choice));
	return menuElements[selectedElement];
}

int Menu::ElementID()
{
	return selectedElement;
}