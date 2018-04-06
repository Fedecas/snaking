#include "block.h"

int BlockInCollision(int x1, int y1, int x2, int y2)
{
  return (x1 == x2 && y1 == y2) ? 1 : 0;
}

