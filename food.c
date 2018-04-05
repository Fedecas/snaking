#include <SDL2/SDL.h>

#include "block.h"
#include "food.h"

struct food* foodCreate()
{
  struct food* food = NULL;

  food = malloc(sizeof(struct food));

  food->x = FOOD_SPAWNX;
  food->y = FOOD_SPAWNY;
  food->calories = FOOD_CALORIES;

  return food;
}

int foodInCollision(struct food* food, struct snake* snake)
{
  int foodX = food->x;
  int foodY = food->y;

  int snakeblockX;
  int snakeblockY;

  for(unsigned int i = 0; i < snake->size; i++) {
    snakeblockX = snake->blocksX[i];
    snakeblockY = snake->blocksY[i];

    if(blockInCollision(foodX, foodY, snakeblockX, snakeblockY)) return 1;
  }

  return 0;
}

struct food* foodEat(struct food* food, struct snake* snake)
{
  int newsnakehunger = snake->hunger - food->calories;

  if(newsnakehunger <= 0) {
    snakeIncrease(snake);

    newsnakehunger = newsnakehunger + SNAKE_HUNGER;
  }

  snake->hunger = newsnakehunger;

  food = foodDestroy(food);

  food = foodCreate();

  return food;
}

struct food* foodDestroy(struct food* food)
{
  free(food);
  food = NULL;

  return food;
}