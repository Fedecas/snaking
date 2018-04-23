#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#define FOOD_SPAWNX   (1 + ((int)random() % (BLOCKS_X - 2))) // Pick a block X in the usable area
#define FOOD_SPAWNY   (1 + ((int)random() % (BLOCKS_Y - 2))) // Pick a block Y in the usable area

typedef struct food {
    int x;
    int y;
} * food;

food FoodCreate();
/*
 * Initialize the food and set the parameters in default values
 */

void FoodDraw(SDL_Surface* surface, food food);
/*
 * Draw the actual food in screen
 */

food FoodDestroy(food food);
/*
 * Free the food's memory
 */

#endif //SNAKE_FOOD_H
