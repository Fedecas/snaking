#ifndef SNAKING_SCORE_H
#define SNAKING_SCORE_H

#include "../engine/draw.h"

typedef unsigned int * score_t;

score_t ScoreCreate();
/*
 * Initialize the score count in '0'
 */

void ScoreIncrease(score_t score);
/*
 * Increase by '1' the given score
 */

void ScoreDraw(SDL_Surface* surface, TTF_Font* font, score_t score);
/*
 * Draw the actual score in the game screen
 */

score_t ScoreDestroy(score_t score);
/*
 * Free the score's memory
 */

#endif //SNAKING_SCORE_H
