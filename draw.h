#ifndef SNAKE_DRAW_H
#define SNAKE_DRAW_H

#endif //SNAKE_DRAW_H

#include "snake.h"

SDL_Surface* drawBox(SDL_Surface* screenSurface, int posX, int posY, int size, SDL_Color color);
/*
 * Draw a box of color in the posX and posY on window
 */

SDL_Surface* drawSnake(SDL_Surface* screenSurface, struct snake* snake, SDL_Color color);
/*
 * Draw a snake of color in the screen
 */