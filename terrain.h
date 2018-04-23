#ifndef SNAKE_TERRAIN_H
#define SNAKE_TERRAIN_H

#include "block.h"
#include "window.h"

#define TERRAIN_X       BLOCK_SIZE
#define TERRAIN_Y       BLOCK_SIZE
#define TERRAIN_WIDTH   (WINDOW_WIDTH - (2 * BLOCK_SIZE))
#define TERRAIN_HEIGHT  (WINDOW_HEIGHT - (2 * BLOCK_SIZE))

typedef struct terrain {
    int x;
    int y;
    int width;
    int height;
} * terrain;

terrain TerrainCreate();
/*
 * Initialize the terrain and set the parameters in default values
 */

void TerrainDraw(SDL_Surface* LevelSurface, terrain LevelTerrain);
/*
 * Draw the space between the walls
 */

terrain TerrainDestroy(terrain LevelTerrain);
/*
 * Free the terrain's memory
 */

#endif //SNAKE_TERRAIN_H
