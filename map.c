#include "map.h"

#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

#include "draw.h"

#include "player.h"

WINDOW *map_window;

void map_draw(int offset_y, int offset_x) {
	window_rectangle_draw(map_window, 0, 0, MAP_HEIGHT, MAP_WIDTH, 'g', MAP_TILE_GRASS_PAIR);
	for(int i = 0; i < MAP_COUNT; i+=1) {
		window_rectangle_draw(
				map_window,
				MAP_MAP[i][0], //- offset_y,	// y
				MAP_MAP[i][1], //- offset_x,	// x
				MAP_MAP[i][2],				// height
				MAP_MAP[i][3],				// width
				MAP_MAP[i][4],				// character
				MAP_MAP[i][5]				// pair
				);
	}
	pnoutrefresh(
			map_window,
			offset_y,
			offset_x,
			0,
			0,
			screen_height - 1,
			screen_width - 1
			);
}

bool map_cant_move(int y, int x) {
	unsigned char character = mvwinch(map_window, y, x);
	for(int i = 0; i < MAP_COLLIDERS_COUNT; i++) {
		if(character == MAP_COLLIDERS[i]) 
			return true;
	}
	return false;
}
		


void map_camera_draw() {
	int offset_y = 0;
	int offset_x = 0;
	int half_width = screen_width / 2;
	int half_height = screen_height / 2;
	if(player_y > half_height) {
		offset_y = player_y - half_height;
	}
	if(player_x > half_width) {
		offset_x = player_x - half_width;
	}
	map_draw(offset_y, offset_x);
}


void map_init() {
	map_window = newpad(MAP_HEIGHT, MAP_WIDTH);

	map_color_generate(MAP_TILE_PLAYER);
	map_color_generate(MAP_TILE_GRASS);
	map_color_generate(MAP_TILE_WATER);
	map_color_generate(MAP_TILE_MOUNTAIN);
	map_color_generate(MAP_TILE_ENEMY);
}



