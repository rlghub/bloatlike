#include <ncurses.h>

#ifndef NSCREEN_H
#define NSCREEN_H

class nscreen
{
    int _height, _width;

public:

    // Initializes the ncurses library
    nscreen();

    // Clears ncurses
    ~nscreen();

    // Print a message on the screen
    void print(const char *message);

    // Get the screen's height and width
    int height();
    int width();
};

#endif

