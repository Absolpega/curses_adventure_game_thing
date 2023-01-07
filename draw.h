#ifndef DRAW_ENGINE_H
#define DRAW_ENGINE_H

#include <ncurses.h>

void window_rectangle_draw(WINDOW *window, int y, int x, int height, int width, char character, int color_pair);

#endif
