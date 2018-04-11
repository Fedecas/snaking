#include "block.h"
#include "draw.h"
#include "window.h"

int BlockInCollision(int x1, int y1, int x2, int y2)
{
  int posX1 = x1 * BLOCK_SIZE;
  int posY1 = y1 * BLOCK_SIZE;
  SDL_Rect A = {posX1, posY1, BLOCK_SIZE, BLOCK_SIZE};

  int posX2 = x2 * BLOCK_SIZE;
  int posY2 = y2 * BLOCK_SIZE;
  SDL_Rect B = {posX2, posY2, BLOCK_SIZE, BLOCK_SIZE};

  SDL_bool hasCollision = SDL_HasIntersection(&A, &B);

  return hasCollision;
}

int BlockOutOfLimits(int x, int y)
{
  int x_outoflimits = (x < WINDOW_LIMIT_LEFT) || (x > WINDOW_LIMIT_RIGHT);
  int y_outoflimits = (y < WINDOW_LIMIT_UP) || (y > WINDOW_LIMIT_DOWN);

  return (x_outoflimits || y_outoflimits) ? 1 : 0;
}

void BlockDraw(SDL_Surface* surface, int x, int y, SDL_Color color, int type)
{
  if(BlockOutOfLimits(x ,y)) {
    printf("[warning] Block out of the screen! (x: %d, y: %d)\n", x, y);
  }

  int drawposX = (x * BLOCK_SIZE);
  int drawposY = (y * BLOCK_SIZE);

  switch (type) {
    case BLOCK_FLAT:
      DrawBox(surface, drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, color);
      break;
    case BLOCK_BORDER:
      DrawBox(surface, drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, COLOR_BLACK);
      DrawBox(surface, drawposX + 1, drawposY + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2, color);
      break;
    case BLOCK_VOLUME: // Beta (?)
      DrawBox(surface, drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, COLOR_BLACK);
      DrawBox(surface, drawposX + 1, drawposY + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2, color);

      color.r = color.r / 2;
      color.g = color.g / 2;
      color.b = color.b / 2;

      int pivot = 0;

      for (int posY = drawposY + (BLOCK_SIZE - 1); posY > drawposY + 1; posY--) {
        pivot++;
        for(int posX = drawposX + pivot; posX < drawposX + (BLOCK_SIZE - 1); posX++) {
          DrawPixel(surface, posX, posY, color);
        }
      }

      drawposX += (BLOCK_SIZE / 4) + 1;
      drawposY += (BLOCK_SIZE / 4) + 1;

      DrawBox(surface, drawposX, drawposY, (BLOCK_SIZE / 2), (BLOCK_SIZE / 2), color);
      break;
    default: break;
  }
}