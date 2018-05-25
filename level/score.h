#ifndef SNAKING_SCORE_H
#define SNAKING_SCORE_H

typedef unsigned int score_t;

score_t LevelScore;

void ScoreRestart();
/*
 * Initialize the score count in '0'
 */

void ScoreIncrease();
/*
 * Increase by '1' the given score
 */

void ScoreDraw();
/*
 * Draw the actual score in the game screen
 */

#endif //SNAKING_SCORE_H