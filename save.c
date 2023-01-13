#include "save.h"

#include <stdio.h>

#include "player.h"

#define SAVE_FILE_PLAYER_Y 1
#define SAVE_FILE_PLAYER_X 2
#define SAVE_FILE_PLAYER_HEALTH 3

void save_write() {
	printf("%i\n%i\n%i\n", player_y, player_x, player_health);
}

void save_read(int argc, char *argv[]) {
	if(argc == 1) return;

	sscanf(argv[SAVE_FILE_PLAYER_Y], "%i", &player_y);
	sscanf(argv[SAVE_FILE_PLAYER_X], "%i", &player_x);
	sscanf(argv[SAVE_FILE_PLAYER_HEALTH], "%i", &player_health);
}
