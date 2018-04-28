#include "draw.h"
#include "terrain.h"

terrain TerrainCreate()
{
  terrain LevelTerrain = (terrain) malloc(sizeof(struct terrain));

  LevelTerrain->x = TERRAIN_X;
  LevelTerrain->y = TERRAIN_Y;
  LevelTerrain->width = TERRAIN_WIDTH;
  LevelTerrain->height = TERRAIN_HEIGHT;

  return LevelTerrain;
}

void TerrainDraw(SDL_Surface* LevelSurface, terrain LevelTerrain)
{
  DrawBox(LevelSurface, LevelTerrain->x, LevelTerrain->y,
          LevelTerrain->width, LevelTerrain->height, COLOR_TERRAIN);
}

terrain TerrainDestroy(terrain LevelTerrain)
{
  free(LevelTerrain);
  LevelTerrain = NULL;

  return LevelTerrain;
}