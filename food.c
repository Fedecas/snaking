#include "draw.h"
#include "food.h"

food* FoodCreate()
{
  food* food = NULL;

  food = malloc(sizeof(struct food));

  food->x = FOOD_SPAWNX;
  food->y = FOOD_SPAWNY;
  food->calories = FOOD_CALORIES;

  return food;
}

int FoodIsColliding(food* food, snake* snake)
{
  int foodX = food->x;
  int foodY = food->y;

  int snakeblockX;
  int snakeblockY;

  for(int i = 0; i < snake->size; i++) {
    snakeblockX = snake->blocksX[i];
    snakeblockY = snake->blocksY[i];

    if(BlockInCollision(foodX, foodY, snakeblockX, snakeblockY)) return 1;
  }

  return 0;
}

food* FoodEat(food* food, snake* snake)
{
  int newsnakehunger = snake->hunger - food->calories;

  if(newsnakehunger <= 0) {
    SnakeIncrease(snake);

    newsnakehunger = newsnakehunger + SNAKE_HUNGER;
  }

  snake->hunger = newsnakehunger;

  FoodDestroy(food);

  food = FoodCreate();

  return food;
}

void FoodDraw(SDL_Surface* surface, food* food)
{
  int posX = food->x;
  int posY = food->y;

  BlockDraw(surface, posX, posY, FOOD_COLOR, 0);
}

food* FoodDestroy(food* food)
{
  free(food);
  food = NULL;

  return food;
}