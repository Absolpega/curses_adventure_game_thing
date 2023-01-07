#include "save.h"

#include <stdio.h>

#include "player.h"

void save_write() {
	printf("%i\n%i\n", player_y, player_x);
}

void save_read(int argc, char *argv[]) {
	if(argc == 1) return;

	sscanf(argv[SAVE_FILE_PLAYER_Y], "%i", &player_y);
	sscanf(argv[SAVE_FILE_PLAYER_X], "%i", &player_x);
}
