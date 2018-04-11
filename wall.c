#include "wall.h"
#include "window.h"

wall* WallCreate()
{
  wall* wall = NULL;

  wall = malloc(sizeof(struct wall));

  wall->size = WALL_SIZE;

  int index = 0;

  // left wall
  for (int i = 0; i < BLOCKS_Y; i++) {
    wall->blocksX[i] = 0;
    wall->blocksY[i] = i;
  }

  index += BLOCKS_Y;

  // top wall
  for (int i = 0; i < BLOCKS_X; i++) {
    wall->blocksX[i + index] = i;
    wall->blocksY[i + index] = 0;
  }

  index += BLOCKS_X;

  // bottom wall
  for (int i = 0; i < BLOCKS_X; i++) {
    wall->blocksX[i + index] = i;
    wall->blocksY[i + index] = BLOCKS_Y - 1;
  }

  index += BLOCKS_X;

  // right wall
  for (int i = 0; i < BLOCKS_Y; i++) {
    wall->blocksX[i + index] = BLOCKS_X - 1;
    wall->blocksY[i + index] = i;
  }

  return wall;
}

void WallDraw(SDL_Surface* surface, wall* wall)
{
  for(int i = 0; i < wall->size; i++) {
    BlockDraw(surface, wall->blocksX[i], wall->blocksY[i], WALL_COLOR, 0);
  }
}

wall* WallDestroy(wall* wall)
{
  free(wall);
  wall = NULL;

  return wall;
}