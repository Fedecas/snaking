#ifndef SNAKE_TERRAIN_H
#define SNAKE_TERRAIN_H

#include <SDL2/SDL_surface.h>

#include "block.h"
#include "draw.h"

#define TERRAIN_X       BLOCK_SIZE
#define TERRAIN_Y       BLOCK_SIZE
#define TERRAIN_WIDTH   ((BLOCKS_X - 2) * BLOCK_SIZE)
#define TERRAIN_HEIGHT  ((BLOCKS_Y - 2) * BLOCK_SIZE)

#define TERRAIN_COLOR   mk_SDL_Color(255, 249, 196, 255)

typedef struct terrain {
    int x;
    int y;
    int width;
    int height;
} terrain;

terrain* TerrainCreate();
/*
 * Initialize the terrain and set the parameters in default values
 */

void TerrainDraw(SDL_Surface* surface, terrain* terrain);
/*
 * Draw the space between the walls
 */

terrain* TerrainDestroy(terrain* terrain);
/*
 * Free the terrain's memory
 */

#endif //SNAKE_TERRAIN_H
