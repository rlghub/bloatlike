#include <ncurses.h>

#include "actor.h"
#include "nscreen.h"
#include "frame.h"

void game_loop(frame &level_map, frame &viewport, actor &p_act, int ch)
{
    // Check if our user wants to play
    if(ch == 'q' || ch =='Q')
        return;

    // Place our actor in the level map and center the viewport over @
    level_map.add(p_act);
    viewport.center(p_act);
    viewport.refresh();
    
    while (1)
    {
        ch = getch();

        if (ch == 'h' || ch == 'H' || ch == KEY_LEFT || ch == '4')
        {
            level_map.add(p_act, p_act.row(), p_act.col() - 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'l' || ch == 'L' || ch == KEY_RIGHT || ch == '6')
        {
            level_map.add(p_act, p_act.row(), p_act.col() + 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'k' || ch == 'K' || ch == KEY_UP || ch == '8')
        {
            level_map.add(p_act, p_act.row() - 1, p_act.col());
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'j' || ch == 'J' || ch == KEY_DOWN || ch == '2')
        {
            level_map.add(p_act, p_act.row() + 1, p_act.col());
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'y' || ch == 'Y' || ch == '7')
        {
            level_map.add(p_act, p_act.row() - 1, p_act.col() - 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'u' || ch == 'U' || ch == '9')
        {
            level_map.add(p_act, p_act.row() - 1, p_act.col() + 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'b' || ch == 'B' || ch == '1')
        {
            level_map.add(p_act, p_act.row() + 1, p_act.col() - 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        if (ch == 'n' || ch == 'N' || ch == '3')
        {
            level_map.add(p_act, p_act.row() + 1, p_act.col() + 1);
            viewport.center(p_act);
            viewport.refresh();
        }
        else if(ch == 'q' || ch == 'Q')
            break;
    }
}

// Get the player's name XXX: currently a constant
const char * get_player_name()
{
    return "Player";
}

// Prints out information in the right-hand pane
void handle_hud(frame hud)
{
    // Get the player's name and print it out at the top of the pane
    hud.print(get_player_name(), 0, 2);
    hud.refresh();
}

// Constant width of the HUD XXX: need to handle for tinyterms!
int hud_width()
{
    return 20;
}

void new_game(nscreen scr)
{
    // Greet the user
    scr.add("Welcome.\nPress the any key to play.\nPress [q] to quit!\n");

    // Wait for user input
    int ch = getch();

    // Initialize our windows

    // Create a window for the level's map
    frame level_map(scr.height(), scr.width(), 0, 0);

    // Create a subwindow for the viewport
    frame viewport(level_map, scr.height() - 6, scr.width() - 20, 0, 0);
   
    // Create a frame for the HUD, we will use the right-hand pane for this
    frame hud(scr.height(), hud_width(), 0, scr.width() - 20);

    // Manage the HUD
    handle_hud(hud);

    // Create our player actor
    // Set initial position as the center of the map for now
    actor p_act('@', level_map.height()/2, level_map.width()/2);

    // Create our debug terrain XXX
    level_map.fill_map();

    // Run the game loop
    game_loop(level_map, viewport, p_act, ch);
}

int main()
{
    // Initialize the ncurses display, scr
    nscreen scr;

    // Start a new game
    new_game(scr);

    return 0;
}
