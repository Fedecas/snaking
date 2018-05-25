#ifndef SNAKING_DRAW_H
#define SNAKING_DRAW_H

#include <SDL2/SDL_surface.h>

typedef SDL_Color color_t;
typedef SDL_Surface * surface_t;

#include "../colors.h"

#include "font.h"

void DrawPixel(int x, int y, color_t color);
/*
 * Paint a pixel of color in the screen
 */

void DrawBox( int x, int y, int width, int height, color_t color);
/*
 * Draw a box of color in the screen
 */

void DrawText(font_t font, char* text, int x, int y, color_t color);
/*
 * Draw text in the screen
 */

#endif //SNAKING_DRAW_H