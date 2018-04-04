#ifndef SNAKE_DRAW_H
#define SNAKE_DRAW_H

#include "snake.h"

void drawPixel(SDL_Surface* screenSurface, int x, int y, SDL_Color color);
/*
 * Paint a pixel of color in the screen
 */

void drawBlock(SDL_Surface* screenSurface, int posX, int posY, SDL_Color color);
/*
 * Draw a box of color in the screen
 */

void drawSnake(SDL_Surface* screenSurface, struct snake* snake, SDL_Color color);
/*
 * Draw a snake of color in the screen
 */

void drawLevelBlocks(SDL_Surface* screenSurface);
void drawLimits(SDL_Surface* screenSurface);

#endif //SNAKE_DRAW_H