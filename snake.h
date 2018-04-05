#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_DIRECTION 1 //(1 + ((int)random() % 4))
#define SNAKE_SIZE      3
#define SNAKE_HUNGER    10
#define SNAKE_SPAWNX    (BLOCKS_X / 2)
#define SNAKE_SPAWNY    (BLOCKS_Y / 2)

#define SNAKE_MAX_BLOCKS  20

struct snake {
    int direction;
    int size;
    int hunger;
    int blocksX[SNAKE_MAX_BLOCKS];
    int blocksY[SNAKE_MAX_BLOCKS];
};

struct snake* snakeCreate();
/*
 * Initialize the snake
 */

void snakeMove(struct snake* snake, int direction);
/*
 * Move the snake one block in a direction
 */

void snakeIncrease(struct snake* snake);
/*
 * Increase the large of the snake in one block
 */

int snakeIsColliding(struct snake* snake);
/*
 * Verify if the snake is colliding with a wall/other snakes
 */

struct snake* snakeDestroy(struct snake* snake);
/*
 * Free the snake's memory
 */

#endif //SNAKE_SNAKE_H