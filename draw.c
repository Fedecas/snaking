#include <SDL2/SDL.h>

#include "draw.h"

static void drawPixel(SDL_Surface* screenSurface, int x, int y, SDL_Color color)
{
  // Color convert
  Uint32 col = SDL_MapRGB(screenSurface->format, color.r, color.g, color.b);
  // Set the start position
  char *buffer = (char*) screenSurface->pixels;
  // Offset for y
  buffer += screenSurface->pitch*y;
  // Offset for x
  buffer += screenSurface->format->BytesPerPixel*x;
  // Copy the pixel
  memcpy(buffer, &col, screenSurface->format->BytesPerPixel);
}

SDL_Surface* drawBox(SDL_Surface* screenSurface, int posX, int posY, int size, SDL_Color color)
{
  // Lock the surface before painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_LockSurface(screenSurface);

  // Draw a box of pixels
  for(int x = posX; x < posX + size; x++) {
    for (int y = posY; y < posY + size; y++) {
      drawPixel(screenSurface, x, y, color);
    }
  }

  // Unlock the surface after painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_UnlockSurface(screenSurface);

  return screenSurface;
}

SDL_Surface* drawSnake(SDL_Surface* screenSurface, struct snake* snake, SDL_Color color)
{
  for(unsigned int i = 0; i < snake->size; i++) {
    screenSurface = drawBox(screenSurface, snake->blocksX[i], snake->blocksY[i], BOX_SIZE, color);
  }

  return screenSurface;
}