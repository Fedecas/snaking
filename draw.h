#ifndef SNAKE_DRAW_H
#define SNAKE_DRAW_H

static SDL_Color mk_SDL_Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_Color color = {red, green, blue, alpha};
  return color;
}

#define COLOR_WHITE   mk_SDL_Color(255, 255, 255, 255)
#define COLOR_DRED    mk_SDL_Color(128, 0, 0, 255)
#define COLOR_RED     mk_SDL_Color(255, 0, 0, 255)
#define COLOR_ORANGE  mk_SDL_Color(255, 128, 0, 255)
#define COLOR_YELLOW  mk_SDL_Color(255, 255, 0, 255)
#define COLOR_BLACK   mk_SDL_Color(0, 0, 0, 255)

#define WALLCOLOR         COLOR_YELLOW
#define TERRAINCOLOR      COLOR_WHITE
#define EXTRACOLOR        COLOR_BLACK
#define SCORECOLOR        COLOR_RED

#define TYPE_FLAT   0 // Draw flat block
#define TYPE_BORDER 1 // Draw block with black border
#define TYPE_VOLUME 2 // Draw block with shadow

void DrawBlock(SDL_Surface* screen, int x, int y, SDL_Color color, int type);
/*
 * Draw a block of color in the screen
 */

void DrawText(SDL_Surface* screen, char* string,
              int size, int x, int y,
              SDL_Color foregroundcolor,
              SDL_Color backgroundcolor);
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

void DrawScore(SDL_Surface* screen, int score);
/*
 * Draw the player score
 */

#endif //SNAKE_DRAW_H