COMPILER = gcc

COMPILER_FLAGS  = -Og -Wall

LIBRARY_FLAGS = -lncurses

BINARY = binary

SOURCE = main.c draw.c map.c player.c save.c

all: $(SOURCE)
	$(COMPILER) $(COMPILER_FLAGS) -o $(BINARY) $(SOURCE) $(LIBRARY_FLAGS)
