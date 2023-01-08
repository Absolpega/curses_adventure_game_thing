#ifndef MAP_H
#define MAP_H

#include <ncurses.h>


#define token_paste(x, y) x##y

#define map_color_generate(base) init_extended_pair(token_paste(base, _PAIR), token_paste(base, _COLOR), token_paste(base, _COLOR))

#define screen_width getmaxx(stdscr)
#define screen_height getmaxy(stdscr)


#define MAP_TILE_PLAYER_COLOR COLOR_BLACK
#define MAP_TILE_PLAYER_PAIR 1
#define MAP_TILE_PLAYER_CHARACTER 'p'

#define MAP_TILE_GRASS_COLOR COLOR_GREEN
#define MAP_TILE_GRASS_PAIR 2
#define MAP_TILE_GRASS_CHARACTER 'g'

#define MAP_TILE_WATER_COLOR COLOR_BLUE
#define MAP_TILE_WATER_PAIR 3
#define MAP_TILE_WATER_CHARACTER 'w'

#define MAP_TILE_MOUNTAIN_COLOR 8
#define MAP_TILE_MOUNTAIN_PAIR 4
#define MAP_TILE_MOUNTAIN_CHARACTER 'm'

#define MAP_TILE_ENEMY_COLOR COLOR_RED
#define MAP_TILE_ENEMY_PAIR 5
#define MAP_TILE_ENEMY_CHARACTER 'e'


#define MAP_HEIGHT 300
#define MAP_WIDTH 600


#define MAP_COUNT_EACH 6
#define MAP_COUNT 3

static const int MAP_MAP[MAP_COUNT][MAP_COUNT_EACH] = {
	{
		10,
		20,
		30,
		60,
		MAP_TILE_WATER_CHARACTER,
		MAP_TILE_WATER_PAIR,
	},
	{
		20,
		90,
		20,
		40,
		MAP_TILE_MOUNTAIN_CHARACTER,
		MAP_TILE_MOUNTAIN_PAIR,
	},
	{
		5,
		10,
		5,
		10,
		MAP_TILE_ENEMY_CHARACTER,
		MAP_TILE_ENEMY_PAIR,
	},
};

#define MAP_COLLIDERS_COUNT 2

static const char MAP_COLLIDERS[MAP_COLLIDERS_COUNT] = {
	'w',
	'm',
};

bool map_cant_move(int y, int x);

void map_camera_draw();

void map_draw(int offset_y, int offset_x);

void map_init();

#endif
