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

void DrawPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
  SDL_Rect pixel = {x, y, 1, 1};
  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_FillRect(surface, &pixel, col);
}

void DrawBox(SDL_Surface* surface, int x, int y, int width, int height, SDL_Color color)
{
  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, width, height};
  SDL_FillRect(surface, &rect, col);
}

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color)
{
}

void DrawText(SDL_Surface* screenSurface, TTF_Font* font,
              char* text, int x, int y, SDL_Color textcolor)
{
  int blockX = (x / BLOCK_SIZE);
  int blockY = (y / BLOCK_SIZE);

  if(BlockOutOfLimits(blockX, blockY)) {
    printf("[warning] Text out of the screen! (x: %d, y: %d)\n", x, y);
  }

  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);
}

// *
void DrawWalls(SDL_Surface* surface)
{
  DrawBox(surface, 0, 0, BLOCK_SIZE, WINDOW_HEIGHT, WALLCOLOR);
  DrawBox(surface, BLOCK_SIZE, 0, WINDOW_WIDTH - (BLOCK_SIZE * 2), BLOCK_SIZE, WALLCOLOR);
  DrawBox(surface, WINDOW_LIMIT_RIGHT * BLOCK_SIZE, 0, BLOCK_SIZE, WINDOW_HEIGHT, WALLCOLOR);
  DrawBox(surface, BLOCK_SIZE, WINDOW_LIMIT_DOWN * BLOCK_SIZE, WINDOW_WIDTH - (BLOCK_SIZE * 2), BLOCK_SIZE, WALLCOLOR);
}

void DrawTerrain(SDL_Surface* surface)
{
  DrawBox(surface, BLOCK_SIZE, BLOCK_SIZE, (BLOCKS_X - 2) * BLOCK_SIZE, (BLOCKS_Y - 2) * BLOCK_SIZE, TERRAINCOLOR);
}

void DrawScore(SDL_Surface* screen, TTF_Font* font, int score)
{
  int posX = (((BLOCKS_X - 1) * BLOCK_SIZE) / 2) - (2 * BLOCK_SIZE);
  int posY = (BLOCKS_Y - 1) * BLOCK_SIZE;

  DrawText(screen, font, "SCORE", posX, posY, SCORECOLOR);

  posX += (BLOCK_SIZE * 2) + 25;

  char str[12];
  sprintf(str, "%d", score);

  DrawText(screen, font, str, posX, posY, SCORECOLOR);
}
