#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "draw.h"
#include "window.h"

// TODO use renders ***
TTF_Font* DrawTextInit()
{
  TTF_Font* font = NULL;

  font = TTF_OpenFont(FONT_DIR, FONT_SIZE);

  if(font == NULL) {
    printf("Font could not be loaded! TTF_Error: %p\n", TTF_GetError);
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

void DrawText(SDL_Surface* screenSurface, SDL_Surface* textSurface,
              TTF_Font* font, char* text, int x, int y,
              SDL_Color textcolor, SDL_Color bgcolor)
{
  textSurface = TTF_RenderText_Shaded(font, text, textcolor, bgcolor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface(textSurface, NULL, screenSurface, &textLocation);
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

void DrawScore(SDL_Surface* screen, SDL_Surface* text, TTF_Font* font, int score)
{
  int posX = (WINDOW_LIMIT_LEFT + (BLOCK_SIZE / 4));
  int posY = ((BLOCKS_Y * BLOCK_SIZE) + (BLOCK_SIZE / 2));

  DrawText(screen, text, font, "SCORE:", posX, posY, SCORECOLOR, EXTRACOLOR);

  posX += ((BLOCK_SIZE * 5) + (BLOCK_SIZE / 2);

  char str[12];
  sprintf(str, "%d", score);

  DrawText(screen, text, font, str, posX, posY, SCORECOLOR, EXTRACOLOR);
}
