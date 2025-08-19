#include <SFML/Graphics.h>
#include "player.h"
#include "draw_utils.h"
//#define ROWS 21
//#define COLS 21



Player pacman;

int startY = ROWS-6;
int startX = COLS/2;
int pelletMap[ROWS][COLS] = {0};
int score = 0;
void drawPellets(sfRenderWindow* window) {
    sfCircleShape* pellet = sfCircleShape_create();
    sfCircleShape_setRadius(pellet, 5);
    sfCircleShape_setFillColor(pellet, sfCyan);

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (pelletMap[y][x]) {
                sfVector2f pos = {x * CELL_SIZE + CELL_SIZE / 2 - 2, y * CELL_SIZE + CELL_SIZE / 2 - 2};
                sfCircleShape_setPosition(pellet, pos);
                sfRenderWindow_drawCircleShape(window, pellet, NULL);
            }
        }
    }
    sfCircleShape_destroy(pellet);
}
void initPellets() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // Place pellet only if it's NOT a wall and not too close to the top
            if (!wall[y][x] && y > 3 && y<=25) {
                pelletMap[y][x] = 1;
            } else {
                pelletMap[y][x] = 0;
            }
        }
    }
}

int main() {
    // Create the window
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Pacman Game", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    // Set frame rate (optional for smoother animation)
    sfRenderWindow_setFramerateLimit(window, 60);

    // Initialize maze
    initMaze();
    initPlayer(&pacman,startX,startY);
    initPellets();

    // Game loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // Clear screen
        sfRenderWindow_clear(window, sfBlack);

        // Draw maze
        drawMaze(window);
        takeInput(&pacman);          // Handle queued direction
        updatePlayer(&pacman, wall); // Update position and direction
        int px = (int)((pacman.posX + CELL_SIZE/2) / CELL_SIZE);
        int py = (int)((pacman.posY + CELL_SIZE/2) / CELL_SIZE);
        
        if (px >= 0 && px < COLS && py >= 0 && py < ROWS && pelletMap[py][px]) {
            pelletMap[py][px] = 0;
            score++;
            printf("Score: %d\n", score);
        }


        drawPlayer(window, &pacman); // Draw Pac-Man
        drawPellets(window); // Draw pellets
         // TODO: Draw Pac-Man, ghosts, pellets, score, etc.
          drawScore(window, score);
        // Display everything
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
