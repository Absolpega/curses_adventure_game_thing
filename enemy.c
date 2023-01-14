#include "enemy.h"

#include <ncurses.h>
#include <stdlib.h>

#include "draw.h"

#include "map.h"

#include "player.h"

#define enemy_y						enemy_map[i][0]
#define enemy_x						enemy_map[i][1]
#define enemy_has_move				enemy_map[i][2]
#define enemy_player_behind_wall	enemy_map[i][3]

#define ENEMY_COUNT_EACH 4
#define ENEMY_COUNT 2

int enemy_map[ENEMY_COUNT][ENEMY_COUNT_EACH] = {
	{
		20, // y
		10, // x
		true, // has move
		false, // player behind wall
	},
	{
		10, // y
		10, // x
		false, // has move
		false, // player behind wall
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

void enemy_move(int i) {
	int relative_player_x = player_x - enemy_x;
	int relative_player_y = player_y - enemy_y;

	int absolute_relative_player_x = abs(relative_player_x);
	int absolute_relative_player_y = abs(relative_player_y);

	if(
			absolute_relative_player_x <= 2 &&
			absolute_relative_player_y <= 1
		) {
		if(player_health == 0) return;

		player_health -= 1;
		return;
	}



	if(!enemy_has_move) {
		enemy_has_move = true;
		return;
	}
	enemy_has_move = false;


	//bool cant_go_up		= false;
	//bool cant_go_down	= false;
	//bool cant_go_right	= false;
	//bool cant_go_left	= false;

	int going_to_be_up		= 0;
	int going_to_be_down	= 0;
	int going_to_be_left	= 0;
	int going_to_be_right	= 0;

	bool go_preference_up		= 0;
	bool go_preference_down		= 0;
	bool go_preference_left		= 0;
	bool go_preference_right	= 0;

	
	{
		// left
		going_to_be_left = enemy_x - ENEMY_STEP_X;

		go_preference_left = 1;

		if(going_to_be_left < 0 || map_cant_move(enemy_y, going_to_be_left)) {
			go_preference_left = 0;
		}
	}
	{
		// right
		going_to_be_right = enemy_x + ENEMY_STEP_X;

		go_preference_right = 1;

		if(going_to_be_right > MAP_WIDTH || map_cant_move(enemy_y, going_to_be_right)) {
			go_preference_right = 0;
		}
	}

	{
		// up
		going_to_be_up = enemy_y - ENEMY_STEP_Y;

		go_preference_up = 1;

		if(going_to_be_up < 0 || map_cant_move(going_to_be_up, enemy_x) || map_cant_move(going_to_be_up, enemy_x+1)) {
			go_preference_up = 0;
		}
	}
	{
		// down
		going_to_be_down = enemy_y + ENEMY_STEP_Y;

		go_preference_down = 1;

		if(going_to_be_down > MAP_HEIGHT || map_cant_move(going_to_be_down, enemy_x) || map_cant_move(going_to_be_down, enemy_x+1)) {
			go_preference_down = 0;
		}
	}
	
	if(absolute_relative_player_x > absolute_relative_player_y) {
		// x axis
		if(relative_player_x * 2 < 0) {
			// left
			if(go_preference_left == 0)
				return;
			enemy_x = going_to_be_left;
		} else {
			// right
			if(go_preference_right == 0)
				return;
			enemy_x = going_to_be_right;
		}
	} else {
		// y axis
		if(relative_player_y < 0) {
			// up
			if(go_preference_up == 0)
				return;
			enemy_y = going_to_be_up;
		} else {
			// down
			if(go_preference_down == 0)
				return;
			enemy_y = going_to_be_down;
		}
	}
}

void enemy_turn() {
	for(int i = 0; i < ENEMY_COUNT; i+=1) {
		enemy_camera_draw(i);
		enemy_move(i);
	}
}
