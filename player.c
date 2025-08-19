#include "player.h"
#include "draw_utils.h"
#include <math.h>
#include <SFML/Window/Keyboard.h>

void initPlayer(Player* player, int startX, int startY) {
    player->gridX = startX;
    player->gridY = startY;
    player->posX = startX * CELL_SIZE;
    player->posY = startY * CELL_SIZE;
    player->currentDir = DIR_NONE;
    player->nextDir = DIR_NONE;
    player->speed = 2.0f;
}

void setPlayerDirection(Player* player, Direction dir) {
    player->nextDir = dir;
}

// void updatePlayer(Player* p, const int wall[ROWS][COLS]) {
//     // 1) Tunnel wrap
//     if (p->currentDir == DIR_LEFT && p->posX <= 0) {
//         p->posX = (COLS - 1) * CELL_SIZE;
//     } else if (p->currentDir == DIR_RIGHT && p->posX >= (COLS - 1) * CELL_SIZE) {
//         p->posX = 0;
//     }
//     // 2) Compute current grid cell
//     int gx = (int)(p->posX / CELL_SIZE);
//     int gy = (int)(p->posY / CELL_SIZE);
//     // 3) Alignment & direction switch
//     float mx = fmodf(p->posX, CELL_SIZE);
//     float my = fmodf(p->posY, CELL_SIZE);
//     int alignedX = (mx < p->speed || mx > CELL_SIZE - p->speed);
//     int alignedY = (my < p->speed || my > CELL_SIZE - p->speed);
//     if (alignedX && alignedY && p->nextDir != DIR_NONE) {
//         int nx = gx, ny = gy;
//         if (p->nextDir == DIR_UP)    ny--;
//         if (p->nextDir == DIR_DOWN)  ny++;
//         if (p->nextDir == DIR_LEFT)  nx--;
//         if (p->nextDir == DIR_RIGHT) nx++;
//         if (wall[ny][nx] == 0) {
//             p->currentDir = p->nextDir;
//             p->posX = gx * CELL_SIZE;
//             p->posY = gy * CELL_SIZE;
//             // recompute mx, my after snapping
//             mx = my = 0;
//         }
//     }
//     // 4) Look ahead
//     int tx = gx, ty = gy;
//     if (p->currentDir == DIR_UP)    ty--;
//     if (p->currentDir == DIR_DOWN)  ty++;
//     if (p->currentDir == DIR_LEFT)  tx--;
//     if (p->currentDir == DIR_RIGHT) tx++;
//     // 5) Move or clamp
//     switch (p->currentDir) {
//         case DIR_RIGHT: {
//             if (wall[gy][gx+1]) {
//                 // If already exactly at boundary, just stop
//                 if (mx <= 0.0001f) {
//                     p->currentDir = DIR_NONE;
//                 } else {
//                     float remaining = CELL_SIZE - mx;
//                     if (p->speed < remaining) {
//                         p->posX += p->speed;
//                     } else {
//                         p->posX += remaining;
//                         p->currentDir = DIR_NONE;
//                     }
//                 }
//             } else {
//                 p->posX += p->speed;
//             }
//             break;
//         }
//         case DIR_LEFT: {
//             if (wall[gy][gx-1]) {
//                 if (mx <= 0.0001f) {
//                     p->currentDir = DIR_NONE;
//                 } else {
//                     float remaining = mx;
//                     if (p->speed < remaining) {
//                         p->posX -= p->speed;
//                     } else {
//                         p->posX -= remaining;
//                         p->currentDir = DIR_NONE;
//                     }
//                 }
//             } else {
//                 p->posX -= p->speed;
//             }
//             break;
//         }
//         case DIR_DOWN: {
//             if (wall[gy+1][gx]) {
//                 if (my <= 0.0001f) {
//                     p->currentDir = DIR_NONE;
//                 } else {
//                     float remaining = CELL_SIZE - my;
//                     if (p->speed < remaining) {
//                         p->posY += p->speed;
//                     } else {
//                         p->posY += remaining;
//                         p->currentDir = DIR_NONE;
//                     }
//                 }
//             } else {
//                 p->posY += p->speed;
//             }
//             break;
//         }
//         case DIR_UP: {
//             if (wall[gy-1][gx]) {
//                 if (my <= 0.0001f) {
//                     p->currentDir = DIR_NONE;
//                 } else {
//                     float remaining = my;
//                     if (p->speed < remaining) {
//                         p->posY -= p->speed;
//                     } else {
//                         p->posY -= remaining;
//                         p->currentDir = DIR_NONE;
//                     }
//                 }
//             } else {
//                 p->posY -= p->speed;
//             }
//             break;
//         }
//         default:
//             break;
//     }
// }

