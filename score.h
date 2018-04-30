#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

typedef unsigned int * score;

score ScoreCreate();
/*
 * Initialize the score count in '0'
 */

void ScoreIncrease(score GameScore);
/*
 * Increase by '1' the score given
 */

void ScoreDraw(SDL_Surface* LevelSurface, TTF_Font* font, score GameScore);
/*
 * Draw the actual score in the game screen
 */

score ScoreDestroy(score GameScore);
/*
 * Free the score's memory
 */

#endif //SNAKE_SCORE_H
