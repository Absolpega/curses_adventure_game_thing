#include "main.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include "draw.h"

#include "map.h"

#include "player.h"

#include "save.h"

void end_game(const char *message, bool error) {
	endwin();

	//printf("\n%s\n\n", message);
	save_write();

	if(error)
		exit(1);

	exit(0);
}

int main(int argc, char *argv[]) {
	//initscr();
	// force tty
	FILE* tty = fopen("/dev/tty", "r+");
	SCREEN* screen = newterm(NULL, tty, tty);
	set_term(screen);

	noecho(); keypad(stdscr, true); start_color();
	//cbreak();
	//nodelay(stdscr, true);
	raw();

	save_read(argc, argv);

	curs_set(0);

	map_init();

	wnoutrefresh(stdscr);

	while(true) {
		map_camera_draw();
		player_update();
	}

	endwin();
	return 0;
}
