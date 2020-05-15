#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>

extern constexpr char clear[] = "cls";

#else
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <curses.h>

extern constexpr char clear[] = "clear";

int kbhit(void) {

	struct termios oldt, newt;

	int ch;

	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

int _getch() {

	struct termios oldt, newt;

	int ch;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}
#endif
#endif