#include "draw.h"
#include "wall.h"

wall* WallCreate()
{
  wall* wall = NULL;

  wall = malloc(sizeof(struct wall));

  wall->size = WALL_SIZE;

  int index = 0;

  // Left wall
  for (int i = 0; i < BLOCKS_Y; i++) {
    wall->blocksX[i] = 0;
    wall->blocksY[i] = i;
  }

  index += BLOCKS_Y;

  // Top wall
  for (int i = 0; i < BLOCKS_X; i++) {
    wall->blocksX[i + index] = i;
    wall->blocksY[i + index] = 0;
  }

  index += BLOCKS_X;

  // Bottom wall
  for (int i = 0; i < BLOCKS_X; i++) {
    wall->blocksX[i + index] = i;
    wall->blocksY[i + index] = BLOCKS_Y - 1;
  }

  index += BLOCKS_X;

  // Right wall
  for (int i = 0; i < BLOCKS_Y; i++) {
    wall->blocksX[i + index] = BLOCKS_X - 1;
    wall->blocksY[i + index] = i;
  }

  return wall;
}

void WallDraw(SDL_Surface* surface, wall* wall)
{
  for(int i = 0; i < wall->size; i++) {
    BlockDraw(surface, wall->blocksX[i], wall->blocksY[i], WALL_COLOR, 2);
  }
}

wall* WallDestroy(wall* wall)
{
  free(wall);
  wall = NULL;

  return wall;
}