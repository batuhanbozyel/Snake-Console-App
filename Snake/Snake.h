#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <iostream>

#define SIZE_X 20
#define SIZE_Y 30

struct Point {
	int x, y;
	bool operator==(const Point& cmp)
	{
		if (x == cmp.x && y == cmp.y)
			return true;
		else
			return false;
	}
	Point& operator=(const Point& tmp)
	{
		x = tmp.x;
		y = tmp.y;
		return *this;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point()
	{
		x = 1;
		y = 1;
	}
};

enum class Direction { LEFT, RIGHT, UP, DOWN };

class SnakeGame {
public:
	void NewGame();
	void SetLevel(int);
private:
	void SpawnFruit();
	void SpawnSnake();
	void ResetMap();
	void Eat();
	void MoveSnake();
	void Input();
	bool isSnake(int, int);
	bool isTail(int, int);
	void PrintMap();
private:
	char map[SIZE_X][SIZE_Y];
	std::vector<Point> snake;
	Point fruit;
	Direction dir = Direction::RIGHT;
	int score = 0;
	int level = 5;
	bool gameOver = false;
};
#endif