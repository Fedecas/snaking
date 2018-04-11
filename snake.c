#include "draw.h"
#include "snake.h"
#include "window.h"

static void SnakeBodyMove(snake* snake)
{
  for (int i = snake->size - 1; i > 0; i--) {
    snake->blocksX[i] = snake->blocksX[i - 1];
    snake->blocksY[i] = snake->blocksY[i - 1];
  }
}

static void SnakeTailDirectionUpdate(snake* snake)
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

snake* SnakeCreate()
{
  snake* snake = NULL;

  snake = malloc(sizeof(struct snake));

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

void SnakeMove(snake* snake, int direction)
{
  snake->headDirection = direction;

  int futureheadpos;

  switch (snake->headDirection) {
    case DIRECTION_LEFT:
      futureheadpos = snake->blocksX[0] - 1;
      if(futureheadpos < WINDOW_LIMIT_LEFT + 1) return;
      SnakeBodyMove(snake);
      snake->blocksX[0] = futureheadpos; break;
    case DIRECTION_RIGHT:
      futureheadpos = snake->blocksX[0] + 1;
      if(futureheadpos > WINDOW_LIMIT_RIGHT - 1) return;
      SnakeBodyMove(snake);
      snake->blocksX[0] = futureheadpos; break;
    case DIRECTION_UP:
      futureheadpos = snake->blocksY[0] - 1;
      if(futureheadpos < WINDOW_LIMIT_UP + 1) return;
      SnakeBodyMove(snake);
      snake->blocksY[0] = futureheadpos; break;
    case DIRECTION_DOWN:
      futureheadpos = snake->blocksY[0] + 1;
      if(futureheadpos > WINDOW_LIMIT_DOWN - 1) return;
      SnakeBodyMove(snake);
      snake->blocksY[0] = futureheadpos; break;
    default: break;
  }

  SnakeTailDirectionUpdate(snake);
}

void SnakeIncrease(snake* snake)
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

int SnakeIsColliding(snake* snake, int x, int y)
{
  for (int i = 0; i < snake->size; i++) {
    if(BlockInCollision(snake->blocksX[i], snake->blocksY[i], x, y)) return 1;
  }

  return 0;
}

void SnakeDraw(SDL_Surface* surface, snake* snake)
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

snake* SnakeDestroy(snake* snake)
{
  free(snake->blocksX);
  snake->blocksX = NULL;

  free(snake->blocksY);
  snake->blocksY = NULL;

  free(snake);
  snake = NULL;

  return snake;
}