#ifndef SNAKING_FOOD_H
#define SNAKING_FOOD_H

#define FOOD_SPAWNX   (1 + ((int)rand() % (BLOCKS_X - 2))) // Pick a block X in the usable area
#define FOOD_SPAWNY   (1 + ((int)rand() % (BLOCKS_Y - 2))) // Pick a block Y in the usable area

typedef struct _food_t * food_t;

food_t LevelFood;

void FoodCreate();
/*
 * Initialize the food and set the parameters in default values
 */

int FoodPosX();
/*
 * Return the x position of the food
 */

int FoodPosY();
/*
 * Return the y position of the food
 */

void FoodDraw();
/*
 * Draw the actual food in screen
 */

void FoodDestroy();
/*
 * Free the food's memory
 */

#endif //SNAKING_FOOD_H
