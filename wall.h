#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#include <SDL2/SDL_surface.h>

#include "block.h"
#include "draw.h"

#define WALL_SIZE   ((BLOCKS_X * 2) + (BLOCKS_Y * 2))

#define WALL_COLOR   mk_SDL_Color(96, 125, 139, 255)

typedef struct wall{
    int size;
    int blocksX[WALL_SIZE];
    int blocksY[WALL_SIZE];
} wall;

wall* WallCreate();
/*
 * Initialize the walls and set the parameters in default values
 */

void WallDraw(SDL_Surface* surface, wall* wall);
/*
 * Draw the walls of the level
 */

wall* WallDestroy(wall* wall);
/*
 * Free the wall's memory
 */

#endif //SNAKE_WALL_H
