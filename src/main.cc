#include <ncurses.h>
#include <curses.h>
#include <string>

#include "main.h"
#include "actor.h"
#include "frame.h"

/* A few definitions to set up and explain the minimum terminal size
   21 + 1 + 58 = 80
    7 + 1 + 16 = 24 */
// Size of the HUD (right-hand pane) display
#define HUD_WIDTH 21
// Size of the message log (bottom-pane) display
#define LOG_HEIGHT 7
// Size of the border between the viewport and the above displays
#define BORDER_SIZE 1
/* Minimum size of the viewport (mostly arbitrary, adds with the above
   to the "standard" terminal size of 80x24) */
#define VIEW_MINWIDTH 58
#define VIEW_MINHEIGHT 16

// Entry point of the program!
int main()
{
    // Initialize the ncurses display, scr
    init_ncurses();
    
    // Check if this screen is large enough for the game
    if (COLS < (VIEW_MINWIDTH + HUD_WIDTH + BORDER_SIZE)
        || LINES < (VIEW_MINHEIGHT + LOG_HEIGHT + BORDER_SIZE))
    {
        clear_ncurses();
        printf("This game needs a terminal size of at least 80x24 to run!\n"
               "Please adjust your terminal size and try again.\n");

    }
    else if (COLS >= (VIEW_MINWIDTH + HUD_WIDTH + BORDER_SIZE)
             && (LINES >= (VIEW_MINHEIGHT + LOG_HEIGHT + BORDER_SIZE)))
    {
        // Start a new game
        new_game();
    }

    clear_ncurses();

    return 0;
}

// Summon the ncurses
void init_ncurses()
{
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// Abolish ncurses
void clear_ncurses()
{
    endwin();
}

void new_game()
{
    refresh();
    // Create a window for the new game screen.
    frame game_menu(LINES, COLS, 0, 0);

    // Greet the user
    game_menu.print("Welcome.\nPress the [enter] key to play.\n"
                    "Press [q] to quit!\n", 0, 0);
    game_menu.refresh();

    int ch;

    while (1)
    {
        ch = getch();

        if (ch == '\r' || ch == '\n' || ch == 'q' || ch == 'Q')
            break;
    }

    // Initialize our windows
    refresh();

    // Create a window for the level's map
    frame level_map(LINES, COLS, 0, 0);

    // Create a subwindow for the viewport
    frame viewport(level_map, LINES - (LOG_HEIGHT + BORDER_SIZE),
            COLS - (HUD_WIDTH + BORDER_SIZE), 0, 0);
   
    // Create a frame for the HUD, we will use the right-hand pane for this
    frame hud(LINES, HUD_WIDTH, 0, COLS - HUD_WIDTH);

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

// Prints out information in the right-hand pane
void handle_hud(frame hud)
{
    // Get the player's name and print it out at the top of the pane
    hud.print(get_player_name(), 0, 0);
    hud.refresh();
}

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

// XXX: Constants we will be using temporarily for testing purposes

std::string get_player_name()
{
    return "Player";
}

