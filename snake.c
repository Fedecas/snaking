#include "draw.h"
#include "snake.h"
#include "window.h"

static int SnakeIsColliding(snake snake, int x, int y)
{
  return BlockInCollision(snake->blocksX[0], snake->blocksY[0], x, y);
}

static void SnakeBodyMove(snake snake)
{
  for (int i = snake->size - 1; i > 0; i--) {
    snake->blocksX[i] = snake->blocksX[i - 1];
    snake->blocksY[i] = snake->blocksY[i - 1];
  }
}

static void SnakeTailDirectionUpdate(snake snake)
{
  int prevIsUpOrDown = snake->blocksX[snake->size - 2] == snake->blocksX[snake->size - 1];

  if(prevIsUpOrDown) {
    int prevIsUp = snake->blocksY[snake->size - 2] == snake->blocksY[snake->size - 1] - 1;

    if(prevIsUp) {
      snake->tailDirection = DIRECTION_UP;
    } else {
      snake->tailDirection = DIRECTION_DOWN;
    }
  } else {
    int prevIsLeft = snake->blocksX[snake->size - 2] == snake->blocksX[snake->size - 1] - 1;

    if(prevIsLeft) {
      snake->tailDirection = DIRECTION_LEFT;
    } else {
      snake->tailDirection = DIRECTION_RIGHT;
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
  snake snake = malloc(sizeof(struct snake));

  snake->headDirection = SNAKE_DIRECTION;
  snake->tailDirection = snake->headDirection;
  snake->size = 1;
  snake->hunger = SNAKE_HUNGER;

  snake->blocksX = malloc(sizeof(int));
  snake->blocksX[0] = SNAKE_SPAWNX;

  snake->blocksY = malloc(sizeof(int));
  snake->blocksY[0] = SNAKE_SPAWNY;

  for(int i = 1; i < SNAKE_SIZE; i++) {
    SnakeIncrease(snake);
  }

  return snake;
}

void SnakeMove(snake snake, int direction)
{
  if(direction != SnakeContraryDirection(snake->headDirection)) {
    snake->headDirection = direction;
  }

  switch (snake->headDirection) {
    case DIRECTION_LEFT:
      SnakeBodyMove(snake);
      snake->blocksX[0] -= 1; break;
    case DIRECTION_RIGHT:
      SnakeBodyMove(snake);
      snake->blocksX[0] += 1; break;
    case DIRECTION_UP:
      SnakeBodyMove(snake);
      snake->blocksY[0] -= 1; break;
    case DIRECTION_DOWN:
      SnakeBodyMove(snake);
      snake->blocksY[0] += 1; break;
    default: break;
  }

  SnakeTailDirectionUpdate(snake);
}

void SnakeIncrease(snake snake)
{
  int oldlastblock = snake->size - 1;

  snake->size++;

  snake->blocksX = realloc(snake->blocksX, sizeof(int) * snake->size);
  snake->blocksY = realloc(snake->blocksY, sizeof(int) * snake->size);

  int newlastblock = snake->size - 1;

  switch (snake->tailDirection) {
    case DIRECTION_LEFT:
      if(snake->blocksX[oldlastblock] < WINDOW_LIMIT_RIGHT - 1) {
        snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] + 1;
        snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      } else {
        if(snake->blocksY[oldlastblock] == WINDOW_LIMIT_UP + 1) {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] + 1;
        } else {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] - 1;
        }
      } break;
    case DIRECTION_RIGHT:
      if(snake->blocksX[oldlastblock] > WINDOW_LIMIT_LEFT + 1) {
        snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] - 1;
        snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      } else {
        if(snake->blocksY[oldlastblock] == WINDOW_LIMIT_UP + 1) {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] + 1;
        } else {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] - 1;
        }
      } break;
    case DIRECTION_UP:
      if(snake->blocksY[oldlastblock] < WINDOW_LIMIT_DOWN - 1) {
        snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
        snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] + 1;
      } else {
        if(snake->blocksX[oldlastblock] == WINDOW_LIMIT_LEFT + 1) {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] + 1;
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
        } else {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] - 1;
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
        }
      } break;
    case DIRECTION_DOWN:
      if(snake->blocksY[oldlastblock] > WINDOW_LIMIT_UP + 1) {
        snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
        snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] - 1;
      } else {
        if(snake->blocksX[oldlastblock] == WINDOW_LIMIT_LEFT + 1) {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] + 1;
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
        } else {
          snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] - 1;
          snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
        }
      } break;
    default: break;
  }

  SnakeTailDirectionUpdate(snake);
}

int SnakeIsCollidingWithFood(snake snake, food food)
{
  return SnakeIsColliding(snake, food->x, food->y);
}

int SnakeIsCollidingWithHerself(snake snake)
{
  for (int i = 1; i < snake->size; ++i) {
    if(SnakeIsColliding(snake, snake->blocksX[i], snake->blocksY[i]))
      return 1;
  }

  return 0;
}

int SnakeIsCollidingWithWall(snake snake, wall wall1, wall wall2, wall wall3, wall wall4)
{
  for(int i = 0; i < wall1->size; i++) {
    if(SnakeIsColliding(snake, wall1->blocksX[i], wall1->blocksY[i]))
      return 1;
  }

  for(int i = 0; i < wall2->size; i++) {
    if(SnakeIsColliding(snake, wall2->blocksX[i], wall2->blocksY[i]))
      return 2;
  }

  for(int i = 0; i < wall3->size; i++) {
    if(SnakeIsColliding(snake, wall3->blocksX[i], wall3->blocksY[i]))
      return 3;
  }

  for(int i = 0; i < wall4->size; i++) {
    if(SnakeIsColliding(snake, wall4->blocksX[i], wall4->blocksY[i]))
      return 4;
  }

  return 0;
}

void SnakeDraw(SDL_Surface* surface, snake snake)
{
  for(int i = 1; i < snake->size; i++) {
    BlockDraw(surface, snake->blocksX[i], snake->blocksY[i], SNAKE_BODY_COLOR, 0);
  }

  BlockDraw(surface, snake->blocksX[0], snake->blocksY[0], SNAKE_HEAD_COLOR, 0);

  // First eye
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Second eye
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Mouth
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(surface, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
}

snake SnakeDestroy(snake snake)
{
  free(snake->blocksX);
  snake->blocksX = NULL;

  free(snake->blocksY);
  snake->blocksY = NULL;

  free(snake);
  snake = NULL;

  return snake;
}