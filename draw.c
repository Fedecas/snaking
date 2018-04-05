#include <SDL2/SDL.h>

#include "color.h"
#include "draw.h"
#include "food.h"
#include "window.h"

#define WALLCOLOR         COLOR_YELLOW
#define FOODCOLOR         COLOR_DRED
#define SURFACECOLOR      COLOR_DGREEN
#define SNAKEHEADCOLOR    COLOR_ORANGE
#define SNAKEBODYCOLOR    COLOR_RED

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

void drawBlock(SDL_Surface* screenSurface, int posX, int posY, SDL_Color color, int type)
{
  int drawposx = posX * BLOCK_SIZE;
  int drawposy = posY * BLOCK_SIZE;

  // Lock the surface before painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_LockSurface(screenSurface);

  switch (type) {
    case TYPE_FLAT:
      // Draw a box of color
      for(int x = drawposx; x < drawposx + BLOCK_SIZE; x++) {
        for (int y = drawposy; y < drawposy + BLOCK_SIZE; y++) {
          drawPixel(screenSurface, x, y, color);
        }
      } break;
    case TYPE_BORDER:
      // Draw a box of color with black border
      for(int x = drawposx; x < drawposx + BLOCK_SIZE; x++) {
        for (int y = drawposy; y < drawposy + BLOCK_SIZE; y++) {
          if(x == drawposx || x == drawposx + (BLOCK_SIZE - 1) || y == drawposy || y == drawposy + (BLOCK_SIZE - 1)) {
            drawPixel(screenSurface, x, y, COLOR_BLACK);
          } else {
            drawPixel(screenSurface, x, y, color);
          }
        }
      } break;
    default: break;
  }

  // Unlock the surface after painting it
  if(SDL_MUSTLOCK(screenSurface)) SDL_UnlockSurface(screenSurface);
}

void drawSnake(SDL_Surface* screenSurface, struct snake* snake)
{
  drawBlock(screenSurface, snake->blocksX[0], snake->blocksY[0], SNAKEHEADCOLOR, 1);

  for(unsigned int i = 1; i < snake->size; i++) {
    drawBlock(screenSurface, snake->blocksX[i], snake->blocksY[i], SNAKEBODYCOLOR, 1);
  }
}

void drawLimits(SDL_Surface* screenSurface)
{
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    drawBlock(screenSurface, WINDOW_LIMIT_LEFT, y, WALLCOLOR, 1);
  }
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    drawBlock(screenSurface, WINDOW_LIMIT_RIGHT, y, WALLCOLOR, 1);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    drawBlock(screenSurface, x, WINDOW_LIMIT_UP, WALLCOLOR, 1);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    drawBlock(screenSurface, x, WINDOW_LIMIT_DOWN, WALLCOLOR, 1);
  }
}

void drawSurface(SDL_Surface* screenSurface)
{
  for(unsigned int y = WINDOW_LIMIT_UP + 1; y < WINDOW_LIMIT_DOWN; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
      drawBlock(screenSurface, x, y, SURFACECOLOR, 0);
    }
  }
}

void drawFood(SDL_Surface* screenSurface, struct food* food)
{
  drawBlock(screenSurface, food->x, food->y, FOODCOLOR, 1);
}