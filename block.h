#ifndef SNAKE_BLOCK_H
#define SNAKE_BLOCK_H

#define BLOCK_SIZE  20 // Size in pixels of each block

#define BLOCKS_X    50 // Number of blocks in X
#define BLOCKS_Y    30 // Number of blocks in Y

int blockInCollision(int block1X, int block1Y, int block2X, int block2Y);
/*
 * Check if the block (block1X, block1Y) is colliding with (block2X, block2Y)
 */

#endif //SNAKE_BLOCK_H