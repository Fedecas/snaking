#include <SDL2/SDL.h>

#include "draw.h"
#include "snake.h"
#include "window.h"

static void SnakeBodyMove(struct snake* snake, int copyX, int copyY)
{
  int auxX, auxY;

  for(int i = 1; i < snake->size; i++) {
    auxX = snake->blocksX[i];
    auxY = snake->blocksY[i];

    snake->blocksX[i] = copyX;
    snake->blocksY[i] = copyY;

    copyX = auxX;
    copyY = auxY;
  }
}

struct snake* SnakeCreate()
{
  struct snake* snake = NULL;

  snake = malloc(sizeof(struct snake));

  snake->direction = SNAKE_DIRECTION;
  snake->size = 1;
  snake->hunger = SNAKE_HUNGER;
  snake->blocksX[0] = SNAKE_SPAWNX;
  snake->blocksY[0] = SNAKE_SPAWNY;

  for(int i = 1; i < SNAKE_SIZE; i++) {
    SnakeIncrease(snake);
  }

  return snake;
}

void SnakeMove(struct snake* snake, int direction)
{
  snake->direction = direction;

  int copyX = snake->blocksX[0];
  int copyY = snake->blocksY[0];

  int futureheadpos;

  switch (direction) {
    case DIRECTION_LEFT:
      futureheadpos = snake->blocksX[0] - 1;
      if(futureheadpos < WINDOW_LIMIT_LEFT + 1) break;
      snake->blocksX[0] = futureheadpos;
      SnakeBodyMove(snake, copyX, copyY); break;
    case DIRECTION_RIGHT:
      futureheadpos = snake->blocksX[0] + 1;
      if(futureheadpos > WINDOW_LIMIT_RIGHT - 1) break;
      snake->blocksX[0] = futureheadpos;
      SnakeBodyMove(snake, copyX, copyY); break;
    case DIRECTION_UP:
      futureheadpos = snake->blocksY[0] - 1;
      if(futureheadpos < WINDOW_LIMIT_UP + 1) break;
      snake->blocksY[0] = futureheadpos;
      SnakeBodyMove(snake, copyX, copyY); break;
    case DIRECTION_DOWN:
      futureheadpos = snake->blocksY[0] + 1;
      if(futureheadpos > WINDOW_LIMIT_DOWN - 1) break;
      snake->blocksY[0] = futureheadpos;
      SnakeBodyMove(snake, copyX, copyY); break;
    default: break;
  }
}

void SnakeIncrease(struct snake* snake)
{
  if(snake->size == SNAKE_MAX_BLOCKS) goto end;

  int oldlastblock = snake->size - 1;

  snake->size++;

  int newlastblock = snake->size - 1;

  switch (snake->direction) {
    case DIRECTION_LEFT:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] - 1;
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      break;
    case DIRECTION_RIGHT:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] + 1;
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      break;
    case DIRECTION_UP:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] - 1;
      break;
    case DIRECTION_DOWN:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] + 1;
      break;
    default: break;
  }
  end:;
}

int SnakeIsColliding(struct snake* snake) {
  return 0;
}

void SnakeDraw(SDL_Surface* screen, struct snake* snake)
{
  BlockDraw(screen, snake->blocksX[0], snake->blocksY[0], SNAKE_HEAD_COLOR, 0);

  // First eye
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Second eye
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 4, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 5, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 6, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 7, COLOR_BLACK);

  // Mouth
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 12, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 13, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 14, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 15, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 8, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 9, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 10, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 11, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 12, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 13, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 14, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 4, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 5, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 6, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);
  DrawPixel(screen, snake->blocksX[0]*BLOCK_SIZE + 7, snake->blocksY[0]*BLOCK_SIZE + 15, COLOR_RED);

  for(int i = 1; i < snake->size; i++) {
    BlockDraw(screen, snake->blocksX[i], snake->blocksY[i], SNAKE_BODY_COLOR, 0);
  }
}

struct snake* SnakeDestroy(struct snake* snake)
{
  free(snake);
  snake = NULL;

  return snake;
}