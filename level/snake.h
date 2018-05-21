#ifndef SNAKING_SNAKE_H
#define SNAKING_SNAKE_H

#include "food.h"
#include "score.h"
#include "../engine/sound.h"
#include "wall.h"

#define DIRECTION_NONE  0
#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_DIRECTION (1 + ((int)rand() % 4)) // Pick a direction to snake by default
#define SNAKE_SIZE      3   // Size of the snake in blocks
#define SNAKE_HUNGER    2   // Number of food the snake have to eat for increase
#define SNAKE_SPAWNX    (SNAKE_SIZE + ((int)rand() % (BLOCKS_X - (2 * SNAKE_SIZE)))) // Default block X to spawn a snake
#define SNAKE_SPAWNY    (SNAKE_SIZE + ((int)rand() % (BLOCKS_Y - (2 * SNAKE_SIZE)))) // Default block Y to spawn a snake

typedef struct _snake_t * snake_t;

snake_t SnakeCreate();
/*
 * Initialize the snake and set the parameters in default values
 */

void SnakeMove(snake_t snake, int direction);
/*
 * Move the snake one block to the entered direction, if direction given is valid
 */

void SnakeIncrease(snake_t snake, sound_t sound);
/*
 * Increase the large of the snake in one block
 */

int SnakeCollidingWallOrBody(snake_t snake, wall_t* walls);
/*
 * Check if snake is colliding with some wall or herself
 */

void SnakeEat(snake_t snake, food_t* food, score_t score, sound_t increase, sound_t eat);
/*
 * Increase the snake, restart the food and increase the score, if snake collide the food
 */

void SnakeDraw(SDL_Surface* surface, snake_t snake);
/*
 * Draw a snake of color in the screen
 */

snake_t SnakeDestroy(snake_t snake);
/*
 * Free the snake's memory
 */

#endif //SNAKING_SNAKE_H