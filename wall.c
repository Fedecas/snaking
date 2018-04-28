#include "block.h"
#include "draw.h"
#include "wall.h"

static wall WallCreate(int size, int x, int y, int rotation)
{
  wall LevelWall = (wall) malloc(sizeof(struct wall));

  LevelWall->size = size;
  LevelWall->rotation = rotation;

  LevelWall->blocksX = (int*) malloc(sizeof(int) * LevelWall->size);
  LevelWall->blocksY = (int*) malloc(sizeof(int) * LevelWall->size);

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

wall* WallsCreate()
{
  wall* LevelWalls = (wall*) malloc(sizeof(struct wall) * WALLS_IN_LEVEL);

  LevelWalls[0] = WallCreate(BLOCKS_Y - 1, 0, 0, WALL_VERTICAL); // Left
  LevelWalls[1] = WallCreate(BLOCKS_Y - 1, BLOCKS_X - 1, 1, WALL_VERTICAL); // Right
  LevelWalls[2] = WallCreate(BLOCKS_X - 1, 1, 0, WALL_HORIZONTAL); // Up
  LevelWalls[3] = WallCreate(BLOCKS_X - 1, 0, BLOCKS_Y - 1, WALL_HORIZONTAL); // Down

  return LevelWalls;
}

static void WallDraw(SDL_Surface* LevelSurface, wall LevelWall)
{
  for(int i = 0; i < LevelWall->size; i++) {
    int thiswallX = LevelWall->blocksX[i];
    int thiswallY = LevelWall->blocksY[i];

    BlockDraw(LevelSurface, thiswallX, thiswallY, COLOR_WALL, 2);
  }
}

void WallsDraw(SDL_Surface* LevelSurface, wall* LevelWalls)
{
  for(int i = 0; i < WALLS_IN_LEVEL; i++) {
    WallDraw(LevelSurface, LevelWalls[i]);
  }
}

static wall WallDestroy(wall LevelWall)
{
  free(LevelWall->blocksX);
  LevelWall->blocksX = NULL;

  free(LevelWall->blocksY);
  LevelWall->blocksY = NULL;

  free(LevelWall);
  LevelWall = NULL;

  return LevelWall;
}

wall* WallsDestroy(wall* LevelWalls)
{
  for(int i = 0; i < WALLS_IN_LEVEL; i++) {
    LevelWalls[i] = WallDestroy(LevelWalls[i]);
  }

  free(LevelWalls);
  LevelWalls = NULL;

  return LevelWalls;
}