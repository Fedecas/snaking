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
#define COLOR_LBROWN    mk_SDL_Color(255, 249, 196, 255)
#define COLOR_BGREY     mk_SDL_Color(96, 125, 139, 255)

#define TERRAINCOLOR    COLOR_LBROWN
#define WALLCOLOR       COLOR_BGREY

#define SCORECOLOR      COLOR_RED

#define FONT_TYPE     "RobotoMono-Light"       // Type of font to use
#define FONT_SIZE     BLOCK_SIZE               // Size of letter
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

void DrawPixel(SDL_Surface *screen, int x, int y, SDL_Color sdlcolor);
/*
 * Paint a pixel of color in the screen
 */

void DrawText(SDL_Surface* screenSurface, SDL_Surface* textSurface,
              TTF_Font* font, char* text, int x, int y,
              SDL_Color textcolor, SDL_Color bgcolor);
/*
 * Draw a text in the screen
 */

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color);
/*
 * Draw a line of pixels from pos (x0, y0) to (x1, y1)
 */

void DrawWalls(SDL_Surface* screen);
/*
 * Draw the limits of the level
 */

void DrawTerrain(SDL_Surface* screen);
/*
 * Draw the blocks of the surface
 */

void DrawScore(SDL_Surface* screen, SDL_Surface* textSurface, TTF_Font* font, int score);
/*
 * Draw the player score
 */

#endif //SNAKE_DRAW_H
