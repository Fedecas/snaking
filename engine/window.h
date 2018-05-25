#ifndef SNAKING_WINDOW_H
#define SNAKING_WINDOW_H

#include <SDL2/SDL.h>

#include "block.h"

#define WINDOW_TITLE  "Snaking Alpha" // Title of the window

#define WINDOW_POSX   SDL_WINDOWPOS_UNDEFINED // The X position where create a window
#define WINDOW_POSY   SDL_WINDOWPOS_UNDEFINED // The Y position where create a window

#define WINDOW_WIDTH    (BLOCKS_X * BLOCK_SIZE) // The X size of the window in pixels
#define WINDOW_HEIGHT   (BLOCKS_Y * BLOCK_SIZE) // The Y size of the window in pixels

#define WINDOW_LIMIT_LEFT   0               // The minimum block X
#define WINDOW_LIMIT_RIGHT  (BLOCKS_X - 1)  // The maximum block X
#define WINDOW_LIMIT_UP     0               // The minimum block Y
#define WINDOW_LIMIT_DOWN   (BLOCKS_Y - 1)  // The maximum block Y

typedef struct _window_t * window_t;

window_t GameWindow;

void WindowAndSurfaceInit();
/*
 * Create a window in WINDOW_POSX and WINDOW_POSY,
 * of size (WINDOW_WIDTH * WINDOW_HEIGHT),
 * with title WINDOW_TITLE
 */

surface_t WindowSurface();
/*
 * Return the direction to the surface of window
 */

void WindowSurfaceUpdate();
/*
 * Update the surface of the window
 */

void WindowAndSurfaceQuit();
/*
 * Free the surface and destroy the window
 */

#endif //SNAKING_WINDOW_H