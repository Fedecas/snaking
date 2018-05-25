#ifndef SNAKING_BLOCK_H
#define SNAKING_BLOCK_H

#include "draw.h"

#define BLOCK_SIZE  24 // Size in pixels of each block

#define BLOCKS_X    53 // Number of blocks in X
#define BLOCKS_Y    30 // Number of blocks in Y

#define BLOCK_FLAT   0 // Draw flat block
#define BLOCK_BORDER 1 // Draw block with black border
#define BLOCK_VOLUME 2 // Draw block simulating volume

int BlockInCollision(int x1, int y1, int x2, int y2);
/*
 * Check if the block (x1, y1) is colliding with (x2, y2)
 */

int BlockOutOfLimits(int x, int y);
/*
 * Check if the block in pos (x, y) is inside or outside of the window
 */

void BlockDraw(int x, int y, color_t color, int type);
/*
 * Draw a block of color in the screen
 */

#endif //SNAKING_BLOCK_H