#include "block.h"
#include "draw.h"

TTF_Font* DrawTextInit()
{
  TTF_Init();

  TTF_Font* font = TTF_OpenFont(FONT_DIR, FONT_SIZE);

  if(font == NULL) {
    printf("[error] Font could not be loaded! TTF_Error: %s\n", SDL_GetError());
  }

  TTF_SetFontStyle(font, FONT_STYLE);

  return font;
}

void DrawPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_Rect pixel = {x, y, 1, 1};
  SDL_FillRect(surface, &pixel, col);
}

void DrawBox(SDL_Surface* surface, int x, int y, int width, int height, SDL_Color color)
{
  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, width, height};
  SDL_FillRect(surface, &rect, col);
}

void DrawText(SDL_Surface* screenSurface, TTF_Font* font,
              char* text, int x, int y, SDL_Color color)
{
  int blockX = (x / BLOCK_SIZE);
  int blockY = (y / BLOCK_SIZE);

  if(BlockOutOfLimits(blockX, blockY)) {
    printf("[warning] Text out of the screen! (x: %d, y: %d)\n", x, y);
  }

  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);

  SDL_FreeSurface(textSurface);
}

TTF_Font* DrawTextQuit(TTF_Font* font)
{
  TTF_CloseFont(font);
  font = NULL;

  TTF_Quit();

  return font;
}