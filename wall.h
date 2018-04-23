#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#define WALL_HORIZONTAL   0 // Rotation of the wall
#define WALL_VERTICAL     1 // Rotation of the wall

typedef struct wall{
    int size;
    int* blocksX;
    int* blocksY;
    int rotation;
} * wall;

wall WallCreate(int size, int x, int y, int rotation);
/*
 * Initialize the walls and set the parameters in default values
 */

void WallDraw(SDL_Surface* LevelSurface, wall LevelWall);
/*
 * Draw the walls of the level
 */

wall WallDestroy(wall LevelWall);
/*
 * Free the wall's memory
 */

#endif //SNAKE_WALL_H
