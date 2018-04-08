#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "block.h"

#define WINDOW_TITLE  "Snaking Alpha v0.5.1" // Title of the window

#define WINDOW_POSX   SDL_WINDOWPOS_UNDEFINED // The X position where create a window
#define WINDOW_POSY   SDL_WINDOWPOS_UNDEFINED // The Y position where create a window

#define WINDOW_WIDTH    (BLOCKS_X * BLOCK_SIZE) // The X size of the window
#define WINDOW_HEIGHT   (BLOCKS_Y * BLOCK_SIZE) // The Y size of the window

#define WINDOW_LIMIT_LEFT   0               // The minimum block X
#define WINDOW_LIMIT_RIGHT  (BLOCKS_X - 1)  // The maximum block X
#define WINDOW_LIMIT_UP     0               // The minimum block Y
#define WINDOW_LIMIT_DOWN   (BLOCKS_Y - 1)  // The maximum block Y

SDL_Window* WindowCreate();
/*
 * Create a window in WINDOW_POSX and WINDOW_POSY,
 * of size (WINDOW_WIDTH * WINDOW_HEIGHT),
 * with title WINDOW_TITLE
 */

#endif //SNAKE_WINDOW_H