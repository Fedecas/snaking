#include "block.h"
#include "draw.h"
#include "food.h"

food FoodCreate()
{
  food NewFood = (food) malloc(sizeof(struct food));

  NewFood->x = FOOD_SPAWNX;
  NewFood->y = FOOD_SPAWNY;

  return NewFood;
}

void FoodDraw(SDL_Surface* LevelSurface, food ActualFood)
{
  int posX = ActualFood->x;
  int posY = ActualFood->y;

  BlockDraw(LevelSurface, posX, posY, COLOR_FOOD, 0);
}

food FoodDestroy(food ActualFood)
{
  free(ActualFood);
  ActualFood = NULL;

  return ActualFood;
}