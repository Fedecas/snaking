#include "../engine/block.h"

#include "food.h"

struct _food_t {
    int x;
    int y;
} _food_t;

food_t FoodCreate()
{
  food_t NewFood = (food_t) malloc(sizeof(_food_t));

  NewFood->x = FOOD_SPAWNX;
  NewFood->y = FOOD_SPAWNY;

  return NewFood;
}

int FoodPosX(food_t ActualFood)
{
  return (ActualFood->x);
}

int FoodPosY(food_t ActualFood)
{
  return (ActualFood->y);
}

void FoodDraw(SDL_Surface* LevelSurface, food_t ActualFood)
{
  int posX = ActualFood->x;
  int posY = ActualFood->y;

  BlockDraw(LevelSurface, posX, posY, COLOR_FOOD, 0);
}

food_t FoodDestroy(food_t ActualFood)
{
  free(ActualFood);
  ActualFood = NULL;

  return ActualFood;
}