#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "draw.h"
#include "window.h"

// TODO use renders to draw ***
TTF_Font* DrawTextInit()
{
  TTF_Font* font = NULL;

  font = TTF_OpenFont(FONT_DIR, FONT_SIZE);

  if(font == NULL) {
    printf("[error] Font could not be loaded! TTF_Error: %s\n", SDL_GetError());
  }

  TTF_SetFontStyle(font, FONT_STYLE);
  TTF_SetFontOutline(font, FONT_OUTLINE);

  return font;
}

void DrawPixel(SDL_Surface *screen, int x, int y, SDL_Color sdlcolor)
{
  Uint32 color = SDL_MapRGBA(screen->format, sdlcolor.r, sdlcolor.g, sdlcolor.b, sdlcolor.a);

  Uint32* pixels = screen->pixels;

  int thispixel = ((y * screen->w) + x);

  pixels[thispixel] = color;
}

void DrawText(SDL_Surface* screenSurface, SDL_Surface* textSurface,
              TTF_Font* font, char* text, int x, int y,
              SDL_Color textcolor, SDL_Color bgcolor)
{
  int blockX = (x / BLOCK_SIZE);
  int blockY = (y / BLOCK_SIZE);

  if(BlockOutOfLimits(blockX, blockY)) {
    printf("[warning] Text out of the screen! (x: %d, y: %d)\n", x, y);
  }

  textSurface = TTF_RenderText_Shaded(font, text, textcolor, bgcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);
}

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color) // TODO DrawLine
{
  // TODO function to compare with return GT - EQ - LT
  if(y0 == y1) {
    while(x0 + 1 < x1) {
      DrawPixel(screen, x0 + 1, y0, color);
      x0++;
    }
  }
}

void DrawWalls(SDL_Surface* screen) // TODO walls module
{
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    BlockDraw(screen, WINDOW_LIMIT_LEFT, y, WALLCOLOR, 0);
  }
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    BlockDraw(screen, WINDOW_LIMIT_RIGHT, y, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    BlockDraw(screen, x, WINDOW_LIMIT_UP, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    BlockDraw(screen, x, WINDOW_LIMIT_DOWN, WALLCOLOR, 0);
  }
}

void DrawTerrain(SDL_Surface* screen) // TODO terrain module
{
  for(unsigned int y = WINDOW_LIMIT_UP + 1; y < WINDOW_LIMIT_DOWN; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
      BlockDraw(screen, x, y, TERRAINCOLOR, 0);
    }
  }
}

void DrawScore(SDL_Surface* screen, SDL_Surface* text, TTF_Font* font, int score)
{
  int posX = (((BLOCKS_X - 1) * BLOCK_SIZE) / 2) - (2 * BLOCK_SIZE);
  int posY = (BLOCKS_Y - 1) * BLOCK_SIZE;

  DrawText(screen, text, font, "SCORE", posX, posY, SCORECOLOR, WALLCOLOR);

  posX += (BLOCK_SIZE * 2) + 25;

  char str[12];
  sprintf(str, "%d", score);

  DrawText(screen, text, font, str, posX, posY, SCORECOLOR, WALLCOLOR);
}
