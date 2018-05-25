#include <time.h>

#include "../engine/block.h"
#include "../engine/handlers.h"
#include "../engine/window.h"

#include "snake.h"

struct _snake_t {
    int headDirection;
    int tailDirection;
    int size;
    int hunger;
    int* blocksX;
    int* blocksY;
};

static int SnakeIsColliding(int x, int y)
{
  return BlockInCollision(LevelSnake->blocksX[0], LevelSnake->blocksY[0], x, y);
}

static int SnakeIsCollidingWithFood()
{
  return SnakeIsColliding(FoodPosX(), FoodPosY());
}

static int SnakeIsCollidingWithHerself()
{
  for (int i = 1; i < LevelSnake->size; ++i) {
    if(SnakeIsColliding(LevelSnake->blocksX[i], LevelSnake->blocksY[i]))
      return 1;
  }

  return 0;
}

static int SnakeIsCollidingWithWalls()
{
  for(int i = 0; i < 4; i++) {
    wall_t thiswall = LevelWalls[i];
    int wallsize = WallSize(thiswall);
    int* wallX = WallBlocksX(thiswall);
    int* wallY = WallBlocksY(thiswall);

    for(int j = 0; j < wallsize; j++) {
      int thiswallX = wallX[j];
      int thiswallY = wallY[j];

      if(SnakeIsColliding(thiswallX, thiswallY))
        return 1;
    }
  }

  return 0;
}

static void SnakeBodyMove()
{
  for (int i = LevelSnake->size - 1; i > 0; i--) {
    LevelSnake->blocksX[i] = LevelSnake->blocksX[i - 1];
    LevelSnake->blocksY[i] = LevelSnake->blocksY[i - 1];
  }
}

static void SnakeTailDirectionUpdate()
{
  int prevIsUpOrDown = LevelSnake->blocksX[LevelSnake->size - 2] ==
                       LevelSnake->blocksX[LevelSnake->size - 1];

  if(prevIsUpOrDown) {
    int prevIsUp = LevelSnake->blocksY[LevelSnake->size - 2] ==
                   LevelSnake->blocksY[LevelSnake->size - 1] - 1;

    if(prevIsUp) {
      LevelSnake->tailDirection = DIRECTION_UP;
    } else {
      LevelSnake->tailDirection = DIRECTION_DOWN;
    }
  } else {
    int prevIsLeft = LevelSnake->blocksX[LevelSnake->size - 2] ==
                     LevelSnake->blocksX[LevelSnake->size - 1] - 1;

    if(prevIsLeft) {
      LevelSnake->tailDirection = DIRECTION_LEFT;
    } else {
      LevelSnake->tailDirection = DIRECTION_RIGHT;
    }
  }
}

static int SnakeContraryDirection()
{
  switch (LevelSnake->headDirection) {
    case DIRECTION_LEFT:
      return DIRECTION_RIGHT;
    case DIRECTION_RIGHT:
      return DIRECTION_LEFT;
    case DIRECTION_UP:
      return DIRECTION_DOWN;
    case DIRECTION_DOWN:
      return DIRECTION_UP;
    default:
      return DIRECTION_NONE;
  }
}

void SnakeCreate()
{
  LevelSnake = (snake_t) malloc(sizeof(struct _snake_t));

  srand((unsigned int) time(NULL));

  LevelSnake->headDirection = SNAKE_DIRECTION;
  LevelSnake->tailDirection = LevelSnake->headDirection;
  LevelSnake->size = 1;
  LevelSnake->hunger = SNAKE_HUNGER;

  LevelSnake->blocksX = (int*) malloc(sizeof(int));
  LevelSnake->blocksX[0] = SNAKE_SPAWNX;

  LevelSnake->blocksY = (int*) malloc(sizeof(int));
  LevelSnake->blocksY[0] = SNAKE_SPAWNY;

  for(int i = 1; i < SNAKE_SIZE; i++) {
    SnakeIncrease();
  }
}

