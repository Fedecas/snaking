#include "block.h"
#include "draw.h"
#include "score.h"

score ScoreInit()
{
  score GameScore = malloc(sizeof(unsigned int));
  *GameScore = 0;

  return GameScore;
}

void ScoreIncrease(score GameScore)
{
  ++*GameScore;
}

void ScoreDraw(SDL_Surface* LevelSurface, TTF_Font* font, score GameScore)
{
  int posX = (((BLOCKS_X - 1) * BLOCK_SIZE) / 2) - (BLOCK_SIZE / 10);
  int posY = ((BLOCKS_Y - 3) * BLOCK_SIZE);

  char scoreInStr[2];
  sprintf(scoreInStr, "%d", *GameScore);

  DrawText(LevelSurface, font, scoreInStr, posX, posY, COLOR_SCORE);
}

score ScoreDestroy(score GameScore)
{
  free(GameScore);
  GameScore = NULL;
}