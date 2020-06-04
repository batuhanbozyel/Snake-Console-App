#include "Menu.h"
#include "InputUnix.h"

#include <iostream>

bool Menu::Move(char DIR)
{
	if (DIR == 'w')
	{
		selectedElement--;
		int size = menuElements.size();
		selectedElement = (selectedElement % size + size) % size;
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
		system(clear);
		PrintMenu();
		choice = _getch();
	} while (Move(choice));
	return menuElements[selectedElement];
}

int Menu::ElementID()
{
	return selectedElement;
}