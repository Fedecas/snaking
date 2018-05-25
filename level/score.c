#include <stdio.h>

#include "../engine/draw.h"
#include "../engine/font.h"

#include "score.h"

void ScoreRestart()
{
  LevelScore = 0;
}

void ScoreIncrease()
{
  ++LevelScore;
}

void ScoreDraw()
{
  char scoreInStr[2];
  sprintf(scoreInStr, "%d", LevelScore);

  int fontwidth, fontheight;
  TTF_SizeText(ScoreFont, scoreInStr, &fontwidth, &fontheight);

  int posX = (BLOCKS_X * BLOCK_SIZE) / 2 - (fontwidth / 2);
  int posY = ((BLOCKS_Y - 3) * BLOCK_SIZE);

  DrawText(ScoreFont, scoreInStr, posX, posY, COLOR_SCORE);
}