void SnakeMove()
{
  if(arrow > DIRECTION_NONE) {
    int contrary = SnakeContraryDirection();

    if(arrow != contrary) {
      LevelSnake->headDirection = arrow;
    }

    SnakeBodyMove();

    switch (LevelSnake->headDirection) {
      case DIRECTION_LEFT:
        LevelSnake->blocksX[0] -= 1; break;
      case DIRECTION_RIGHT:
        LevelSnake->blocksX[0] += 1; break;
      case DIRECTION_UP:
        LevelSnake->blocksY[0] -= 1; break;
      case DIRECTION_DOWN:
        LevelSnake->blocksY[0] += 1; break;
      default: break;
    }

    SnakeTailDirectionUpdate();
  }
}

void SnakeIncrease()
{
  int oldlastblock = LevelSnake->size - 1;

  LevelSnake->size++;

  LevelSnake->blocksX = (int*) realloc(LevelSnake->blocksX, sizeof(int) * LevelSnake->size);
  LevelSnake->blocksY = (int*) realloc(LevelSnake->blocksY, sizeof(int) * LevelSnake->size);

  int newlastblock = LevelSnake->size - 1;

  switch (LevelSnake->tailDirection) {
    case DIRECTION_LEFT:
      LevelSnake->blocksX[newlastblock] = LevelSnake->blocksX[oldlastblock] + 1;
      LevelSnake->blocksY[newlastblock] = LevelSnake->blocksY[oldlastblock];
      break;
    case DIRECTION_RIGHT:
      LevelSnake->blocksX[newlastblock] = LevelSnake->blocksX[oldlastblock] - 1;
      LevelSnake->blocksY[newlastblock] = LevelSnake->blocksY[oldlastblock];
      break;
    case DIRECTION_UP:
      LevelSnake->blocksX[newlastblock] = LevelSnake->blocksX[oldlastblock];
      LevelSnake->blocksY[newlastblock] = LevelSnake->blocksY[oldlastblock] + 1;
      break;
    case DIRECTION_DOWN:
      LevelSnake->blocksX[newlastblock] = LevelSnake->blocksX[oldlastblock];
      LevelSnake->blocksY[newlastblock] = LevelSnake->blocksY[oldlastblock] - 1;
      break;
    default: break;
  }
}

int SnakeCollidingWallOrBody()
{
  // If snake collide with some wall
  if(SnakeIsCollidingWithWalls()) {
    return 1;
  }

  // If snake hit herself
  if(SnakeIsCollidingWithHerself()) {
    return 1;
  }

  return 0;
}

void SnakeEat()
{
  // If snake eat the food
  if(SnakeIsCollidingWithFood()) {
    SoundPlay(EatSound);
    int newsnakehunger = LevelSnake->hunger - 1;

    if(newsnakehunger <= 0) {
      SnakeIncrease();

      newsnakehunger = newsnakehunger + SNAKE_HUNGER;
    }

    LevelSnake->hunger = newsnakehunger;

    FoodDestroy();
    FoodCreate();

    ScoreIncrease();
  }
}

void SnakeDraw()
{
  int x;
  int y;

  for(int i = 1; i < LevelSnake->size; i++) {
    x = LevelSnake->blocksX[i];
    y = LevelSnake->blocksY[i];

    BlockDraw(x, y, COLOR_SNAKE_BODY, 0);
  }

  x = LevelSnake->blocksX[0];
  y = LevelSnake->blocksY[0];
  BlockDraw(x, y, COLOR_SNAKE_HEAD, 0);

  int startfaceX = LevelSnake->blocksX[0] * BLOCK_SIZE;
  int startfaceY = LevelSnake->blocksY[0] * BLOCK_SIZE;

  int eyesize = (BLOCK_SIZE / 6);

  // The eyes
  x = startfaceX + eyesize;
  y = startfaceY + eyesize;
  DrawBox(x, y, eyesize, eyesize, COLOR_BLACK);

  x += 2 * eyesize;
  DrawBox(x, y, eyesize, eyesize, COLOR_BLACK);

  // The mouth
  x -= 2 * eyesize;
  y += 2 * eyesize;
  DrawBox(x, y, 3 * eyesize, eyesize, COLOR_SNAKE_BODY);
}

void SnakeDestroy()
{
  free(LevelSnake->blocksX);
  LevelSnake->blocksX = NULL;

  free(LevelSnake->blocksY);
  LevelSnake->blocksY = NULL;

  free(LevelSnake);
  LevelSnake = NULL;
}