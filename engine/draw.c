#include "draw.h"
#include "window.h"

void DrawPixel(int x, int y, color_t color)
{
  surface_t surface = WindowSurface();

  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  Uint32* pixels = surface->pixels;
  pixels[(y * surface->w) + x] = col;
}

void DrawBox(int x, int y, int width, int height, color_t color)
{
  surface_t surface = WindowSurface();

  Uint32 col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, width, height};
  SDL_FillRect(surface, &rect, col);
}

void DrawText(font_t font, char* text, int x, int y, color_t color)
{
  surface_t screenSurface = WindowSurface();

  int blockX = (x / BLOCK_SIZE);
  int blockY = (y / BLOCK_SIZE);

  if(BlockOutOfLimits(blockX, blockY)) {
    printf("[warning] Text out of the screen! (x: %d, y: %d)\n", x, y);
  }

  surface_t textSurface = TTF_RenderText_Solid(font, text, color);

  if(textSurface == NULL) {
    printf("[error] Text could not be writen! TTF_Error: %s\n", SDL_GetError());
  }

  SDL_Rect textLocation = {x, y, 0, 0};
  SDL_UpperBlit(textSurface, NULL, screenSurface, &textLocation);

  SDL_FreeSurface(textSurface);
}