void updatePlayer(Player* p, const int wall[ROWS][COLS]) {
    // 1) Tunnel wrap - LEFT to RIGHT
    if (p->currentDir == DIR_LEFT && p->posX <= 0) {
        p->posX = (COLS - 1) * CELL_SIZE;
    } 
    // Tunnel wrap - RIGHT to LEFT
    else if (p->currentDir == DIR_RIGHT && p->posX >= (COLS - 1) * CELL_SIZE) {
        p->posX = 0;
    }

    // 2) Compute current grid cell
    int gx = (int)(p->posX / CELL_SIZE);
    int gy = (int)(p->posY / CELL_SIZE);

    // 3) Alignment & direction switch
    float mx = fmodf(p->posX, CELL_SIZE);
    float my = fmodf(p->posY, CELL_SIZE);
    int alignedX = (mx < p->speed || mx > CELL_SIZE - p->speed);
    int alignedY = (my < p->speed || my > CELL_SIZE - p->speed);

    if (alignedX && alignedY && p->nextDir != DIR_NONE) {
        int nx = gx, ny = gy;
        if (p->nextDir == DIR_UP)    ny--;
        if (p->nextDir == DIR_DOWN)  ny++;
        if (p->nextDir == DIR_LEFT)  nx--;
        if (p->nextDir == DIR_RIGHT) nx++;
        if (wall[ny][nx] == 0) {
            p->currentDir = p->nextDir;
            p->posX = gx * CELL_SIZE;
            p->posY = gy * CELL_SIZE;
            // recompute mx, my after snapping
            mx = my = 0;
        }
    }

    // 4) Look ahead
    int tx = gx, ty = gy;
    if (p->currentDir == DIR_UP)    ty--;
    if (p->currentDir == DIR_DOWN)  ty++;
    if (p->currentDir == DIR_LEFT)  tx--;
    if (p->currentDir == DIR_RIGHT) tx++;

    // 5) Move or clamp
    switch (p->currentDir) {
        case DIR_RIGHT: {
            if (wall[gy][gx+1]) {
                // If already exactly at boundary, just stop
                if (mx <= 0.0001f) {
                    p->currentDir = DIR_NONE;
                } else {
                    float remaining = CELL_SIZE - mx;
                    if (p->speed < remaining) {
                        p->posX += p->speed;
                    } else {
                        p->posX += remaining;
                        p->currentDir = DIR_NONE;
                    }
                }
            } else {
                p->posX += p->speed;
            }
            break;
        }
        case DIR_LEFT: {
            if (wall[gy][gx-1]) {
                if (mx <= 0.0001f) {
                    p->currentDir = DIR_NONE;
                } else {
                    float remaining = mx;
                    if (p->speed < remaining) {
                        p->posX -= p->speed;
                    } else {
                        p->posX -= remaining;
                        p->currentDir = DIR_NONE;
                    }
                }
            } else {
                p->posX -= p->speed;
            }
            break;
        }
        case DIR_DOWN: {
            if (wall[gy+1][gx]) {
                if (my <= 0.0001f) {
                    p->currentDir = DIR_NONE;
                } else {
                    float remaining = CELL_SIZE - my;
                    if (p->speed < remaining) {
                        p->posY += p->speed;
                    } else {
                        p->posY += remaining;
                        p->currentDir = DIR_NONE;
                    }
                }
            } else {
                p->posY += p->speed;
            }
            break;
        }
        case DIR_UP: {
            if (wall[gy-1][gx]) {
                if (my <= 0.0001f) {
                    p->currentDir = DIR_NONE;
                } else {
                    float remaining = my;
                    if (p->speed < remaining) {
                        p->posY -= p->speed;
                    } else {
                        p->posY -= remaining;
                        p->currentDir = DIR_NONE;
                    }
                }
            } else {
                p->posY -= p->speed;
            }
            break;
        }
        default:
            break;
    }
}



void drawPlayer(sfRenderWindow* window, const Player* player) {
    sfCircleShape* pacman = sfCircleShape_create();
    float radius = CELL_SIZE / 2.5f;
    sfCircleShape_setRadius(pacman, radius);
    sfCircleShape_setFillColor(pacman, sfYellow);

    sfVector2f position = {
        player->posX + CELL_SIZE / 2.0f - radius,
        player->posY + CELL_SIZE / 2.0f - radius
    };
    sfCircleShape_setPosition(pacman, position);

    sfRenderWindow_drawCircleShape(window, pacman, NULL);
    sfCircleShape_destroy(pacman);
}


void takeInput(Player* player) {
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        setPlayerDirection(player, DIR_UP);
    } else if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        setPlayerDirection(player, DIR_DOWN);
    } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        setPlayerDirection(player, DIR_LEFT);
    } else if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        setPlayerDirection(player, DIR_RIGHT);
    }
}
