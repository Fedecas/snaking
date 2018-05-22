#ifndef SNAKING_DRAW_H
#define SNAKING_DRAW_H

#include <SDL2/SDL_ttf.h>

#include "../colors.h"

#define FONT_TYPE     "RobotoMono-Light"                // Type of font to use
#define FONT_PATH     "assets/fonts/"FONT_TYPE".ttf"    // Path of a TrueType font for write
#define FONT_SIZE     (BLOCK_SIZE * 2)                  // Size of letter

TTF_Font* DrawTextInit();
/*
 * Init the font for write in screen
 */

void DrawPixel(SDL_Surface* surface, int x, int y, SDL_Color color);
/*
 * Paint a pixel of color in the screen
 */

void DrawBox(SDL_Surface* surface, int x, int y, int width, int height, SDL_Color color);
/*
 * Draw a box of color in the screen
 */

void DrawText(SDL_Surface* surface, TTF_Font* font,
              char* text, int x, int y, SDL_Color color);
/*
 * Draw text in the screen
 */

TTF_Font* DrawTextQuit(TTF_Font* font);
/*
 * Close the font opened and exit TTF module
 */

#endif //SNAKING_DRAW_H