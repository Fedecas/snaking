#include "draw.h"
#include "terrain.h"

terrain* TerrainCreate()
{
  terrain* terrain = NULL;

  terrain = malloc(sizeof(struct terrain));

  terrain->x = TERRAIN_X;
  terrain->y = TERRAIN_Y;
  terrain->width = TERRAIN_WIDTH;
  terrain->height = TERRAIN_HEIGHT;

  return terrain;
}

void TerrainDraw(SDL_Surface* surface, terrain* terrain)
{
  DrawBox(surface, terrain->x, terrain->y, terrain->width, terrain->height, TERRAIN_COLOR);
}

terrain* TerrainDestroy(terrain* terrain)
{
  free(terrain);
  terrain = NULL;

  return terrain;
}