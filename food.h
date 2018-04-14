#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#define FOOD_SPAWNX   (1 + ((int)random() % (BLOCKS_X - 2))) // Pick a block X in the usable area
#define FOOD_SPAWNY   (1 + ((int)random() % (BLOCKS_Y - 2))) // Pick a block Y in the usable area
#define FOOD_CALORIES 5 // (SNAKE_HUNGER / FOOD_CALORIES) = nº of food to eat for increase the snake

#define FOOD_COLOR  mk_SDL_Color(109, 76, 65, 255)

typedef struct food {
    int x;
    int y;
    int calories;
} *food;

food FoodCreate();
/*
 * Initialize the food and set the parameters in default values
 */

int FoodIsColliding(food food, int x, int y);
/*
 * Check if the entered food is in collision with the entered snake
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
