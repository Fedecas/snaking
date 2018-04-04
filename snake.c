#include <SDL2/SDL.h>

#include "snake.h"
#include "window.h"

static void snakeMoveBody(struct snake* snake, int copyX, int copyY)
{
  int auxX, auxY;

  for(unsigned int i = 1; i < snake->size; i++) {
    auxX = snake->blocksX[i];
    auxY = snake->blocksY[i];

    snake->blocksX[i] = copyX;
    snake->blocksY[i] = copyY;

    copyX = auxX;
    copyY = auxY;
  }
}

struct snake* snakeCreate()
{
  struct snake* snake = NULL;

  snake = malloc(sizeof(struct snake));

  snake->direction = 1;
  snake->size = 1;
  snake->blocksX[0] = 105;
  snake->blocksY[0] = 105;

  return snake;
}

void snakeMove(struct snake* snake, int direction)
{
  snake->direction = direction;

  int copyX = snake->blocksX[0];
  int copyY = snake->blocksY[0];

  int futureheadpos;

  switch (direction) {
    case DIRECTION_LEFT:
      futureheadpos = snake->blocksX[0] - SNAKE_BLOCK;
      if(futureheadpos < WINDOW_LIMIT_LEFT) break;
      snake->blocksX[0] = futureheadpos;
      snakeMoveBody(snake, copyX, copyY); break;
    case DIRECTION_RIGHT:
      futureheadpos = snake->blocksX[0] + SNAKE_BLOCK;
      if(futureheadpos > WINDOW_LIMIT_RIGHT) break;
      snake->blocksX[0] = futureheadpos;
      snakeMoveBody(snake, copyX, copyY); break;
    case DIRECTION_UP:
      futureheadpos = snake->blocksY[0] - SNAKE_BLOCK;
      if(futureheadpos < WINDOW_LIMIT_UP) break;
      snake->blocksY[0] = futureheadpos;
      snakeMoveBody(snake, copyX, copyY); break;
    case DIRECTION_DOWN:
      futureheadpos = snake->blocksY[0] + SNAKE_BLOCK;
      if(futureheadpos > WINDOW_LIMIT_DOWN) break;
      snake->blocksY[0] = futureheadpos;
      snakeMoveBody(snake, copyX, copyY); break;
    default: break;
  }
}

void snakeIncrease(struct snake* snake)
{
  int oldlastblock = snake->size - 1;

  snake->size++;

  int newlastblock = snake->size - 1;

  switch (snake->direction) {
    case 1:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] - SNAKE_BLOCK;
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      break;
    case 2:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock] + SNAKE_BLOCK;
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock];
      break;
    case 3:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] - SNAKE_BLOCK;
      break;
    case 4:
      snake->blocksX[newlastblock] = snake->blocksX[oldlastblock];
      snake->blocksY[newlastblock] = snake->blocksY[oldlastblock] + SNAKE_BLOCK;
      break;
    default: break;
  }
}

int snakeIsColliding(struct snake* snake) {
  return 0;
}

void snakeDestroy(struct snake* snake)
{
  free(snake);
  snake = NULL;
}