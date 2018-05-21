#include "../engine/draw.h"
#include "../engine/window.h"

#include "terrain.h"

struct _terrain_t {
    int x;
    int y;
    int width;
    int height;
} _terrain_t;

terrain_t TerrainCreate()
{
  terrain_t LevelTerrain = (terrain_t) malloc(sizeof(_terrain_t));

  LevelTerrain->x = TERRAIN_X;
  LevelTerrain->y = TERRAIN_Y;
  LevelTerrain->width = TERRAIN_WIDTH;
  LevelTerrain->height = TERRAIN_HEIGHT;

  return LevelTerrain;
}

void TerrainDraw(SDL_Surface* LevelSurface, terrain_t LevelTerrain)
{
  DrawBox(LevelSurface, LevelTerrain->x, LevelTerrain->y,
          LevelTerrain->width, LevelTerrain->height, COLOR_TERRAIN);
}

terrain_t TerrainDestroy(terrain_t LevelTerrain)
{
  free(LevelTerrain);
  LevelTerrain = NULL;

  return LevelTerrain;
}