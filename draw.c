#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "draw.h"
#include "window.h"

void DrawPixel(SDL_Surface *screen, int x, int y, SDL_Color sdlcolor)
{
  Uint32 color = SDL_MapRGBA(screen->format, sdlcolor.r, sdlcolor.g, sdlcolor.b, sdlcolor.a);

  Uint32* pixels = screen->pixels;

  int thispixel = ((y * screen->w) + x);

  pixels[thispixel] = color;
}

void DrawBlock(SDL_Surface* screen, int x, int y, SDL_Color color, int type) // TODO move to block.c
{
  int drawposX = (x * BLOCK_SIZE);
  int drawposY = (y * BLOCK_SIZE);

  int asd = 0;

  if(SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

  switch (type) {
    case TYPE_FLAT:
      for(int posX = drawposX; posX < drawposX + BLOCK_SIZE; posX++) {
        for (int posY = drawposY; posY < drawposY + BLOCK_SIZE; posY++) {
          DrawPixel(screen, posX, posY, color);
        }
      } break;
    case TYPE_BORDER:
      for(int posX = drawposX; posX < drawposX + BLOCK_SIZE; posX++) {
        for (int posY = drawposY; posY < drawposY + BLOCK_SIZE; posY++) {
          if(posX == drawposX || posX == drawposX + (BLOCK_SIZE - 1)
             || posY == drawposY || posY == drawposY + (BLOCK_SIZE - 1)) {
            DrawPixel(screen, posX, posY, COLOR_BLACK);
          } else {
            DrawPixel(screen, posX, posY, color);
          }
        }
      } break;
    case TYPE_VOLUME:
      for(int posX = drawposX; posX < drawposX + BLOCK_SIZE; posX++) {
        for (int posY = drawposY; posY < drawposY + BLOCK_SIZE; posY++) {
          if(posX == drawposX || posX == drawposX + (BLOCK_SIZE - 1)
             || posY == drawposY || posY == drawposY + (BLOCK_SIZE - 1)) {
            DrawPixel(screen, posX, posY, COLOR_BLACK);
          } else {
            DrawPixel(screen, posX, posY, color);
          }
        }
      }

      color.r = color.r / 2;
      color.g = color.g / 2;
      color.b = color.b / 2;

      for (int posY = drawposY + BLOCK_SIZE - 1; posY > drawposY + 1; posY--) {
        asd++;
        for(int posX = drawposX + asd; posX < drawposX + BLOCK_SIZE - 1; posX++) {
          DrawPixel(screen, posX, posY, color);
        }
      }

      for(int posX = drawposX + BLOCK_SIZE/4 + 1; posX < drawposX + BLOCK_SIZE - BLOCK_SIZE/4; posX++) {
        for (int posY = drawposY + BLOCK_SIZE - BLOCK_SIZE/4 - 1; posY > drawposY + BLOCK_SIZE/4; posY--) {
          DrawPixel(screen, posX, posY, color);
        }
      } break;
    default: break;
  }

  if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
}

void DrawText(SDL_Surface* screen, char* text, int size, int x, int y, SDL_Color textcolor, SDL_Color bgcolor)
{
  TTF_Font* font = TTF_OpenFont("assets/Capture_it.ttf", size); // TODO view fonts

  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text, textcolor, bgcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

  SDL_FreeSurface(textSurface);

  TTF_CloseFont(font);
}

void DrawLine(SDL_Surface* screen, int x0, int y0, int x1, int y1, SDL_Color color) // TODO
{
  // TODO function compare with return GT - EQ - LT
  if(y0 == y1) {
    while(x0 + 1 < x1) {
      DrawPixel(screen, x0 + 1, y0, color);
      x0++;
    }
  }
}

void DrawCircle(SDL_Surface* screen, int x0, int y0, SDL_Color color) // TODO draw complete circle
{
  int radius = (BLOCK_SIZE/2);
  x0 = ((x0 * BLOCK_SIZE) + radius);
  y0 = ((y0 * BLOCK_SIZE) + radius);

  int x = (radius - 1);
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = (dx - (radius << 1));

  while (x >= y)
  {
    DrawPixel(screen, x0 + x, y0 + y, color);
    DrawPixel(screen, x0 - x, y0 + y, color);
    DrawLine(screen, x0 - x, y0 + y, x0 + x, y0 + y, color);
    DrawPixel(screen, x0 - y, y0 + x, color);
    DrawPixel(screen, x0 + y, y0 + x, color);
    DrawPixel(screen, x0 - x, y0 - y, color);
    DrawPixel(screen, x0 + x, y0 - y, color);
    DrawLine(screen, x0 - x, y0 - y, x0 + x, y0 - y, color);
    DrawPixel(screen, x0 - y, y0 - x, color);
    DrawPixel(screen, x0 + y, y0 - x, color);

    if (err <= 0)
    {
      y++;
      err += dy;
      dy += 2;
    } else {
      x--;
      dx += 2;
      err += dx - (radius << 1);
    }
  }
}

// -- Refactor -- //
void DrawWalls(SDL_Surface* screen) // TODO walls
{
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    DrawBlock(screen, WINDOW_LIMIT_LEFT, y, WALLCOLOR, 0);
  }
  for(unsigned int y = WINDOW_LIMIT_UP; y < WINDOW_LIMIT_DOWN + 1; y++) {
    DrawBlock(screen, WINDOW_LIMIT_RIGHT, y, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    DrawBlock(screen, x, WINDOW_LIMIT_UP, WALLCOLOR, 0);
  }
  for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
    DrawBlock(screen, x, WINDOW_LIMIT_DOWN, WALLCOLOR, 0);
  }
}

