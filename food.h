#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include "snake.h"

#define FOOD_SPAWNX   (1 + ((int)random() % (BLOCKS_X - 2))) // Pick a block X in the usable area
#define FOOD_SPAWNY   (1 + ((int)random() % (BLOCKS_Y - 2))) // Pick a block Y in the usable area
#define FOOD_CALORIES 5 // (SNAKE_HUNGER / FOOD_CALORIES) = nº of food to eat for increase the snake

#define FOOD_COLOR  mk_SDL_Color(109, 76, 65)

struct food {
    int x;
    int y;
    int calories;
};

struct food* FoodCreate();
/*
 * Initialize the food and set the parameters in default values
 */

int FoodInCollision(struct food* food, struct snake* snake);
/*
 * Check if the entered food is in collision with the entered snake
 */

struct food* FoodEat(struct food* food, struct snake* snake);
/*
 * Increase the entered snake if correspond, set the new hunger, destroy the actual food and return a new one
 */

void FoodDraw(SDL_Surface* screen, struct food* food);
/*
 * Draw the actual food in screen
 */

struct food* FoodDestroy(struct food* food);
/*
 * Free the food's memory
 */

#endif //SNAKE_FOOD_H
