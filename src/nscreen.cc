#include "nscreen.h"

// Initializes the ncurses library
nscreen::nscreen()
{
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

	// Get the screen's dimensions
	getmaxyx(stdscr, _height, _width);
}

// Clear ncurses
nscreen::~nscreen()
{
	endwin();
}

// Print a message on the screen
void nscreen::add(const char *message)
{
	printw(message);
}

// Get the screen's height and width
int nscreen::height()
{
	return _height;
}

int nscreen::width()
{
	return _width;
}

