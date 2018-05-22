#ifndef SNAKING_FOOD_H
#define SNAKING_FOOD_H

#include "../engine/draw.h"

#define FOOD_SPAWNX   (1 + ((int)rand() % (BLOCKS_X - 2))) // Pick a block X in the usable area
#define FOOD_SPAWNY   (1 + ((int)rand() % (BLOCKS_Y - 2))) // Pick a block Y in the usable area

typedef struct _food_t * food_t;

food_t FoodCreate();
/*
 * Initialize the food and set the parameters in default values
 */

int FoodPosX(food_t food);
/*
 * Return the x position of the food
 */

int FoodPosY(food_t food);
/*
 * Return the y position of the food
 */

void FoodDraw(SDL_Surface* surface, food_t food);
/*
 * Draw the actual food in screen
 */

food_t FoodDestroy(food_t food);
/*
 * Free the food's memory
 */

#endif //SNAKING_FOOD_H
