#include "draw.h"
#include "snake.h"
#include "window.h"

static int SnakeIsColliding(snake PlayerSnake, int x, int y)
{
  return BlockInCollision(PlayerSnake->blocksX[0], PlayerSnake->blocksY[0], x, y);
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
  int prevIsUpOrDown = PlayerSnake->blocksX[PlayerSnake->size - 2] == PlayerSnake->blocksX[PlayerSnake->size - 1];

  if(prevIsUpOrDown) {
    int prevIsUp = PlayerSnake->blocksY[PlayerSnake->size - 2] == PlayerSnake->blocksY[PlayerSnake->size - 1] - 1;

    if(prevIsUp) {
      PlayerSnake->tailDirection = DIRECTION_UP;
    } else {
      PlayerSnake->tailDirection = DIRECTION_DOWN;
    }
  } else {
    int prevIsLeft = PlayerSnake->blocksX[PlayerSnake->size - 2] == PlayerSnake->blocksX[PlayerSnake->size - 1] - 1;

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
  snake NewSnake = malloc(sizeof(struct snake));

  NewSnake->headDirection = SNAKE_DIRECTION;
  NewSnake->tailDirection = NewSnake->headDirection;
  NewSnake->size = 1;
  NewSnake->hunger = SNAKE_HUNGER;

  NewSnake->blocksX = malloc(sizeof(int));
  NewSnake->blocksX[0] = SNAKE_SPAWNX;

  NewSnake->blocksY = malloc(sizeof(int));
  NewSnake->blocksY[0] = SNAKE_SPAWNY;

  for(int i = 1; i < SNAKE_SIZE; i++) {
    SnakeIncrease(NewSnake);
  }

  return NewSnake;
}

void SnakeMove(snake PlayerSnake, int direction)
{
  if(direction != SnakeContraryDirection(PlayerSnake->headDirection)) {
    PlayerSnake->headDirection = direction;
  }

  switch (PlayerSnake->headDirection) {
    case DIRECTION_LEFT:
      SnakeBodyMove(PlayerSnake);
      PlayerSnake->blocksX[0] -= 1; break;
    case DIRECTION_RIGHT:
      SnakeBodyMove(PlayerSnake);
      PlayerSnake->blocksX[0] += 1; break;
    case DIRECTION_UP:
      SnakeBodyMove(PlayerSnake);
      PlayerSnake->blocksY[0] -= 1; break;
    case DIRECTION_DOWN:
      SnakeBodyMove(PlayerSnake);
      PlayerSnake->blocksY[0] += 1; break;
    default: break;
  }

  SnakeTailDirectionUpdate(PlayerSnake);
}

void SnakeIncrease(snake PlayerSnake)
{
  int oldlastblock = PlayerSnake->size - 1;

  PlayerSnake->size++;

  PlayerSnake->blocksX = realloc(PlayerSnake->blocksX, sizeof(int) * PlayerSnake->size);
  PlayerSnake->blocksY = realloc(PlayerSnake->blocksY, sizeof(int) * PlayerSnake->size);

  int newlastblock = PlayerSnake->size - 1;

  switch (PlayerSnake->tailDirection) {
    case DIRECTION_LEFT:
      if(PlayerSnake->blocksX[oldlastblock] < WINDOW_LIMIT_RIGHT - 1) {
        PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] + 1;
        PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
      } else {
        if(PlayerSnake->blocksY[oldlastblock] == WINDOW_LIMIT_UP + 1) {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] + 1;
        } else {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] - 1;
        }
      } break;
    case DIRECTION_RIGHT:
      if(PlayerSnake->blocksX[oldlastblock] > WINDOW_LIMIT_LEFT + 1) {
        PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] - 1;
        PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
      } else {
        if(PlayerSnake->blocksY[oldlastblock] == WINDOW_LIMIT_UP + 1) {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] + 1;
        } else {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] - 1;
        }
      } break;
    case DIRECTION_UP:
      if(PlayerSnake->blocksY[oldlastblock] < WINDOW_LIMIT_DOWN - 1) {
        PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
        PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] + 1;
      } else {
        if(PlayerSnake->blocksX[oldlastblock] == WINDOW_LIMIT_LEFT + 1) {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] + 1;
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
        } else {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] - 1;
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
        }
      } break;
    case DIRECTION_DOWN:
      if(PlayerSnake->blocksY[oldlastblock] > WINDOW_LIMIT_UP + 1) {
        PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock];
        PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock] - 1;
      } else {
        if(PlayerSnake->blocksX[oldlastblock] == WINDOW_LIMIT_LEFT + 1) {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] + 1;
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
        } else {
          PlayerSnake->blocksX[newlastblock] = PlayerSnake->blocksX[oldlastblock] - 1;
          PlayerSnake->blocksY[newlastblock] = PlayerSnake->blocksY[oldlastblock];
        }
      } break;
    default: break;
  }

  SnakeTailDirectionUpdate(PlayerSnake);
}

int SnakeIsCollidingWithFood(snake PlayerSnake, food ActualFood)
{
  return SnakeIsColliding(PlayerSnake, ActualFood->x, ActualFood->y);
}

int SnakeIsCollidingWithHerself(snake PlayerSnake)
{
  for (int i = 1; i < PlayerSnake->size; ++i) {
    if(SnakeIsColliding(PlayerSnake, PlayerSnake->blocksX[i], PlayerSnake->blocksY[i])) {
      printf("block: %d\n", i);
      return 1;
    }
  }

  return 0;
}

int SnakeIsCollidingWithWall(snake PlayerSnake, wall wall1, wall wall2, wall wall3, wall wall4)
{
  for(int i = 0; i < wall1->size; i++) {
    if(SnakeIsColliding(PlayerSnake, wall1->blocksX[i], wall1->blocksY[i]))
      return 1;
  }

  for(int i = 0; i < wall2->size; i++) {
    if(SnakeIsColliding(PlayerSnake, wall2->blocksX[i], wall2->blocksY[i]))
      return 2;
  }

  for(int i = 0; i < wall3->size; i++) {
    if(SnakeIsColliding(PlayerSnake, wall3->blocksX[i], wall3->blocksY[i]))
      return 3;
  }

  for(int i = 0; i < wall4->size; i++) {
    if(SnakeIsColliding(PlayerSnake, wall4->blocksX[i], wall4->blocksY[i]))
      return 4;
  }

  return 0;
}

void SnakeDraw(SDL_Surface* LevelSurface, snake PlayerSnake)
{
  for(int i = 1; i < PlayerSnake->size; i++) {
    BlockDraw(LevelSurface, PlayerSnake->blocksX[i], PlayerSnake->blocksY[i], COLOR_SNAKE_BODY, 0);
  }

  BlockDraw(LevelSurface, PlayerSnake->blocksX[0], PlayerSnake->blocksY[0], COLOR_SNAKE_HEAD, 0);

  // First eye
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Second eye
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Mouth
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 12, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 13, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 14, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 15, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 8, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 9, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 10, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 11, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 8, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 9, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 10, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 11, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 8, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 9, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 10, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 11, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 8, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 9, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 10, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 11, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 4, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 5, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 6, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(LevelSurface, PlayerSnake->blocksX[0]*BLOCK_SIZE + 7, PlayerSnake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
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