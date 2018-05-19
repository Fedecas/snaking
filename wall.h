#ifndef SNAKE_WALL_H
#define SNAKE_WALL_H

#define WALL_HORIZONTAL   0 // Rotation of the wall
#define WALL_VERTICAL     1 // Rotation of the wall

#define WALLS_IN_LEVEL    4

typedef struct _wall_t * wall_t;

wall_t* WallsCreate();
/*
 * Initialize the walls and set the parameters in default values
 */

int WallSize(wall_t wall);

int* WallBlocksX(wall_t wall);

int* WallBlocksY(wall_t wall);

void WallsDraw(SDL_Surface* surface, wall_t* walls);
/*
 * Draw the walls of the level
 */

wall_t* WallsDestroy(wall_t* walls);
/*
 * Free the wall's memory
 */

#endif //SNAKE_WALL_H
