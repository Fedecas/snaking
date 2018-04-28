#include "draw.h"
#include "snake.h"
#include "window.h"

static int SnakeIsColliding(snake PlayerSnake, int x, int y)
{
  return BlockInCollision(PlayerSnake->blocksX[0], PlayerSnake->blocksY[0], x, y);
}

static int SnakeIsCollidingWithFood(snake PlayerSnake, food ActualFood)
{
  return SnakeIsColliding(PlayerSnake, ActualFood->x, ActualFood->y);
}

static int SnakeIsCollidingWithHerself(snake PlayerSnake)
{
  for (int i = 1; i < PlayerSnake->size; ++i) {
    if(SnakeIsColliding(PlayerSnake, PlayerSnake->blocksX[i], PlayerSnake->blocksY[i]))
      return 1;
  }

  return 0;
}

static int SnakeIsCollidingWithWalls(snake PlayerSnake, wall* LevelWalls)
{
  for(int i = 0; i < WALLS_IN_LEVEL; i++) {
    wall thiswall = LevelWalls[i];
    for(int j = 0; j < thiswall->size; j++) {
      int thiswallX = thiswall->blocksX[j];
      int thiswallY = thiswall->blocksY[j];

      if(SnakeIsColliding(PlayerSnake, thiswallX, thiswallY))
        return 1;
    }
  }

  return 0;
}

static void SnakeBodyMove(snake PlayerSnake)
{
  for (int i = PlayerSnake->size - 1; i > 0; i--) {
    PlayerSnake->blocksX[i] = PlayerSnake->blocksX[i - 1];
    PlayerSnake->blocksY[i] = PlayerSnake->blocksY[i - 1];
  }
}

static void SnakeTailDirectionUpdate(snake PlayerSnake)
{
  int prevIsUpOrDown = PlayerSnake->blocksX[PlayerSnake->size - 2] ==
                       PlayerSnake->blocksX[PlayerSnake->size - 1];

  if(prevIsUpOrDown) {
    int prevIsUp = PlayerSnake->blocksY[PlayerSnake->size - 2] ==
                   PlayerSnake->blocksY[PlayerSnake->size - 1] - 1;

    if(prevIsUp) {
      PlayerSnake->tailDirection = DIRECTION_UP;
    } else {
      PlayerSnake->tailDirection = DIRECTION_DOWN;
    }
  } else {
    int prevIsLeft = PlayerSnake->blocksX[PlayerSnake->size - 2] ==
                     PlayerSnake->blocksX[PlayerSnake->size - 1] - 1;

    if(prevIsLeft) {
      PlayerSnake->tailDirection = DIRECTION_LEFT;
    } else {
      PlayerSnake->tailDirection = DIRECTION_RIGHT;
    }
  }
}

static int SnakeContraryDirection(int direction)
{
  switch (direction) {
    case DIRECTION_LEFT:
      return 2;
    case DIRECTION_RIGHT:
      return 1;
    case DIRECTION_UP:
      return 4;
    case DIRECTION_DOWN:
      return 3;
    default:
      return 0;
  }
}

snake SnakeCreate()
{
  snake NewSnake = (snake) malloc(sizeof(struct snake));

  NewSnake->headDirection = SNAKE_DIRECTION;
  NewSnake->tailDirection = NewSnake->headDirection;
  NewSnake->size = 1;
  NewSnake->hunger = SNAKE_HUNGER;

  NewSnake->blocksX = (int*) malloc(sizeof(int));
  NewSnake->blocksX[0] = SNAKE_SPAWNX;

  NewSnake->blocksY = (int*) malloc(sizeof(int));
  NewSnake->blocksY[0] = SNAKE_SPAWNY;

  for(int i = 1; i < SNAKE_SIZE; i++) {
    SnakeIncrease(NewSnake);
  }

  return NewSnake;
}

