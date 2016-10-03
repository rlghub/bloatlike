#include <ncurses.h>
#include "actor.h"

#ifndef FRAME_H
#define FRAME_H

class frame
{
    // Dimensions of the frame
    int _height, _width;

    // Positions of the frame
    int _row, _col;

    // Declare whether the window is a superwindow (no parent) - FALSE
    // or a subwindow (with a parent) - TRUE
    bool _has_super;

    // Pointer to an ncurses window
    WINDOW *_w;

    // Pointer to an ncurses window
    // Will be null for a superwindow
    // and point to the parent for a subwindow
    WINDOW *_super;

public:

    // Get the window and its parent
    WINDOW *win();
    WINDOW *super();

    // Initialize a superwindow
    frame(int nr_rows, int nr_cols, int row_0, int col_0);

    // Initialize a subwindow with a parent
    frame(frame &parent, int nr_rows, int nr_cols, int row_0, int col_0);
    ~frame();

    // Return true if this window is a subwindow
    bool has_super();

    // Get the dimensions of the window
    int height();
    int width();
    // Get the position of the window
    int row();
    int col();

    // Refresh the window
    void refresh();

    // Move a window to a new position (row, col)
    void move(int row, int col);

    // Place an actor in a window
    void add(actor &x);

    // Add an actor at a specific position to the window
    void add(actor &x, int row_0, int col_0);

    // Define the "erase" character, to clean up the path of actors
    void erase(actor &x);

    // Center the viewport around an actor
    void center(actor &x);

    // Fill the window with "0" and "#" XXX
    // Create a simple map for debugging purposes
    void fill_map();

    void print(const char *message, int row, int col);
};

#endif
