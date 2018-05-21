#include "../engine/block.h"
#include "../engine/draw.h"
#include "score.h"

score_t ScoreCreate()
{
  score_t GameScore = (score_t) malloc(sizeof(unsigned int));
  *GameScore = 0;

  return GameScore;
}

void ScoreIncrease(score_t GameScore)
{
  ++*GameScore;
}

void ScoreDraw(SDL_Surface* LevelSurface, TTF_Font* font, score_t GameScore)
{
  char scoreInStr[2];
  sprintf(scoreInStr, "%d", *GameScore);

  int fontwidth, fontheight;
  TTF_SizeText(font, scoreInStr, &fontwidth, &fontheight);

  int posX = (BLOCKS_X * BLOCK_SIZE) / 2 - (fontwidth / 2);
  int posY = ((BLOCKS_Y - 3) * BLOCK_SIZE);

  DrawText(LevelSurface, font, scoreInStr, posX, posY, COLOR_SCORE);
}

score_t ScoreDestroy(score_t GameScore)
{
  free(GameScore);
  GameScore = NULL;

  return GameScore;
}