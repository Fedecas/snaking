#ifndef SNAKE_BLOCK_H
#define SNAKE_BLOCK_H

#include <SDL2/SDL.h>

#define BLOCK_SIZE  20 // Size in pixels of each block

#define BLOCKS_X    50 // Number of blocks in X
#define BLOCKS_Y    30 // Number of blocks in Y

int BlockInCollision(int x1, int y1, int x2, int y2);
/*
 * Check if the block (x1, y1) is colliding with (x2, y2)
 */

int BlockOutOfLimits(int x, int y);
/*
 * Check if the block in pos (x, y) is inside or outside of the window
 */

void BlockDraw(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y, SDL_Color color, int type);
/*
 * Draw a block of color in the screen
 */

#endif //SNAKE_BLOCK_H