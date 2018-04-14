#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#include "block.h"

#define WALL_HORIZONTAL   0
#define WALL_VERTICAL     1

#define WALL_COLOR   mk_SDL_Color(96, 125, 139, 255)

typedef struct wall{
    int size;
    int* blocksX;
    int* blocksY;
    int rotation;
} *wall;

wall WallCreate(int size, int x, int y, int rotation);
/*
 * Initialize the walls and set the parameters in default values
 */

void WallDraw(SDL_Surface* surface, wall wall);
/*
 * Draw the walls of the level
 */

wall WallDestroy(wall wall);
/*
 * Free the wall's memory
 */

#endif //SNAKE_WALL_H
