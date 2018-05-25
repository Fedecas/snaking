#include "../engine/block.h"
#include "../engine/draw.h"
#include "../engine/window.h"

#include "wall.h"

struct _wall_t {
    int size;
    int blocksX[WALL_SIZE];
    int blocksY[WALL_SIZE];
    int rotation;
};

static wall_t WallCreate(int size, int x, int y, int rotation)
{
  wall_t LevelWall = (wall_t) malloc(sizeof(struct _wall_t));

  LevelWall->size = size;
  LevelWall->rotation = rotation;

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

void WallsCreate()
{
  LevelWalls = (wall_t*) malloc(sizeof(wall_t) * 4);

  LevelWalls[0] = WallCreate(BLOCKS_Y - 1, 0, 0, WALL_VERTICAL); // Left
  LevelWalls[1] = WallCreate(BLOCKS_Y - 1, BLOCKS_X - 1, 1, WALL_VERTICAL); // Right
  LevelWalls[2] = WallCreate(BLOCKS_X - 1, 1, 0, WALL_HORIZONTAL); // Up
  LevelWalls[3] = WallCreate(BLOCKS_X - 1, 0, BLOCKS_Y - 1, WALL_HORIZONTAL); // Down
}

int WallSize(wall_t LevelWall)
{
  return (LevelWall->size);
}

int* WallBlocksX(wall_t LevelWall)
{
  return (LevelWall->blocksX);
}

int* WallBlocksY(wall_t LevelWall)
{
  return (LevelWall->blocksY);
}

static void WallDraw(wall_t LevelWall)
{
  for(int i = 0; i < LevelWall->size; i++) {
    int thiswallX = LevelWall->blocksX[i];
    int thiswallY = LevelWall->blocksY[i];

    BlockDraw(thiswallX, thiswallY, COLOR_WALL, 2);
  }
}

void WallsDraw()
{
  for(int i = 0; i < 4; i++) {
    WallDraw(LevelWalls[i]);
  }
}

static wall_t WallDestroy(wall_t LevelWall)
{
  free(LevelWall);
  LevelWall = NULL;

  return LevelWall;
}

void WallsDestroy()
{
  for(int i = 0; i < 4; i++) {
    LevelWalls[i] = WallDestroy(LevelWalls[i]);
  }

  free(LevelWalls);
  LevelWalls = NULL;
}