void SnakeMove(snake PlayerSnake, int direction)
{
  if(direction > DIRECTION_NONE) {
    if(direction != SnakeContraryDirection(PlayerSnake->headDirection)) {
      PlayerSnake->headDirection = direction;
    }

    SnakeBodyMove(PlayerSnake);

    switch (PlayerSnake->headDirection) {
      case DIRECTION_LEFT:
        PlayerSnake->blocksX[0] -= 1; break;
      case DIRECTION_RIGHT:
        PlayerSnake->blocksX[0] += 1; break;
      case DIRECTION_UP:
        PlayerSnake->blocksY[0] -= 1; break;
      case DIRECTION_DOWN:
        PlayerSnake->blocksY[0] += 1; break;
      default: break;
    }

    SnakeTailDirectionUpdate(PlayerSnake);
  }
}

void SnakeIncrease(snake PlayerSnake)
{
  int oldlastblock = PlayerSnake->size - 1;

  PlayerSnake->size++;

  PlayerSnake->blocksX = (int*) realloc(PlayerSnake->blocksX, sizeof(int) * PlayerSnake->size);
  PlayerSnake->blocksY = (int*) realloc(PlayerSnake->blocksY, sizeof(int) * PlayerSnake->size);

  int newlastblock = PlayerSnake->size - 1;

  switch (PlayerSnake->tailDirection) {
    case DIRECTION_LEFT:
      PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] + 1;
      PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
      break;
    case DIRECTION_RIGHT:
      PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] - 1;
      PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
      break;
    case DIRECTION_UP:
      PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
      PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] + 1;
      break;
    case DIRECTION_DOWN:
      PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
      PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] - 1;
      break;
    default: break;
  }
}

int SnakeCollidingWallOrBody(snake PlayerSnake, wall* LevelWalls)
{
  // If snake collide with some wall
  if(SnakeIsCollidingWithWalls(PlayerSnake, LevelWalls)) {
    return 1;
  }

  // If snake hit herself
  if(SnakeIsCollidingWithHerself(PlayerSnake)) {
    return 1;
  }

  return 0;
}

void SnakeEat(snake PlayerSnake, food* ActualFood, score GameScore)
{
  // If snake eat the food
  if(SnakeIsCollidingWithFood(PlayerSnake, *ActualFood)) {
    int newsnakehunger = PlayerSnake->hunger - 1;

    if(newsnakehunger <= 0) {
      SnakeIncrease(PlayerSnake);

      newsnakehunger = newsnakehunger + SNAKE_HUNGER;
    }

    PlayerSnake->hunger = newsnakehunger;

    FoodDestroy(*ActualFood);
    *ActualFood = FoodCreate();

    ScoreIncrease(GameScore);
  }
}

void SnakeDraw(SDL_Surface* LevelSurface, snake PlayerSnake)
{
  for(int i = 1; i < PlayerSnake->size; i++) {
    BlockDraw(LevelSurface, PlayerSnake->blocksX[i], PlayerSnake->blocksY[i], COLOR_SNAKE_BODY, 0);
  }

  BlockDraw(LevelSurface, PlayerSnake->blocksX[0], PlayerSnake->blocksY[0], COLOR_SNAKE_HEAD, 0);

  int startfaceX = PlayerSnake->blocksX[0] * BLOCK_SIZE;
  int startfaceY = PlayerSnake->blocksY[0] * BLOCK_SIZE;

  int eyesize = (BLOCK_SIZE / 6);

  // The eyes
  DrawBox(LevelSurface, startfaceX + eyesize, startfaceY + eyesize,
          eyesize, eyesize, COLOR_BLACK);
  DrawBox(LevelSurface, startfaceX + 3 * eyesize, startfaceY + eyesize,
          eyesize, eyesize, COLOR_BLACK);

  // The mouth
  DrawBox(LevelSurface, startfaceX + eyesize, startfaceY + 3 * eyesize,
          3 * eyesize, eyesize, COLOR_SNAKE_BODY);
}

snake SnakeDestroy(snake PlayerSnake)
{
  free(PlayerSnake->blocksX);
  PlayerSnake->blocksX = NULL;

  free(PlayerSnake->blocksY);
  PlayerSnake->blocksY = NULL;

  free(PlayerSnake);
  PlayerSnake = NULL;

  return PlayerSnake;
}