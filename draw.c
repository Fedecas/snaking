#include <SDL2/SDL.h>

#include "color.h"
#include "draw.h"
#include "window.h"

void drawPixel(SDL_Surface* screenSurface, int x, int y, SDL_Color color)
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

void drawBlock(SDL_Surface* screenSurface, int posX, int posY, SDL_Color color)
{
  int drawposx = posX * BLOCK_SIZE;
  int drawposy = posY * BLOCK_SIZE;

  // Lock the surface before painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_LockSurface(screenSurface);

  // Draw a box of pixels
  for(int x = drawposx; x < drawposx + BLOCK_SIZE; x++) {
    for (int y = drawposy; y < drawposy + BLOCK_SIZE; y++) {
      if(x == drawposx || x == drawposx + (BLOCK_SIZE - 1) || y == drawposy || y == drawposy + (BLOCK_SIZE - 1)) {
        drawPixel(screenSurface, x, y, COLOR_BLACK);
      } else {
        drawPixel(screenSurface, x, y, color);
      }
    }
  }

  // Unlock the surface after painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_UnlockSurface(screenSurface);
}

void drawSnake(SDL_Surface* screenSurface, struct snake* snake, SDL_Color color)
{
  drawBlock(screenSurface, snake->blocksX[0], snake->blocksY[0], COLOR_ORANGE);

  for(unsigned int i = 1; i < snake->size; i++) {
    drawBlock(screenSurface, snake->blocksX[i], snake->blocksY[i], color);
  }
}

void drawLimits(SDL_Surface* screenSurface)
{
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    drawBlock(screenSurface, WINDOW_LIMIT_LEFT, y, COLOR_BLUE);
  }
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    drawBlock(screenSurface, WINDOW_LIMIT_RIGHT, y, COLOR_BLUE);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    drawBlock(screenSurface, x, WINDOW_LIMIT_UP, COLOR_GREEN);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    drawBlock(screenSurface, x, WINDOW_LIMIT_DOWN, COLOR_GREEN);
  }
}

void drawSurface(SDL_Surface* screenSurface)
{
  for(unsigned int y = WINDOW_LIMIT_UP + 1; y < WINDOW_LIMIT_DOWN; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
      drawBlock(screenSurface, x, y, COLOR_WHITE);
    }
  }
}