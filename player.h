#include "draw_utils.h"
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.h>

#define CELL_SIZE 20

typedef enum {
    DIR_NONE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
} Direction;

typedef struct {
    float posX, posY;
    int gridX, gridY;
    Direction currentDir;
    Direction nextDir;
    float speed;
} Player;

void initPlayer(Player* player, int startX, int startY);
void updatePlayer(Player* player, const int wall[ROWS][COLS]);
void drawPlayer(sfRenderWindow* window, const Player* player);
void setPlayerDirection(Player* player, Direction dir);
void takeInput(Player* player);


#endif
