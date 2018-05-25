#ifndef SNAKING_SNAKE_H
#define SNAKING_SNAKE_H

#include "../engine/block.h"

#define SNAKE_DIRECTION (1 + ((int)rand() % 4)) // Pick a direction to snake by default
#define SNAKE_SIZE      3   // Size of the snake in blocks
#define SNAKE_HUNGER    2   // Number of food the snake have to eat for increase
#define SNAKE_SPAWNX    (SNAKE_SIZE + ((int)rand() % (BLOCKS_X - (2 * SNAKE_SIZE)))) // Default block X to spawn a snake
#define SNAKE_SPAWNY    (SNAKE_SIZE + ((int)rand() % (BLOCKS_Y - (2 * SNAKE_SIZE)))) // Default block Y to spawn a snake

typedef struct _snake_t * snake_t;

snake_t LevelSnake;

void SnakeCreate();
/*
 * Initialize the snake and set the parameters in default values
 */

void SnakeMove();
/*
 * Move the snake one block to the entered direction, if direction given is valid
 */

void SnakeIncrease();
/*
 * Increase the large of the snake in one block
 */

int SnakeCollidingWallOrBody();
/*
 * Check if snake is colliding with some wall or herself
 */

void SnakeEat();
/*
 * Increase the snake, restart the food and increase the score, if snake collide the food
 */

void SnakeDraw();
/*
 * Draw a snake of color in the screen
 */

void SnakeDestroy();
/*
 * Free the snake's memory
 */

#endif //SNAKING_SNAKE_H