#include <time.h>

#include "../engine/block.h"
#include "../engine/window.h"

#include "food.h"

struct _food_t {
    int x;
    int y;
};

void FoodCreate()
{
  LevelFood = (food_t) malloc(sizeof(struct _food_t));

  srand((unsigned int) time(NULL));

  LevelFood->x = FOOD_SPAWNX;
  LevelFood->y = FOOD_SPAWNY;
}

int FoodPosX()
{
  return (LevelFood->x);
}

int FoodPosY()
{
  return (LevelFood->y);
}

void FoodDraw()
{
  int posX = LevelFood->x;
  int posY = LevelFood->y;

  BlockDraw(posX, posY, COLOR_FOOD, 0);
}

void FoodDestroy()
{
  free(LevelFood);
  LevelFood = NULL;
}