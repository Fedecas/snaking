#include <stdio.h>

#include "block.h"
#include "window.h"

int BlockInCollision(int x1, int y1, int x2, int y2)
{
  return ((x1 == x2) && (y1 == y2));
}

int BlockOutOfLimits(int x, int y)
{
  int x_outOfLimits = (x < WINDOW_LIMIT_LEFT) || (x > WINDOW_LIMIT_RIGHT);
  int y_outOfLimits = (y < WINDOW_LIMIT_UP) || (y > WINDOW_LIMIT_DOWN);

  return (x_outOfLimits || y_outOfLimits);
}

void BlockDraw(int x, int y, color_t color, int type)
{
  if(BlockOutOfLimits(x ,y)) {
    printf("[warning] Block out of the screen! (x: %d, y: %d)\n", x, y);
  }

  int drawposX = (x * BLOCK_SIZE);
  int drawposY = (y * BLOCK_SIZE);

  switch (type) {
    case BLOCK_FLAT:
      DrawBox(drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, color);
      break;
    case BLOCK_BORDER:
      DrawBox(drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, COLOR_BLACK);
      DrawBox(drawposX + 1, drawposY + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2, color);
      break;
    case BLOCK_VOLUME:
      DrawBox(drawposX, drawposY, BLOCK_SIZE, BLOCK_SIZE, COLOR_BLACK);
      DrawBox(drawposX + 1, drawposY + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2, color);

      color.r /= 2;
      color.g /= 2;
      color.b /= 2;

      int pivot = 0;

      for (int posY = drawposY + (BLOCK_SIZE - 2); posY > drawposY; posY--) {
        pivot++;
        for(int posX = drawposX + pivot; posX < drawposX + (BLOCK_SIZE - 1); posX++) {
          DrawPixel(posX, posY, color);
        }
      }

      drawposX += (BLOCK_SIZE / 4) + 1;
      drawposY += (BLOCK_SIZE / 4) + 1;

      DrawBox(drawposX, drawposY, (BLOCK_SIZE / 2), (BLOCK_SIZE / 2), color);
      break;
    default: break;
  }
}