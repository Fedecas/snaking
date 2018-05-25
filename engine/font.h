#ifndef SNAKING_FONT_H
#define SNAKING_FONT_H

#include <SDL2/SDL_ttf.h>

#include "block.h"

#define FONT_TYPE   "RobotoMono-Light"                // Type of font to use
#define FONT_PATH   "assets/fonts/"FONT_TYPE".ttf"    // Path of a TrueType font for write
#define FONT_SIZE   (BLOCK_SIZE * 2)                  // Size of the score font

typedef TTF_Font * font_t;

font_t ScoreFont;
font_t ButtonFont;

void FontInitModuleAndScore();
/*
 * Init the TTF module and 'ScoreFont' for game score
 */

void FontInitButton();
/*
 * Init 'ButtonFont' for button's text
 */

void FontSize(font_t font, char* text, int* fontwidth, int* fontheight);
/*
 *
 */

void FontQuitButton();
/*
 * Close font 'ButtonFont'
 */

void FontQuitScore();
/*
 * Close font 'ScoreFont' and exit TTF module
 */

#endif //SNAKING_FONT_H
