#ifndef SNAKE_TERRAIN_H
#define SNAKE_TERRAIN_H

#include "../engine/block.h"
#include "../engine/window.h"

#define TERRAIN_X       BLOCK_SIZE
#define TERRAIN_Y       BLOCK_SIZE
#define TERRAIN_WIDTH   (WINDOW_WIDTH - (2 * BLOCK_SIZE))
#define TERRAIN_HEIGHT  (WINDOW_HEIGHT - (2 * BLOCK_SIZE))

typedef struct _terrain_t * terrain_t;

terrain_t TerrainCreate();
/*
 * Initialize the terrain and set the parameters in default values
 */

void TerrainDraw(SDL_Surface* surface, terrain_t terrain);
/*
 * Draw the space between the walls
 */

terrain_t TerrainDestroy(terrain_t terrain);
/*
 * Free the terrain's memory
 */

#endif //SNAKE_TERRAIN_H
