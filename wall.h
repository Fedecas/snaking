#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#define WALL_HORIZONTAL   0 // Rotation of the wall
#define WALL_VERTICAL     1 // Rotation of the wall

#define WALLS_IN_LEVEL    4

typedef struct wall{
    int size;
    int* blocksX;
    int* blocksY;
    int rotation;
} * wall;

wall* WallsCreate();
/*
 * Initialize the walls and set the parameters in default values
 */

void WallsDraw(SDL_Surface* LevelSurface, wall* LevelWalls);
/*
 * Draw the walls of the level
 */

wall* WallsDestroy(wall* LevelWalls);
/*
 * Free the wall's memory
 */

#endif //SNAKE_WALL_H
