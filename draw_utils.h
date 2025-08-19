// draw_utils.h

#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include <SFML/Graphics.h>
#include <stdio.h>

#define CELL_SIZE 20
#define ROWS 30
#define COLS 40

extern int wall[ROWS][COLS];


// Initializes wall array with border walls and internal maze layout
void initMaze();
// void initPellets();

// Draws the maze walls
void drawMaze(sfRenderWindow* window);
void printTest();
void drawScore(sfRenderWindow* window, int score);
// void drawPellets(sfRenderWindow* window);

#endif
