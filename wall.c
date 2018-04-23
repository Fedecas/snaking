#include "block.h"
#include "draw.h"
#include "wall.h"

wall WallCreate(int size, int x, int y, int rotation)
{
  wall LevelWall = NULL;

  LevelWall = malloc(sizeof(struct wall));

  LevelWall->size = size;
  LevelWall->rotation = rotation;

  LevelWall->blocksX = malloc(sizeof(int) * LevelWall->size);
  LevelWall->blocksY = malloc(sizeof(int) * LevelWall->size);

  switch (LevelWall->rotation) {
    case WALL_HORIZONTAL:
      for(int i = 0; i < LevelWall->size; i++) {
        LevelWall->blocksX[i] = x + i;
        LevelWall->blocksY[i] = y;
      } break;
    case WALL_VERTICAL:
      for(int i = 0; i < LevelWall->size; i++) {
        LevelWall->blocksX[i] = x;
        LevelWall->blocksY[i] = y + i;
      } break;
    default: break;
  }

  return LevelWall;
}

void WallDraw(SDL_Surface* LevelSurface, wall LevelWall)
{
  for(int i = 0; i < LevelWall->size; i++) {
    BlockDraw(LevelSurface, LevelWall->blocksX[i], LevelWall->blocksY[i], COLOR_WALL, 2);
  }
}

wall WallDestroy(wall LevelWall)
{
  free(LevelWall);
  LevelWall = NULL;

  return LevelWall;
}