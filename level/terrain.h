#ifndef SNAKING_TERRAIN_H
#define SNAKING_TERRAIN_H

#include "../engine/window.h"

#define TERRAIN_X       BLOCK_SIZE
#define TERRAIN_Y       BLOCK_SIZE
#define TERRAIN_WIDTH   (WINDOW_WIDTH - (2 * BLOCK_SIZE))
#define TERRAIN_HEIGHT  (WINDOW_HEIGHT - (2 * BLOCK_SIZE))

typedef struct _terrain_t * terrain_t;

terrain_t LevelTerrain;

void TerrainCreate();
/*
 * Initialize the terrain and set the parameters in default values
 */

void TerrainDraw();
/*
 * Draw the space between the walls
 */

void TerrainDestroy();
/*
 * Free the terrain's memory
 */

#endif //SNAKING_TERRAIN_H
