#ifndef ACTOR_H
#define ACTOR_H

class actor
{
	int _row, _col;
	char _symbol;

public:

	// Create an actor
	actor(char symbol, int row, int col);

	// Change the actor's position, where _0 is an initial position
	void position(int row_0, int col_0);

	// Get the actor's row (y) and col(x) positions
	int row();
	int col();
	// Get the actor's symbol
	char symbol();
};

#endif

