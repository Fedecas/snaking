#include "terrain.h"

struct _terrain_t {
    int x;
    int y;
    int width;
    int height;
};

void TerrainCreate()
{
  LevelTerrain = (terrain_t) malloc(sizeof(struct _terrain_t));

  LevelTerrain->x = TERRAIN_X;
  LevelTerrain->y = TERRAIN_Y;
  LevelTerrain->width = TERRAIN_WIDTH;
  LevelTerrain->height = TERRAIN_HEIGHT;
}

void TerrainDraw()
{
  int x = LevelTerrain->x;
  int y = LevelTerrain->y;
  int width = LevelTerrain->width;
  int height = LevelTerrain->height;

  DrawBox(x, y, width, height, COLOR_TERRAIN);
}

void TerrainDestroy()
{
  free(LevelTerrain);
  LevelTerrain = NULL;
}