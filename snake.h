#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#endif //SNAKE_SNAKE_H

#define BOX_SIZE        20
#define BOX_SEPARATION  1

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define SNAKE_BLOCK     (BOX_SIZE+BOX_SEPARATION)

#define SNAKE_MAX_SIZE  10

struct snake {
    int direction;
    int size;
    int blocksX[SNAKE_MAX_SIZE];
    int blocksY[SNAKE_MAX_SIZE];
};


struct snake* snakeCreate();

void snakeMove(struct snake* snake, int direction);

void snakeIncrease(struct snake* snake);

int snakeIsColliding(struct snake* snake);

void snakeDestroy(struct snake* snake);