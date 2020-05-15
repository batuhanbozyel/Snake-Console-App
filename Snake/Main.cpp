#include <ctime>
#include "Snake.h"
#include "Menu.h"

int main()
{
	srand((unsigned int)time(NULL));
	SnakeGame gameObj;
	Menu MainMenu({ "New Game","Options", "Exit" });
	std::string chooseMain;
	do
	{
		chooseMain = MainMenu.Choose();
		if (chooseMain == "New Game")
		{
			gameObj.NewGame();
		}
		else if (chooseMain == "Options")
		{
			system(clear);
			int level;
			std::cout << "Level (1-10): ";
			std::cin >> level;
			gameObj.SetLevel(level);
		}
	} while (chooseMain != "Exit");
	
	return 0;
}
