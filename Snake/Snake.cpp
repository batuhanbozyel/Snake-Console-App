#include "Snake.h"
#include "InputUnix.h"

#include <sstream>

//Time Complexity: O(n*m) -> n: map rows | m: map columns
void SnakeGame::ResetMap()
{
	//Initialize Map
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (i == 0 || j == 0 || i == SIZE_X - 1 || j == SIZE_Y - 1)
				map[i][j] = '#';
			else
				map[i][j] = ' ';
		}
	}
}

//Time Complexity: O((n*m)*(n*m)) -> n: map rows | m: map columns
void SnakeGame::NewGame()
{
	gameOver = false;
	dir = Direction::RIGHT;
	score = 0;
	//Reset Snake Status
	while (!snake.empty())
		snake.pop_back();

	ResetMap(); //O(n*m)
	SpawnSnake(); //O(1)
	SpawnFruit(); //O(1)

	//Main Infinite Loop
	while (!gameOver) //O((n*m)*(n*m))
	{
		Input(); //O(1)
		MoveSnake(); //O(n)
		PrintMap(); //O(n*m)
		Sleep(200 / level);
	}
}

//Time Complexity: O(n) -> n: Snake length
void SnakeGame::SpawnFruit()
{
	fruit.x = rand() % (SIZE_X - 2) + 1;
	fruit.y = rand() % (SIZE_Y - 2) + 1;
	if (map[fruit.x][fruit.y] != ' ')
		SpawnFruit();
	else
		map[fruit.x][fruit.y] = 'F';
}

//Time Complexity: O(1)
void SnakeGame::SpawnSnake()
{
	Point point;
	point.x = rand() % (SIZE_X - 3) + 1;
	point.y = rand() % (SIZE_Y - 5) + 1;
	snake.push_back(point);
}

//Time Complexity: O(n*m) -> n: map rows | m: map columns
void SnakeGame::PrintMap()
{
	system(clear);
	map[snake[snake.size() - 1].x][snake[snake.size() - 1].y] = 'O';
	for (int i = 0; i < snake.size() - 1; i++)
		map[snake[i].x][snake[i].y] = 'o';
	
	std::stringstream screenBuffer;
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			screenBuffer << map[i][j] << " ";
		}
		screenBuffer << '\n';
	}
	screenBuffer << "SCORE: " << score;

	std::cout << screenBuffer.str();
}

//Time Complexity: O(1)
void SnakeGame::Eat()
{
	Point point;
	point.x = fruit.x;
	point.y = fruit.y;
	snake.push_back(point);
	score++;
}

//Time Complexity: O(n) -> n: Snake length
void SnakeGame::MoveSnake()
{
	int head = (int)snake.size() - 1;
	map[snake[0].x][snake[0].y] = ' ';
	switch (dir)
	{
	case Direction::LEFT:
		//Move Tail
		for (int i = 0; i < head; i++)
		{
			snake[i] = snake[(size_t)i+1];
		}
		//Move Head
		snake[head].y--;
		//Hitting Wall
		if (snake[head].y < 1)
			gameOver = true;
		else if (isTail(snake[head].x, snake[head].y))
			gameOver = true;
		break;
	case Direction::RIGHT:
		//Move Tail
		for (int i = 0; i < head; i++)
		{
			snake[i] = snake[(size_t)i+1];
		}
		//Move Head
		snake[head].y++;
		//Hitting Wall
		if (snake[head].y > (SIZE_Y - 2))
			gameOver = true;
		else if (isTail(snake[head].x, snake[head].y))
			gameOver = true;
		break;
	case Direction::UP:
		//Move Tail
		for (int i = 0; i < head; i++)
		{
			snake[i] = snake[(size_t)i+1];
		}
		//Move Head
		snake[head].x--;
		//Hitting Wall
		if (snake[head].x < 1)
			gameOver = true;
		else if (isTail(snake[head].x, snake[head].y))
			gameOver = true;
		break;
	case Direction::DOWN:
		//Move Tail
		for (int i = 0; i < head; i++)
		{
			snake[i] = snake[(size_t)i+1];
		}
		//Move Head
		snake[head].x++;
		//Hitting Wall
		if (snake[head].x > (SIZE_X - 2))
			gameOver = true;
		else if (isTail(snake[head].x, snake[head].y))
			gameOver = true;
		break;
	}
	if (snake[head] == fruit)
	{
		Eat();
		SpawnFruit();
	}
}

//Time Complexity: O(1)
void SnakeGame::Input()
{
	if (_kbhit())
	{
		char key = _getch();
		if ((key == 'a' || key == 'A') && dir != Direction::RIGHT)
			dir = Direction::LEFT;
		else if ((key == 'd' || key == 'D') && dir != Direction::LEFT)
			dir = Direction::RIGHT;
		else if ((key == 'w' || key == 'W') && dir != Direction::DOWN)
			dir = Direction::UP;
		else if ((key == 's' || key == 'S') && dir != Direction::UP)
			dir = Direction::DOWN;
	}
}

//Time Complexity: O(1)
bool SnakeGame::isSnake(int x, int y)
{
	return map[x][y] == 'o' || map[x][y] == 'O';
}

//Time Complexity: O(1)
bool SnakeGame::isTail(int x, int y)
{
	return map[x][y] == 'o';
}

//Time Complexity: O(1)
void SnakeGame::SetLevel(int lvl)
{
	level = lvl % 11;
	if (level == 0)
		level = 5;
}