#ifndef SNAKE_DRAW_H
#define SNAKE_DRAW_H

#include <SDL2/SDL_ttf.h>

static SDL_Color mk_SDL_Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_Color color = {red, green, blue, alpha};
  return color;
}

#define COLOR_RED       mk_SDL_Color(255, 0, 0, 255)
#define COLOR_BLACK     mk_SDL_Color(0, 0, 0, 255)

#define SCORECOLOR      COLOR_RED

#define FONT_TYPE     "RobotoMono-Light"       // Type of font to use
#define FONT_SIZE     (BLOCK_SIZE * 2)               // Size of letter
#define FONT_STYLE    TTF_STYLE_NORMAL         // Style of font (NORMAL, BOLD, ITALIC)
#define FONT_OUTLINE  0                        // Size of the font outline
#define FONT_DIR      "assets/"FONT_TYPE".ttf" // Path of a TrueType font for write

#define BLOCK_FLAT   0 // Draw flat block
#define BLOCK_BORDER 1 // Draw block with black border
#define BLOCK_VOLUME 2 // Draw block simulating volume

TTF_Font* DrawTextInit();
/*
 * Init the assets for write in screen
 */

void DrawPixel(SDL_Surface* surface, int x, int y, SDL_Color color);
/*
 * Paint a pixel of color in the screen
 */

void DrawBox(SDL_Surface* surface, int x, int y, int width, int height, SDL_Color color);
/*
 * Draw a box of color in the screen
 */

void DrawText(SDL_Surface* screenSurface, TTF_Font* font,
              char* text, int x, int y, SDL_Color color);
/*
 * Draw text in the screen
 */

void DrawScore(SDL_Surface* screen, TTF_Font* font, int score);
/*
 * Draw the player score
 */

#endif //SNAKE_DRAW_H
