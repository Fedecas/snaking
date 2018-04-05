#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "block.h"

#define WINDOW_WIDTH   (BLOCKS_X * BLOCK_SIZE) // The X size of the window
#define WINDOW_HEIGHT  (BLOCKS_Y * BLOCK_SIZE) // The Y size of the window

#define WINDOW_LIMIT_LEFT   0               // The minimum block X
#define WINDOW_LIMIT_RIGHT  (BLOCKS_X - 1)  // The maximum block X
#define WINDOW_LIMIT_UP     0               // The minimum block Y
#define WINDOW_LIMIT_DOWN   (BLOCKS_Y - 1)  // The maximum block Y

SDL_Window* windowCreate(SDL_Window* window, int posX, int posY, int width, int height);
/*
 *  Create a window in the posX and posY of the screen with size width * height
 */

SDL_Surface* windowSurfaceColor(SDL_Surface* screenSurface, SDL_Window* window, SDL_Color color);
/*
 * Set the window surface with new color
 */

#endif //SNAKE_WINDOW_H