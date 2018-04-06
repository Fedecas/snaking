#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "color.h"
#include "draw.h"
#include "food.h"
#include "window.h"

#define WALLCOLOR         COLOR_YELLOW
#define FOODCOLOR         COLOR_DRED
#define SURFACECOLOR      COLOR_DGREEN
#define SNAKEHEADCOLOR    COLOR_ORANGE
#define SNAKEBODYCOLOR    COLOR_RED
#define EXTRACOLOR        COLOR_WHITE
#define SCORECOLOR        COLOR_RED
#define FPSCOLOR          COLOR_BLACK

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

void drawExtra(SDL_Surface* screenSurface)
{
  int drawed = 0;
  for(unsigned int y = WINDOW_LIMIT_DOWN + 1; y < WINDOW_LIMIT_DOWN + WINDOW_EXTRA + 1; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT; x < WINDOW_LIMIT_RIGHT + 1; x++) {
      drawBlock(screenSurface, x, y, EXTRACOLOR, 0);
      drawed++;
    }
  }
}

void drawText(SDL_Surface* screenSurface, char* string,
   int size, int x, int y,
   SDL_Color foregroundcolor,
   SDL_Color backgroundcolor)
{
  TTF_Font* font = TTF_OpenFont("assets/Capture_it.ttf", size);

  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string, foregroundcolor, backgroundcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);

  SDL_FreeSurface(textSurface);

  TTF_CloseFont(font);
}

void drawScore(SDL_Surface* screenSurface, int score)
{
  int posX = (WINDOW_LIMIT_LEFT + (BLOCK_SIZE / 4));
  int posY = ((BLOCKS_Y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

  drawText(screenSurface, "SCORE:", 25, posX, posY, SCORECOLOR, EXTRACOLOR);

  posX += ((BLOCK_SIZE * 4) + BLOCK_SIZE);
  posY -= (BLOCK_SIZE / 4);

  char str[12];
  sprintf(str, "%d", score); // Integer to string

  drawText(screenSurface, str, 30, posX, posY, SCORECOLOR, EXTRACOLOR);
}

void drawFPS(SDL_Surface* screenSurface, int fps)
{
  int posX = (((WINDOW_LIMIT_RIGHT - 1) * BLOCK_SIZE) - (BLOCK_SIZE / 2));
  int posY = ((BLOCKS_Y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

  drawText(screenSurface, "FPS", 25, posX, posY, FPSCOLOR, EXTRACOLOR);

  posX -= ((BLOCK_SIZE * 2) + (BLOCK_SIZE / 4));
  posY -= (BLOCK_SIZE / 4);

  char str[12];
  sprintf(str, "%d", fps); // Integer to string

  drawText(screenSurface, str, 30, posX, posY, FPSCOLOR, EXTRACOLOR);
}