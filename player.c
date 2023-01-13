#include "player.h"

#include <curses.h>
#include <ncurses.h>

#include "main.h"

#include "draw.h"

#include "map.h"

int player_y = 0;
int player_x = 0;

int player_health = 10;

WINDOW *player_window;
WINDOW *debug_window;

int default_keyhandle() {
	int character = getch();
	switch(character) {
		case '\e':
			end_game("user quit", false);
			break;
	}
	return character;
}

#define PLAYER_STEP_Y 1
#define PLAYER_STEP_X 2

void keyhandle() {
	int going_to_be;
	switch(default_keyhandle()) {
		case 'w':
		case KEY_UP:
			going_to_be = player_y - PLAYER_STEP_Y;
			if(going_to_be < 0 || map_cant_move(going_to_be, player_x) || map_cant_move(going_to_be, player_x+1)) {
				break;
			}
			player_y = going_to_be;
			break;
		case 's':
		case KEY_DOWN:
			going_to_be = player_y + PLAYER_STEP_Y;
			if(going_to_be > MAP_HEIGHT || map_cant_move(going_to_be, player_x) || map_cant_move(going_to_be, player_x+1)) {
				break;
			}
			player_y = going_to_be;
			break;
		case 'a':
		case KEY_LEFT:
			going_to_be = player_x - PLAYER_STEP_X;
			if(going_to_be < 0 || map_cant_move(player_y, going_to_be)) {
				break;
			}
			player_x = going_to_be;
			break;
		case 'd':
		case KEY_RIGHT:
			going_to_be = player_x + PLAYER_STEP_X;
			if(going_to_be > MAP_WIDTH || map_cant_move(player_y, going_to_be)) {
				break;
			}
			player_x = going_to_be;
			break;


		case 'h':
			if(player_health >= 10){
				//player_health = 10;
				keyhandle();
				break;
			}
			player_health += 1;
			break;

		default:
			keyhandle();
	}
}

void player_draw(int y, int x) {
	player_window = newwin(1,2, y, x);

	//wattron(player_window, COLOR_PAIR(MAP_TILE_PLAYER_PAIR));
	//mvwaddch(player_window, 0, 0, MAP_TILE_PLAYER_CHARACTER);
	//mvwaddch(player_window, 0, 1, MAP_TILE_PLAYER_CHARACTER);
	//wattroff(player_window, COLOR_PAIR(MAP_TILE_PLAYER_PAIR));
	
	// much cleaner
	window_rectangle_draw(
			player_window,
			0,0,
			1,2,
			MAP_TILE_PLAYER_CHARACTER,
			MAP_TILE_PLAYER_PAIR
			);

	wnoutrefresh (player_window);
}

void player_camera_draw() {
	int draw_y = player_y;
	int draw_x = player_x;
	int half_width = getmaxx(stdscr) / 2;
	int half_height = getmaxy(stdscr) / 2;

	if(player_y > half_height) {
		draw_y = half_height;
	}
	if(player_x > half_width) {
		draw_x = half_width;
	}
	player_draw(draw_y, draw_x);
}

#define DEBUG_HEIGHT 20
#define DEBUG_WIDTH 50

void player_debug_draw() {
	debug_window = newwin(DEBUG_HEIGHT, DEBUG_WIDTH, getmaxy(stdscr) - DEBUG_HEIGHT, getmaxx(stdscr) - DEBUG_WIDTH);
	mvwprintw(debug_window, 0,0, "%i", player_x);
	mvwprintw(debug_window, 1,0, "%i", player_y);
	mvwprintw(debug_window, 3,0, "%i", screen_width);
	mvwprintw(debug_window, 4,0, "%i", screen_height);
	mvwprintw(debug_window, 6,0, "%i", player_health);
	wnoutrefresh(debug_window);
}


void player_load() {
}

void player_update() {
	player_camera_draw();
	player_debug_draw();
	doupdate();
	keyhandle();
}
