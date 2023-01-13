#include "ui.h"

#include <ncurses.h>

#include "player.h"

#include "map.h"

#include "draw.h"

#define UI_WINDOW_PLAYER_HEALTH_HEIGHT 1
#define UI_WINDOW_PLAYER_HEALTH_WIDTH 30

WINDOW *ui_window_player_health;

void ui_player_health_init() {
	ui_window_player_health = newwin(1, UI_WINDOW_PLAYER_HEALTH_WIDTH+1, 1, screen_width - UI_WINDOW_PLAYER_HEALTH_WIDTH-3);
}

void ui_player_health() {
	werase(ui_window_player_health);
	window_rectangle_draw(ui_window_player_health, 0, 1, UI_WINDOW_PLAYER_HEALTH_HEIGHT, player_health*3-1, MAP_COLOR_HEALTHBAR_RED_CHARACTER, MAP_COLOR_HEALTHBAR_RED_PAIR);

	for(int i = 0; i < 11; i++) {
		wattron(ui_window_player_health, COLOR_PAIR(MAP_COLOR_HEALTHBAR_BLACK_COLOR));
		mvwaddch(ui_window_player_health, 0, i*3, ' ');
		wattroff(ui_window_player_health, COLOR_PAIR(MAP_COLOR_HEALTHBAR_BLACK_COLOR));
	}

	mvwaddch(ui_window_player_health, 0, 0, '[');
	mvwaddch(ui_window_player_health, 0, UI_WINDOW_PLAYER_HEALTH_WIDTH, ']');
	wnoutrefresh(ui_window_player_health);
}

void ui_draw() {
	ui_player_health();
}
