#include "block.h"
#include "draw.h"
#include "wall.h"

struct _wall_t {
    int size;
    int blocksX[WALL_SIZE];
    int blocksY[WALL_SIZE];
    int rotation;
} _wall_t;

static wall_t WallCreate(int size, int x, int y, int rotation)
{
  wall_t LevelWall = (wall_t) malloc(sizeof(_wall_t));

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

wall_t* WallsCreate()
{
  wall_t* LevelWalls = (wall_t*) malloc(sizeof(wall_t) * WALLS_IN_LEVEL);

  LevelWalls[0] = WallCreate(BLOCKS_Y - 1, 0, 0, WALL_VERTICAL); // Left
  LevelWalls[1] = WallCreate(BLOCKS_Y - 1, BLOCKS_X - 1, 1, WALL_VERTICAL); // Right
  LevelWalls[2] = WallCreate(BLOCKS_X - 1, 1, 0, WALL_HORIZONTAL); // Up
  LevelWalls[3] = WallCreate(BLOCKS_X - 1, 0, BLOCKS_Y - 1, WALL_HORIZONTAL); // Down

  return LevelWalls;
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

static void WallDraw(SDL_Surface* LevelSurface, wall_t LevelWall)
{
  for(int i = 0; i < LevelWall->size; i++) {
    int thiswallX = LevelWall->blocksX[i];
    int thiswallY = LevelWall->blocksY[i];

    BlockDraw(LevelSurface, thiswallX, thiswallY, COLOR_WALL, 2);
  }
}

void WallsDraw(SDL_Surface* LevelSurface, wall_t* LevelWalls)
{
  for(int i = 0; i < WALLS_IN_LEVEL; i++) {
    WallDraw(LevelSurface, LevelWalls[i]);
  }
}

static wall_t WallDestroy(wall_t LevelWall)
{
  free(LevelWall);
  LevelWall = NULL;

  return LevelWall;
}

wall_t* WallsDestroy(wall_t* LevelWalls)
{
  for(int i = 0; i < WALLS_IN_LEVEL; i++) {
    LevelWalls[i] = WallDestroy(LevelWalls[i]);
  }

  free(LevelWalls);
  LevelWalls = NULL;

  return LevelWalls;
}