void DrawTerrain(SDL_Surface* screen) // TODO terrain
{
  for(unsigned int y = WINDOW_LIMIT_UP + 1; y < WINDOW_LIMIT_DOWN; y++) {
    for(unsigned int x = WINDOW_LIMIT_LEFT + 1; x < WINDOW_LIMIT_RIGHT; x++) {
      DrawBlock(screen, x, y, TERRAINCOLOR, 0);
    }
  }
}

void DrawExtra(SDL_Surface* screen)
{
  for(int posY = (WINDOW_LIMIT_DOWN + 1); posY < (WINDOW_LIMIT_DOWN + WINDOW_EXTRA + 1); posY++) {
    for(int posX = WINDOW_LIMIT_LEFT; posX < (WINDOW_LIMIT_RIGHT + 1); posX++) {
      DrawBlock(screen, posX, posY, EXTRACOLOR, 0);
    }
  }
}

void DrawScore(SDL_Surface* screen, int score)
{
  int posX = (WINDOW_LIMIT_LEFT + (BLOCK_SIZE / 4));
  int posY = ((BLOCKS_Y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

  DrawText(screen, "SCORE:", 25, posX, posY, SCORECOLOR, EXTRACOLOR);

  posX += ((BLOCK_SIZE * 4) + BLOCK_SIZE);
  posY -= (BLOCK_SIZE / 4);

  char str[12];
  sprintf(str, "%d", score);

  DrawText(screen, str, 30, posX, posY, SCORECOLOR, EXTRACOLOR);
}

/*void DrawFPS(SDL_Surface* screen, int fps)
{
  int posX = (((WINDOW_LIMIT_RIGHT - 1) * BLOCK_SIZE) - (BLOCK_SIZE / 2));
  int posY = ((BLOCKS_Y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

  DrawText(screen, "FPS", 25, posX, posY, FPSCOLOR, EXTRACOLOR);

  posX -= ((BLOCK_SIZE * 2) + (BLOCK_SIZE / 4));
  posY -= (BLOCK_SIZE / 4);

  char str[12];
  sprintf(str, "%d", fps);

  DrawText(screen, str, 30, posX, posY, FPSCOLOR, EXTRACOLOR);
}*/