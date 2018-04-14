#include "draw.h"
#include "wall.h"

wall WallCreate(int size, int x, int y, int rotation)
{
  wall wall = NULL;

  wall = malloc(sizeof(struct wall));

  wall->size = size;
  wall->rotation = rotation;

  wall->blocksX = malloc(sizeof(int) * wall->size);
  wall->blocksY = malloc(sizeof(int) * wall->size);

  switch (wall->rotation) {
    case WALL_HORIZONTAL:
      for(int i = 0; i < wall->size; i++) {
        wall->blocksX[i] = x + i;
        wall->blocksY[i] = y;
      } break;
    case WALL_VERTICAL:
      for(int i = 0; i < wall->size; i++) {
        wall->blocksX[i] = x;
        wall->blocksY[i] = y + i;
      } break;
    default: break;
  }

  return wall;
}

void WallDraw(SDL_Surface* surface, wall wall)
{
  for(int i = 0; i < wall->size; i++) {
    BlockDraw(surface, wall->blocksX[i], wall->blocksY[i], WALL_COLOR, 2);
  }
}

wall WallDestroy(wall wall)
{
  free(wall);
  wall = NULL;

  return wall;
}