#ifndef MAIN_H
#define MAIN_H

#define msleep(ms) usleep(ms##000)

#include <stdbool.h>

void end_game(const char *message, bool error);

#endif
