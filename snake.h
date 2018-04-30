#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "food.h"
#include "score.h"
#include "sound.h"
#include "wall.h"

#define DIRECTION_NONE  0
#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_DIRECTION (1 + ((int)random() % 4)) // Pick a direction to snake by default
#define SNAKE_SIZE      3   // Size of the snake in blocks
#define SNAKE_HUNGER    2   // Number of food the snake have to eat for increase
#define SNAKE_SPAWNX    (SNAKE_SIZE + ((int)random() % (BLOCKS_X - (2 * SNAKE_SIZE)))) // Default block X to spawn a snake
#define SNAKE_SPAWNY    (SNAKE_SIZE + ((int)random() % (BLOCKS_Y - (2 * SNAKE_SIZE)))) // Default block Y to spawn a snake

typedef struct snake {
    int headDirection;
    int tailDirection;
    int size;
    int hunger;
    int* blocksX;
    int* blocksY;
} * snake;

snake SnakeCreate();
/*
 * Initialize the snake and set the parameters in default values
 */

void SnakeMove(snake PlayerSnake, int direction);
/*
 * Move the snake one block to the entered direction, if direction given is valid
 */

void SnakeIncrease(snake PlayerSnake, sound IncreaseSound);
/*
 * Increase the large of the snake in one block
 */

int SnakeCollidingWallOrBody(snake PlayerSnake, wall* LevelWalls);
/*
 * Check if snake is colliding with some wall or herself
 */

void SnakeEat(snake PlayerSnake, food* ActualFood, score GameScore, sound IncreaseSound, sound EatSound);
/*
 * Increase the snake, restart the food and increase the score, if snake collide the food
 */

void SnakeDraw(SDL_Surface* LevelSurface, snake PlayerSnake);
/*
 * Draw a snake of color in the screen
 */

snake SnakeDestroy(snake PlayerSnake);
/*
 * Free the snake's memory
 */

#endif //SNAKE_SNAKE_H