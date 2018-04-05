#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include "snake.h"

#define FOOD_CALORIES 5 // (SNAKE_HUNGER / FOOD_CALORIES) = nº of food to eat for grow the snake

struct food {
    int x;
    int y;
    int calories;
};

struct food* foodCreate();
int foodInCollision(struct food* food, struct snake* snake);
struct food* foodEat(struct food* food, struct snake* snake);
struct food* foodDestroy(struct food* food);


#endif //SNAKE_FOOD_H
