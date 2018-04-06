#include <SDL2/SDL.h>

#include "draw.h"
#include "snake.h"
#include "window.h"

static void SnakeBodyMove(struct snake* snake, int copyX, int copyY)
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

struct snake* SnakeCreate()
{
  struct snake* snake = NULL;

  snake = malloc(sizeof(struct snake));

  snake->direction = SNAKE_DIRECTION;
  snake->size = 1;
  snake->hunger = SNAKE_HUNGER;
  snake->blocksX[0] = SNAKE_SPAWNX;
  snake->blocksY[0] = SNAKE_SPAWNY;

  for(unsigned int i = 1; i < SNAKE_SIZE; i++) {
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

int SnakeIsColliding(struct snake* snake) { // TODO
  return 0;
}

void SnakeDraw(SDL_Surface* screen, struct snake* snake)
{
  DrawBlock(screen, snake->blocksX[0], snake->blocksY[0], SNAKE_HEAD_COLOR, 1);

  for(unsigned int i = 1; i < snake->size; i++) {
    DrawBlock(screen, snake->blocksX[i], snake->blocksY[i], SNAKE_BODY_COLOR, 1);
  }
}

struct snake* SnakeDestroy(struct snake* snake)
{
  free(snake);
  snake = NULL;

  return snake;
}