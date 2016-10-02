#include <ncurses.h>
#include "actor.h"
#include "nscreen.h"

// Erase characters which would be left behind
void erase(int row, int col)
{
	mvaddch(row, col, ' ');
}

void move_actor(int row, int col, char symbol)
{
	for(;;)
	{
		int ch = getch();

		if (ch == 'h' || ch == 'H' || ch == KEY_LEFT || ch == '4')
		{
			erase(row, col);
			col = col - 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'l' || ch == 'L' || ch == KEY_RIGHT || ch == '6')
		{
			erase(row, col);
			col = col + 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'k' || ch == 'K' || ch == KEY_UP || ch == '8')
		{
			erase(row, col);
			row = row - 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'j' || ch == 'J' || ch == KEY_DOWN || ch == '2')
		{
			erase(row, col);
			row = row + 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'y' || ch == 'Y' || ch == '7')
		{
			erase(row, col);
			row = row - 1;
			col = col - 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'u' || ch == 'U' || ch == '9')
		{
			erase(row, col);
			row = row - 1;
			col = col + 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'b' || ch == 'B' || ch == '1')
		{
			erase(row, col);
			row = row + 1;
			col = col - 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		if (ch == 'n' || ch == 'N' || ch == '3')
		{
			erase(row, col);
			row = row + 1;
			col = col + 1;
			mvaddch(row, col, symbol);
			refresh();
		}
		else if(ch == 'q' || ch == 'Q')
			break;
	}
}

void game_loop(int ch)
{
	// Check if our user wants to play
	if(ch == 'q' || ch =='Q') return;

	// Create our actor, we'll put it at (10,10) for now
	actor p_act('@', 10, 10);

	mvaddch(p_act.row(), p_act.col(), p_act.symbol());

	// Allow movement!
	move_actor(p_act.row(), p_act.col(), p_act.symbol());
}

void new_game(nscreen scr)
{
	// Greet the user
	scr.add("Welcome.\nPress the any key to play.\nPress [q] to quit!\n");

	// Wait for user input then scrub
	int ch = getch();
	clear();

	// Run the game loop
	game_loop(ch);
}

int main()
{
	// Initialize the ncurses display and give it the shorthand "scr"
	nscreen scr;

	// Start a new game
	new_game(scr);

	return 0;
}
