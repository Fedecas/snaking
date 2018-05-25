#ifndef SNAKING_HANDLERS_H
#define SNAKING_HANDLERS_H

#define DIRECTION_NONE  0
#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP    3
#define DIRECTION_DOWN  4

#define OPTION_CONTINUE   0
#define OPTION_QUIT       1
#define OPTION_RESTART    2

int arrow;
int quit;

void HandleInputDirection();
/*
 * Catch the pressed arrow for snake direction, or quit if correspond
 */

void HandleInputOption();
/*
 * Catch the option button pressed, or quit if correspond
 */

#endif //SNAKING_HANDLERS_H