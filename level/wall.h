#ifndef SNAKING_WALL_H
#define SNAKING_WALL_H

#define WALL_SIZE       (BLOCKS_X - 1)

#define WALL_HORIZONTAL   0 // Rotation of the wall
#define WALL_VERTICAL     1 // Rotation of the wall

typedef struct _wall_t * wall_t;

wall_t* LevelWalls;

void WallsCreate();
/*
 * Initialize the walls and set the parameters in default values
 */

int WallSize(wall_t wall);
/*
 * Return the size of the wall
 */

int* WallBlocksX(wall_t wall);
/*
 * Return the x direction to the first block of wall
 */

int* WallBlocksY(wall_t wall);
/*
 * Return the y direction to the first block of wall
 */

void WallsDraw();
/*
 * Draw the walls of the level
 */

void WallsDestroy();
/*
 * Free the wall's memory
 */

#endif //SNAKING_WALL_H
