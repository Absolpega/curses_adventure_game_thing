#include "draw.h"

#include <ncurses.h>

void window_rectangle_draw(WINDOW *window, int y, int x, int height, int width, char character, int color_pair) {
	wattron(window, COLOR_PAIR(color_pair));
	for(int i = 0; i < height; i+=1) {
		for(int j = 0; j < width; j+=1) {
			mvwaddch(window, y+i, x+j, character);
		}
	}
	wattroff(window, COLOR_PAIR(color_pair));
}
