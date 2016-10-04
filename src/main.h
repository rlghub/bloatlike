#include <string>
#include <ncurses.h>

#include "actor.h"
#include "frame.h"

#ifndef MAIN_H
#define MAIN_H

void game_loop(frame &, frame &, actor &, int);

std::string get_player_name();

void handle_hud(frame);

void new_game();

int main();

void init_ncurses();
void clear_ncurses();

#endif

