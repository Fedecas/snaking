#ifndef SNAKE_BLOCK_H
#define SNAKE_BLOCK_H

#define BLOCK_SIZE  20 // Size in pixels of each block

#define BLOCKS_X    50 // Number of blocks in X
#define BLOCKS_Y    30 // Number of blocks in Y

int BlockInCollision(int x1, int y1, int x2, int y2);
/*
 * Check if the block (block1X, block1Y) is colliding with (block2X, block2Y)
 */

#endif //SNAKE_BLOCK_H