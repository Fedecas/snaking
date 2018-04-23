#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "food.h"
#include "wall.h"

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_DIRECTION (1 + ((int)random() % 4)) // Pick a direction to snake by default
#define SNAKE_SIZE      3   // Size of the snake in blocks
#define SNAKE_HUNGER    10  // Number of calories to have to eat the snake for increase
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
 * Move the snake one block to the entered direction
 */

void SnakeIncrease(snake PlayerSnake);
/*
 * Increase the large of the snake in one block
 */

int SnakeIsCollidingWithWall(snake PlayerSnake, wall wall1, wall wall2, wall wall3, wall wall4);
/*
 * Check if the snake is colliding with a wall
 */

int SnakeIsCollidingWithFood(snake PlayerSnake, food ActualFood);
/*
 * Check if the snake is colliding with food
 */

int SnakeIsCollidingWithHerself(snake PlayerSnake);
/*
 * Check if the snake is colliding with her body
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
