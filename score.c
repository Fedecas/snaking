#include "block.h"
#include "draw.h"
#include "score.h"

score ScoreInit()
{
  score GameScore = (score) malloc(sizeof(unsigned int));
  *GameScore = 0;

  return GameScore;
}

void ScoreIncrease(score GameScore)
{
  ++*GameScore;
}

void ScoreDraw(SDL_Surface* LevelSurface, TTF_Font* font, score GameScore)
{
  char scoreInStr[2];
  sprintf(scoreInStr, "%d", *GameScore);

  int fontwidth, fontheight;
  TTF_SizeText(font, scoreInStr, &fontwidth, &fontheight);

  int posX = (BLOCKS_X * BLOCK_SIZE) / 2 - (fontwidth / 2);
  int posY = ((BLOCKS_Y - 3) * BLOCK_SIZE);

  DrawText(LevelSurface, font, scoreInStr, posX, posY, COLOR_SCORE);
}

score ScoreDestroy(score GameScore)
{
  free(GameScore);
  GameScore = NULL;

  return GameScore;
}