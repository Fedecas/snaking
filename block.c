#include "block.h"

int blockInCollision(int block1X, int block1Y, int block2X, int block2Y)
{
  if(block1X == block2X && block1Y == block2Y) return 1;
  else return 0;
}

