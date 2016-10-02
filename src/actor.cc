#include "actor.h"

// Create an actor
actor::actor(char symbol, int row_0, int col_0)
{
	_symbol = symbol;
	_row = row_0;
	_col = col_0;
}

// Manage changes in the actor's position from _0(initial pos)
void actor::position(int row_0, int col_0)
{
	_row = row_0;
	_col = col_0;
}

// Fetch the actor's row (y) and col (x) positions
int actor::row()
{
	return _row;
}

int actor::col()
{
	return _col;
}

// Fetch the actor's symbol
char actor::symbol()
{
	return _symbol;
}

