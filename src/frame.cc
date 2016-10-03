#include "frame.h"

// Initialize a superwindow
frame::frame(int nr_rows, int nr_cols, int row_0, int col_0)
{
    _has_super = FALSE;
    _super = NULL;
    _w = newwin(nr_rows, nr_cols, row_0, col_0);
    _height = nr_rows;
    _width = nr_cols;
    _row = row_0;
    _col = col_0;
}

// Initialize a subwindow with a parent
frame::frame(frame &parent, int nr_rows, int nr_cols, int row_0, int col_0)
{
    _has_super = TRUE;
    _super = parent.win();
    _w = derwin(parent.win(), nr_rows, nr_cols, row_0, col_0);
    _height = nr_rows;
    _width = nr_cols;
    _row = row_0;
    _col = col_0;
}

frame::~frame()
{
    delwin(_w);
}

// Place an actor in a window
void frame::add(actor &x)
{
    mvwaddch(_w, x.row(), x.col(), x.symbol());
}

// Define the "erase" character, to clean up the path of actors
void frame::erase(actor &x)
{
    mvwaddch(_w, x.row(), x.col(), '.');
}

// Add an actor at a specific position to the window
void frame::add(actor &x, int row_0, int col_0)
{
    if ((row_0 >= 0 && row_0 < _height) && (col_0 >= 0 && col_0 < _width))
    {
        erase(x);
        mvwaddch(_w, row_0, col_0, x.symbol());
        x.position(row_0, col_0);
    }
}

// Center the viewport around an actor
void frame::center(actor &x)
{
    if (_has_super)
    {
        int row = _row, col = _col, hh, ww;
        int _r = x.row() - _height/2;
        int _c = x.col() - _width/2;

        getmaxyx(_super, hh, ww);

        if (_c + _width >= ww)
        {
            int delta = ww -  (_c + _width);
            col = _c + delta;
        }

        else
            col = _c;

        if (_r + _height >= hh)
        {
            int delta = hh - (_r + _height);
            row = _r + delta;
        }

        else
            row = _r;

        if (_r < 0)
            row = 0;

        if (_c < 0)
            col = 0;

        move(row, col);
    }
}

// Refresh the window
void frame::refresh()
{
    if(_has_super)
        touchwin(_super);
    wrefresh(_w);
}

// Move a window to a new position (row, col)
void frame::move(int row, int col)
{
    if (_super)
    {
        mvderwin(_w, row, col);
        _row = row;
        _col = col;
        refresh();
    }
}

// Get the window
WINDOW* frame::win()
{
	return _w;
}

// Get the parent window
WINDOW* frame::super()
{
	return _super;
}

// Return true if this window is a subwindow
bool frame::has_super()
{
    return _has_super;
}

// Get the dimensions of the window
int frame::height()
{
    return _height;
}

int frame::width()
{
    return _width;
}

// Get the position of the window
int frame::row()
{
    return _row;
}

int frame::col()
{
    return _col;
}

// Fill a map with "0" and "#" XXX
// Simple terrain for debugging purposes
void frame::fill_map()
{
    // Fill the inner region with "."
    for (int y = 0; y < _height; ++y)
    {
        for (int x = 0; x < _width; ++x)
            mvwaddch(_w, y, x, '0');
    }

    // Fill the borders with "#"
    for (int y = 0; y < _height; ++y)
    {
        mvwaddch(_w, y, 0, '#');
        mvwaddch(_w, y, _width - 1, '#');
    }
    for (int x = 0; x < _width; ++x)
    {
        mvwaddch(_w, 0, x, '#');
        mvwaddch(_w, _height - 1, x, '#');
    }
}

void frame::print(const char *message, int row, int col)
{
    mvwprintw(_w, row, col, message);
}
