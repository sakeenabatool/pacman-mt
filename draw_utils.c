// draw_utils.c

#include "draw_utils.h"

int wall[ROWS][COLS];

void printTest(){
    printf("hwllo");
}
void initMaze() {
    // Directly hardcoded maze layout with all ones and zeros
    // 1 = wall, 0 = path
    
    // First initialize the entire array to zeros (empty space)
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            wall[i][j] = 0;
        }
    }

    // UI space buffer - fill top 3 rows and bottom 3 rows with paths (zeros)
    int uiRows = 3;
    
    // Top UI area (rows 0-2) - all paths (zeros)
    int topRows[3][COLS] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    
    for (int i = 0; i < uiRows; i++) {
        for (int j = 0; j < COLS; j++) {
            wall[i][j] = topRows[i][j];
        }
    }
    
    // Bottom UI area (rows ROWS-3 to ROWS-1) - all paths (zeros)
    int bottomRows[3][COLS] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    
    for (int i = 0; i < uiRows; i++) {
        for (int j = 0; j < COLS; j++) {
            wall[ROWS-uiRows+i][j] = bottomRows[i][j];
        }
    }
    
    // Outer border walls (for the game area)
    int row4[COLS] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int row27[COLS] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    
    for (int j = 0; j < COLS; j++) {
        wall[3][j] = row4[j];
        wall[ROWS-4][j] = row27[j];
    }
    
    // Side walls
    for (int i = 4; i < ROWS-4; i++) {
        wall[i][0] = 1;
        wall[i][1] = 1;
        wall[i][COLS-2] = 1;
        wall[i][COLS-1] = 1;
    }
    
    // Top section - Row by row direct assignment
    int row5[COLS] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
    int row6[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1};
    int row7[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1};
    int row8[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1};
    int row9[COLS] = {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1};
    int row10[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1};
    int row11[COLS] = {1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1};
    int row12[COLS] = {1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1};
    
    for (int j = 0; j < COLS; j++) {
        wall[4][j] = row5[j];
        wall[5][j] = row6[j];
        wall[6][j] = row7[j];
        wall[7][j] = row8[j];
        wall[8][j] = row9[j];
        wall[9][j] = row10[j];
        wall[10][j] = row11[j];
        wall[11][j] = row12[j];
    }
    
    // Middle section - Ghost house and surroundings
    int row13[COLS] = {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1};
    int row14[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1};
    int row15[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1};
    int row16[COLS] = {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1};
    int row17[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1};
    int row18[COLS] = {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1};
    int row19[COLS] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
    
    for (int j = 0; j < COLS; j++) {
        wall[12][j] = row13[j];
        wall[13][j] = row14[j];
        wall[14][j] = row15[j];
        wall[15][j] = row16[j];
        wall[16][j] = row17[j];
        wall[17][j] = row18[j];
        wall[18][j] = row19[j];
    }
    
    // Bottom section
    int row20[COLS] = {1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,1,1};
    int row21[COLS] = {1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,1,1};
    int row22[COLS] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
    int row23[COLS] = {1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1};
    int row24[COLS] = {1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1};
    int row25[COLS] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};
    int row26[COLS] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    
    for (int j = 0; j < COLS; j++) {
        wall[19][j] = row20[j];
        wall[20][j] = row21[j];
        wall[21][j] = row22[j];
        wall[22][j] = row23[j];
        wall[23][j] = row24[j];
        wall[24][j] = row25[j];
        wall[25][j] = row26[j];
    }
    
    // Side tunnels
    wall[15][0] = 0;
    wall[15][1] = 0;
    wall[15][COLS-2] = 0;
    wall[15][COLS-1] = 0;
}


void drawMaze(sfRenderWindow* window) {
    sfRectangleShape* rect = sfRectangleShape_create();
    sfVector2f size = {CELL_SIZE, CELL_SIZE};
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfBlue);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (wall[i][j] == 1) {
                sfVector2f pos = {j * CELL_SIZE, i * CELL_SIZE};
                sfRectangleShape_setPosition(rect, pos);
                sfRenderWindow_drawRectangleShape(window, rect, NULL);
            }
        }
    }

    sfRectangleShape_destroy(rect);
}



void drawScore(sfRenderWindow* window, int score) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    sfFont* font = sfFont_createFromFile("Arial.ttf");
    sfText* text = sfText_create();
    sfText_setString(text, scoreText);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 20);
    sfText_setFillColor(text, sfWhite);
    sfVector2f position = {10, 10};
    sfText_setPosition(text, position);
    
    sfRenderWindow_drawText(window, text, NULL);
    
    // Cleanup
    sfText_destroy(text);
    sfFont_destroy(font);
    // Note: In a real application, you might want to keep the font loaded
    // for the lifetime of the application instead of loading it every frame.
    // sfFont_destroy(font); // Uncomment this if you want to destroy the font here
    // sfFont_destroy(font); // Uncomment this if you want to destroy the font here
}

