CC      = gcc
CFLAGS  = -Wall
LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

TARGET = pacman
SRC    = main.c draw_utils.c player.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
