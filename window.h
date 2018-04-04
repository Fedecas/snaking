#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "block.h"

#define WINDOW_WIDTH   (BLOCKS_X * BLOCK_SIZE)
#define WINDOW_HEIGHT  (BLOCKS_Y * BLOCK_SIZE)

#define WINDOW_LIMIT_UP     0
#define WINDOW_LIMIT_DOWN   (BLOCKS_Y - 1)
#define WINDOW_LIMIT_LEFT   0
#define WINDOW_LIMIT_RIGHT  (BLOCKS_X - 1)

SDL_Window* windowCreate(SDL_Window* window, int posX, int posY, int width, int height);
/*
 *  Create a window in the screen
 */

SDL_Surface* windowSurfaceColor(SDL_Surface* screenSurface, SDL_Window* window, SDL_Color color);
/*
 * Set the window surface with new color
 */

#endif //SNAKE_WINDOW_H