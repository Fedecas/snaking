#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "draw.h"
#include "window.h"

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

void DrawPixel(SDL_Renderer* renderer, int x, int y, SDL_Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(renderer, x, y);
}

void DrawBox(SDL_Surface* surface, int x, int y, SDL_Color color)
{
  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
  SDL_FillRect(surface, &rect, col);
}

void DrawText(SDL_Surface* screenSurface, SDL_Surface* textSurface,
              TTF_Font* font, char* text, int x, int y,
              SDL_Color textcolor)
{
  int blockX = (x / BLOCK_SIZE);
  int blockY = (y / BLOCK_SIZE);

  if(BlockOutOfLimits(blockX, blockY)) {
    printf("[warning] Text out of the screen! (x: %d, y: %d)\n", x, y);
  }

  textSurface = TTF_RenderText_Solid(font, text, textcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);
}

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color)
{
}

void DrawWalls(SDL_Renderer* renderer, SDL_Surface* surface)
{
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    BlockDraw(renderer, surface, WINDOW_LIMIT_LEFT, y, WALLCOLOR, 0);
  }
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    BlockDraw(renderer, surface, WINDOW_LIMIT_RIGHT, y, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    BlockDraw(renderer, surface, x, WINDOW_LIMIT_UP, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    BlockDraw(renderer, surface, x, WINDOW_LIMIT_DOWN, WALLCOLOR, 0);
  }
}

void DrawTerrain(SDL_Renderer* renderer, SDL_Surface* surface)
{
  for(unsigned int y = WINDOW_LIMIT_UP + 1; y < WINDOW_LIMIT_DOWN; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
      BlockDraw(renderer, surface, x, y, TERRAINCOLOR, 0);
    }
  }
}

void DrawScore(SDL_Surface* screen, SDL_Surface* text, TTF_Font* font, int score)
{
  int posX = (((BLOCKS_X - 1) * BLOCK_SIZE) / 2) - (2 * BLOCK_SIZE);
  int posY = (BLOCKS_Y - 1) * BLOCK_SIZE;

  DrawText(screen, text, font, "SCORE", posX, posY, SCORECOLOR);

  posX += (BLOCK_SIZE * 2) + 25;

  char str[12];
  sprintf(str, "%d", score);

  DrawText(screen, text, font, str, posX, posY, SCORECOLOR);
}
