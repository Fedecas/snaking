#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

typedef unsigned int * score_t;

score_t ScoreCreate();
/*
 * Initialize the score count in '0'
 */

void ScoreIncrease(score_t score);
/*
 * Increase by '1' the score given
 */

void ScoreDraw(SDL_Surface* surface, TTF_Font* font, score_t score);
/*
 * Draw the actual score in the game screen
 */

score_t ScoreDestroy(score_t score);
/*
 * Free the score's memory
 */

#endif //SNAKE_SCORE_H
