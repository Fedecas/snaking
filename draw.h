#ifndef SNAKE_DRAW_H
#define SNAKE_DRAW_H

#include "food.h"
#include "snake.h"

#define TYPE_FLAT   0
#define TYPE_BORDER 1

void drawPixel(SDL_Surface* screenSurface, int x, int y, SDL_Color color);
/*
 * Paint a pixel of color in the screen
 */

void drawBlock(SDL_Surface* screenSurface, int posX, int posY, SDL_Color color, int type);
/*
 * Draw a block of color in the screen
 */

void drawSnake(SDL_Surface* screenSurface, struct snake* snake, SDL_Color color);
/*
 * Draw a snake of color in the screen
 */

void drawLimits(SDL_Surface* screenSurface);
/*
 * Draw the limits of the level
 */

void drawSurface(SDL_Surface* screenSurface);
/*
 * Draw the blocks of the surface
 */

void drawFood(SDL_Surface* screenSurface, struct food* food);

#endif //SNAKE_DRAW_H