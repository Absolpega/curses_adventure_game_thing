#include "enemy.h"

#include <ncurses.h>
#include <stdlib.h>

#include "draw.h"

#include "map.h"

#include "player.h"

#define enemy_x enemy_map[i][1]
#define enemy_y enemy_map[i][0]

int enemy_map[ENEMY_COUNT][ENEMY_COUNT_EACH] = {
	{
		20, // y
		10, // x
	},
};

WINDOW *enemy_window;

void enemy_draw(int y, int x) {
	enemy_window = newwin(1,2, y, x);

	// much cleaner
	window_rectangle_draw(
			enemy_window,
			0,0,
			1,2,
			MAP_TILE_ENEMY_CHARACTER,
			MAP_TILE_ENEMY_PAIR
			);

	wnoutrefresh (enemy_window);
}

void enemy_camera_draw(int i) {
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
	enemy_draw(enemy_y - offset_y, enemy_x - offset_x);
}

#define ENEMY_STEP_X 2
#define ENEMY_STEP_Y 1

bool enemy_has_move = true;

void enemy_move(int i) {
	if(!enemy_has_move) {
		enemy_has_move = true;
		return;
	}
	enemy_has_move = false;

	int relative_player_x = player_x - enemy_x;
	int relative_player_y = player_y - enemy_y;

	int absolute_relative_player_x = abs(relative_player_x);
	int absolute_relative_player_y = abs(relative_player_y);
	if(absolute_relative_player_x > absolute_relative_player_y) {
		// x axis
		if(relative_player_x * 2 < 0) {
			enemy_x -= ENEMY_STEP_X;
		} else {
			enemy_x += ENEMY_STEP_X;
		}
	} else {
		// y axis
		if(relative_player_y < 0) {
			enemy_y -= ENEMY_STEP_Y;
		} else {
			enemy_y += ENEMY_STEP_Y;
		}
	}
}

void enemy_turn() {
	for(int i = 0; i < ENEMY_COUNT; i+=1) {
		enemy_camera_draw(i);
		enemy_move(i);
	}
}
