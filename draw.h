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

#define EXTRACOLOR      COLOR_BLACK
#define SCORECOLOR      COLOR_RED

#define FONT_TYPE     "RobotoMono-Light"
#define FONT_SIZE     30
#define FONT_STYLE    TTF_STYLE_NORMAL
#define FONT_OUTLINE  0
#define FONT_DIR      "assets/"FONT_TYPE".ttf"

#define TYPE_FLAT   0 // Draw flat block
#define TYPE_BORDER 1 // Draw block with black border
#define TYPE_VOLUME 2 // Draw block simulating volume

TTF_Font* DrawTextInit();

void DrawPixel(SDL_Surface *screen, int x, int y, SDL_Color sdlcolor);
/*
 * Paint a pixel of color in the screen
 */

void DrawBlock(SDL_Surface* screen, int x, int y, SDL_Color color, int type);
/*
 * Draw a block of color in the screen
 */

void DrawText(SDL_Surface* screenSurface, SDL_Surface* textSurface,
              TTF_Font* font, char* text, int x, int y,
              SDL_Color textcolor, SDL_Color bgcolor);
/*
 * Draw a text in the screen
 */

void DrawCircle(SDL_Surface* screen, int x0, int y0, SDL_Color color);

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color);


// -- Refactor -- //
void DrawWalls(SDL_Surface* screen);
/*
 * Draw the limits of the level
 */

void DrawTerrain(SDL_Surface* screen);
/*
 * Draw the blocks of the surface
 */

void DrawExtra(SDL_Surface* screen);
/*
 * Draw the extra blocks below the game level
 */

void DrawScore(SDL_Surface* screen, SDL_Surface* textSurface, TTF_Font* font, int score);
/*
 * Draw the player score
 */

#endif //SNAKE_DRAW_H
