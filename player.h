#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>

extern int player_y;
extern int player_x;

extern WINDOW *debug_window;

void player_update();

void player_load();

#endif
