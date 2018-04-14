#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "block.h"
#include "food.h"
#include "wall.h"

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_DIRECTION 1   // Pick a direction to snake by default
#define SNAKE_SIZE      3   // Size of the snake in blocks
#define SNAKE_HUNGER    10  // Number of calories to have to eat the snake for increase
#define SNAKE_SPAWNX    (BLOCKS_X / 2) // Default block X to spawn a snake
#define SNAKE_SPAWNY    (BLOCKS_Y / 2) // Default block Y to spawn a snake

#define SNAKE_HEAD_COLOR  mk_SDL_Color(192, 202, 51, 255)
#define SNAKE_BODY_COLOR  mk_SDL_Color(211, 47, 47, 255)

typedef struct snake {
    int headDirection;
    int tailDirection;
    int size;
    int hunger;
    int* blocksX;
    int* blocksY;
} *snake;

snake SnakeCreate();
/*
 * Initialize the snake and set the parameters in default values
 */

void SnakeMove(snake snake, int direction);
/*
 * Move the snake one block to the entered direction
 */

void SnakeIncrease(snake snake);
/*
 * Increase the large of the snake in one block
 */

int SnakeIsCollidingWithWall(snake snake, wall wall1, wall wall2, wall wall3, wall wall4);
/*
 * Check if the snake is colliding with a wall
 */

int SnakeIsCollidingWithFood(snake snake, food food);
/*
 * Check if the snake is colliding with food
 */

int SnakeIsCollidingWithHerself(snake snake);
/*
 * Check if the snake is colliding with her body
 */

void SnakeDraw(SDL_Surface* surface, snake snake);
/*
 * Draw a snake of color in the screen
 */

snake SnakeDestroy(snake snake);
/*
 * Free the snake's memory
 */

#endif //SNAKE_SNAKE_H
