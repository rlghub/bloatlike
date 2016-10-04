#include <ncurses.h>

#include "actor.h"
#include "nscreen.h"
#include "frame.h"

#ifndef MAIN_H
#define MAIN_H

void game_loop(frame &, frame &, actor &, int);

const char * get_player_name();

void handle_hud(frame);

void new_game(nscreen);

int main();

// XXX: Lazy constants to be refactored out later
int hud_width();

#endif

