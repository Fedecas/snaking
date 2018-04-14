#include "draw.h"
#include "food.h"
#include "snake.h"

food FoodCreate()
{
  food food = NULL;

  food = malloc(sizeof(struct food));

  food->x = FOOD_SPAWNX;
  food->y = FOOD_SPAWNY;
  food->calories = FOOD_CALORIES;

  return food;
}

int FoodIsColliding(food food, int x, int y)
{
  return BlockInCollision(food->x, food->y, x, y);
}

void FoodDraw(SDL_Surface* surface, food food)
{
  int posX = food->x;
  int posY = food->y;

  BlockDraw(surface, posX, posY, FOOD_COLOR, 0);
}

food FoodDestroy(food food)
{
  free(food);
  food = NULL;

  return food;
}